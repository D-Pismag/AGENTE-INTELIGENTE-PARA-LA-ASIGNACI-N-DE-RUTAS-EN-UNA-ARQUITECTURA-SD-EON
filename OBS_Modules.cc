// Universidad del Cauca
// "AGENTE INTELIGENTE PARA LA ASIGNACION DE RUTAS EN UNA ARQUITECTURA SD-EON"
// Trabajo de grado
// Autores: David Santiago Pismag Imbachi
//          Andrés Fernando Medina Pino

#include <map>
#include <string>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <iostream>
#include <omnetpp.h>

#include <sendMessages_m.h>

using namespace omnetpp;

class Source : public cSimpleModule{
    private:
        cMessage *sendTimeOut;      //Temporizador para enviar mensajes
        int hostID;                 //Dirección de origen
        //int generationLimit;        //Tiempo límite para la generación de mensajes
        double msgTimeGeneration;   //Tiempo de generacion entre mensajes
        int sendLimit;              //Contador para limitar el número de mensajes enviados
        int msgDestination[14];     //Contador para el destino de los mensajes
        int sendMsg[3];             //Contador para los mensajes enviados de cada clase
        int numberOfNodes;          //Numero de nodos en la red
        bool flag;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void finish() override;
}; Define_Module(Source);

void Source::initialize(){
    flag=true;
    //Parametros de la fuente
    sendTimeOut=new cMessage("sendTimer");
    msgTimeGeneration=par("messageTimeGeneration").doubleValue();
    numberOfNodes=par("numberOfNodes").intValue();
    hostID=getParentModule()->par("hostID").intValue();
    //generationLimit=par("messagesToSend").intValue();
    //Timer para la generacion de mensajes
    scheduleAt(simTime()+(exponential(msgTimeGeneration)), sendTimeOut);
    sendLimit=0;
    //Contadores
    for(int i=0; i<3 ; i++){
        sendMsg[i]=0;
    }
    for(int j=0; j<14 ; j++){
        msgDestination[j]=0;
    }
    //Visualizacion de contadores
    WATCH(sendMsg);
    WATCH(msgDestination);
}

void Source::handleMessage(cMessage *msg){
    //if((msg==sendTimeOut)&&(sendLimit<generationLimit)){ //Se agota el timer y se genera un nuevo mensaje
        sendLimit++;
        //if (hostID==1 && flag==true){
        //flag=false;
        hostMessage *generatedMsg = new hostMessage("hostMessage");
        int sourceAdd=hostID;
        double delay=simTime().dbl();
        int destinationAdd;
        do{ //Generar aleatoriamente el destino del mensaje con distribucion uniforme
            destinationAdd=intuniform(1,numberOfNodes);
            //destinationAdd=14;
        }while(destinationAdd==sourceAdd);
        int typeOfService=intuniform(1,3);
        int payloadLength;
        int headerLength;
        switch(typeOfService){ //Se asumen datagramas IP, y diferentes consideraciones para las cabeceras (en bytes)
            case 1: //Servicio clase 1 (voz)
                payloadLength=160;
                headerLength=40;    //20 header IP, 8 header UDP y 12 header RTP
                break;
            case 2: //Servicio clase 2 (video)
                payloadLength=1288;
                headerLength=40;    //20 header IP, 8 header UDP y 12 header RTP
                break;
            case 3: //Servicio clase 3 (datos)
                payloadLength=1460;
                headerLength=40;    //20 header IP y 20 header TCP
                break;
        }
        //Aumento de contadores
        sendMsg[typeOfService-1]++;
        msgDestination[destinationAdd-1]++;
        //Generacion del mensaje
        generatedMsg->setSourceAdd(sourceAdd);
        generatedMsg->setDestinationAdd(destinationAdd);
        generatedMsg->setPayloadLength(payloadLength);
        generatedMsg->setHeaderLength(headerLength);
        generatedMsg->setTypeOfService(typeOfService);
        generatedMsg->setDelay(delay);
        send(generatedMsg, "outSource");
        //Timer para generar otro mensaje
        scheduleAt(simTime()+(exponential(msgTimeGeneration)), sendTimeOut);
        //}
    //}
}

void Source::finish(){
    EV << "=================Estadisticas de transmision para el host " << hostID << "=================\n";
    EV << "Mensajes enviados: " << sendLimit << "\n";
    EV << " Clasificacion por clase de servicio\n";
    for(int i=0; i<3 ; i++){
        EV << "     Clase " << i+1 << ": " << sendMsg[i] << "\n";
    }
    EV << " Clasificacion por destino\n";
    for(int j=0; j<numberOfNodes; j++){
        EV << "     Nodo " << j+1 << ": " << msgDestination[j] << "\n";
    }
}

class Sink : public cSimpleModule{
    private:
        int msgSource[3][14];           //Contador para el origen de los mensajes recibidos
        double accumulatedDelay[3][14]; //Indicador del delay promedio para cada origen de los mensajes recibidos
        int numberOfNodes;              //Numero de nodos en la red
        int hostID;                     //ID del host
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void finish() override;
}; Define_Module(Sink);

void Sink::initialize(){
    //Parametros del receptor
    hostID=getParentModule()->par("hostID").intValue();
    numberOfNodes=par("numberOfNodes").intValue();
    //Contadores
    for(int j=0; j<14; j++){
        for(int k=0; k<3; k++){
            accumulatedDelay[k][j]=0;
            msgSource[k][j]=0;
        }
    }
    //Visualizadores
    WATCH(msgSource);
    WATCH(accumulatedDelay);
}

void Sink::handleMessage(cMessage *msg){
    hostMessage *receivedMsg = check_and_cast<hostMessage *>(msg);
    //Se extrae la informacion de los paquetes que llegan
    int typeOfService=receivedMsg->getTypeOfService();
    int sourceAdd=receivedMsg->getSourceAdd();
    double delay=receivedMsg->getDelay();
    double actualTime=simTime().dbl();
    double msgDelay=actualTime-delay;
    //Se incrementan los contadores
    msgSource[typeOfService-1][sourceAdd-1]++;
    accumulatedDelay[typeOfService-1][sourceAdd-1]=(accumulatedDelay[typeOfService-1][sourceAdd-1]+msgDelay);
    //Liberar la memoria
    delete(msg);
}

void Sink::finish(){
    int totalMessage=0;
    int totalMessageDestination[14];
    for(int i=0; i<14; i++){
        totalMessageDestination[i]=0;
        for (int j=0; j<3; j++){
           totalMessage=totalMessage+msgSource[j][i];
           totalMessageDestination[i]=totalMessageDestination[i]+msgSource[j][i];
        }
    }
    EV << "=================Estadisticas de recepcion para el nodo " << hostID << "=================\n";
    EV << "Mensajes recibidos: " << totalMessage << "\n";

    double delayE2E[3];
    delayE2E[0]=0;
    delayE2E[1]=0;
    delayE2E[2]=0;

    EV << " Clasificacion por origen\n";
    for(int j=0; j<numberOfNodes; j++){
        EV << "     Nodo " << j+1 << ": " << totalMessageDestination[j] << " mensajes\n";
        for(int i=0; i<3 ; i++){
            EV << "     Clase " << i+1 << ": " << msgSource[i][j] << " con delay promedio: " << accumulatedDelay[i][j]/msgSource[i][j] << "s\n";
            if(msgSource[i][j]!=0){
                delayE2E[i] = delayE2E[i] + (accumulatedDelay[i][j]/msgSource[i][j]);
            }
        }
    }
    EV << "Delay E2E promedio:\n";
    EV << "     Clase 1: "<< delayE2E[0]/(numberOfNodes-1) <<"\n";
    EV << "     Clase 2: "<< delayE2E[1]/(numberOfNodes-1) <<"\n";
    EV << "     Clase 3: "<< delayE2E[2]/(numberOfNodes-1) <<"\n";
}

class Classifier : public cSimpleModule{
    private:
        double additionalDelay;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
}; Define_Module(Classifier);

void Classifier::initialize(){
    //Parametro para el tiempo de procesamiento
    additionalDelay=par("processDelay").doubleValue();
}

void Classifier::handleMessage(cMessage *msg){
    hostMessage *receivedMsg = check_and_cast<hostMessage *>(msg);
    int outputGate;
    if(strcmp(getName(), "Destination_Classifier") == 0){
        outputGate=(receivedMsg->getDestinationAdd())-1;
    }
    else if(strcmp(getName(), "CoS_Classifier") == 0){
        outputGate=(receivedMsg->getTypeOfService())-1;
    }
    sendDelayed(receivedMsg, additionalDelay, "outClassifier", outputGate);
}

class MUX : public cSimpleModule{
    private:
    protected:
        virtual void handleMessage(cMessage *msg) override;
}; Define_Module(MUX);

void MUX::handleMessage(cMessage *msg){
    send(msg, "outMux");
}

class Buffer : public cSimpleModule{
    private:
        int msgLimit;               //Limite de paquetes de una rafaga segun el tipo de servicio
        int contLimit;              //Contador para el limite de paquetes de una rafaga, tambien usada como burstID
        int payloadLength;          //Longitud total de la rafaga (payload+header IP)
        int headerLength;           //Longitud de la cabecera OBS
        double timeLimit;           //Limite del timer para enviar la rafaga
        double additionalDelay;     //Tiempo de procesamiento del buffer (generacion de rafaga)
        cQueue classBuffer;         //Buffer para almacenar los datagramas IP para formar la ráfaga
        cMessage *bufferTimeOut;    //Mensaje usado para limitar el tiempo de espera de conformacion de la rafaga
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void sendBurstMessage();
}; Define_Module(Buffer);

void Buffer::initialize(){
    contLimit=0;
    payloadLength=0;
    headerLength=par("headerLength").intValue();
    msgLimit=par("msgLimitClass").intValue();
    timeLimit=par("timeLimitClass").doubleValue();
    additionalDelay=par("processDelay").doubleValue();
    bufferTimeOut=new cMessage("bufferTimeOut");
}

void Buffer::handleMessage(cMessage *msg){
    if(msg==bufferTimeOut){ //Se acabo el tiempo de espera asignado y se envia el macropaquete
        sendBurstMessage();
    }else if(contLimit < (msgLimit)){ //Llega un mensaje nuevo, se agrega al buffer para formar la rafaga
        hostMessage *receivedMsg = check_and_cast<hostMessage *>(msg);
        if (contLimit==0){ //Tratamiento para el primer mensaje, se genera el timer para envio de rafaga
            scheduleAt(simTime()+timeLimit, bufferTimeOut);
        }
        int totalDatagramLength=receivedMsg->getPayloadLength()+receivedMsg->getHeaderLength();
        payloadLength=payloadLength+totalDatagramLength;
        contLimit++;
        classBuffer.insert(receivedMsg);
        if(contLimit==msgLimit){
            cancelEvent(bufferTimeOut);
            sendBurstMessage();
        }
    }
}

void Buffer::sendBurstMessage(){
    hostMessage *receivedMsg = new hostMessage("hostMessage");
    obsMessage *obsBurst= new obsMessage("obsBurst");
    obsBurst->setHostMessageGroupArraySize(msgLimit);
    for(int i=0; i<msgLimit ; i++){
            obsBurst->setHostMessageGroup(i, nullptr);
    }
    int i=0;
    while(!classBuffer.isEmpty()){
        receivedMsg=(hostMessage *) classBuffer.pop();
        if(i==0){ //Se configuran los parametros base de la rafaga OBS para el primer mensaje (todos tienen los mismos parametros)
            obsBurst->setSourceAdd(receivedMsg->getSourceAdd());
            obsBurst->setDestinationAdd(receivedMsg->getDestinationAdd());
            obsBurst->setTypeOfService(receivedMsg->getTypeOfService());
            obsBurst->setSignalWavelenght(0);
            obsBurst->setPayloadLength(payloadLength);
            obsBurst->setHeaderLength(headerLength);
            obsBurst->setBurstID(contLimit);
        }
        //Se agregan todos los datagramas al vector en la rafaga
        obsBurst->setHostMessageGroup(i, receivedMsg);
        i++;
    }
    //Se envia la rafaga
    sendDelayed(obsBurst, additionalDelay, "outBuffer");
    //Se reinician los contadores
    contLimit=0;
    payloadLength=0;
}

class Deconformer : public cSimpleModule{
    private:
        int contReceivedBursts[3];  //Conteo de rafagas recibidas por tipo de servicio
        double averageLength[3];    //Longitud promedio de las rafagas recibidas por tipo de servicio
        double additionalDelay;     //Tiempo de procesamiento del deconformador
        double firstBurst;          //Tiempo en que se recibe la primera ráfaga
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void receptionACK(obsMessage *msg);
        virtual void disassembleBurst(obsMessage *msg);
        virtual void finish() override;
}; Define_Module(Deconformer);

void Deconformer::initialize(){
    additionalDelay=par("processDelay").doubleValue();
    for(int i=0; i<3; i++){
        contReceivedBursts[i]=0;
        averageLength[i]=0;
    }
    firstBurst=0;
    WATCH(contReceivedBursts);
    WATCH(averageLength);
}

void Deconformer::handleMessage(cMessage *msg){
    obsMessage *receivedMsg = check_and_cast<obsMessage *>(msg);
    EV << "=================Llega un mensaje al "<< getParentModule()->getParentModule()->getParentModule()->getName() <<"=================\n";
    receptionACK(receivedMsg);
    disassembleBurst(receivedMsg);
}

void Deconformer::receptionACK(obsMessage *msg){ //Generamos un mensaje de confirmar recepcion para liberar el recurso
    resourceRequest *releaseMsg=new resourceRequest("obsBurst");
    releaseMsg->setTypeOfMsg(3);
    releaseMsg->setSourceNode(getParentModule()->getParentModule()->getParentModule()->par("nodeID").intValue());
    releaseMsg->setDestinationNode(msg->getSourceAdd());
    releaseMsg->setSignalWavelenght(msg->getSignalWavelenght());
    sendDelayed(releaseMsg, additionalDelay, "outToAssembler");
    EV << "Se libera la longitud de onda: " << msg->getSignalWavelenght() << "\n";
}

void Deconformer::disassembleBurst(obsMessage *msg){ //Desensamble de la rafaga
    if( (contReceivedBursts[0]==0) && (contReceivedBursts[1]==0) && (contReceivedBursts[2]==0) ){
        firstBurst=simTime().dbl();
    }
    int ToS=msg->getTypeOfService();
    int messageLimit=msg->getHostMessageGroupArraySize();
    contReceivedBursts[ToS-1]++;
    averageLength[ToS-1]=averageLength[ToS-1]+(msg->getPayloadLength()+msg->getHeaderLength());
    for(int i=0 ; i<messageLimit ; i++){
        const hostMessage *receivedMsgList=msg->getHostMessageGroup(i);
        if(receivedMsgList!=nullptr){
            hostMessage *msgCopy = receivedMsgList->dup();
            sendDelayed(msgCopy, additionalDelay, "outDeconformer");
        }
    }
    EV<< "Llega a " << getParentModule()->getParentModule()->getParentModule()->getName() << " la rafaga con ID " << msg->getBurstID() << "\n";
    delete(msg);
}

void Deconformer::finish(){
    int totalMessages=0;

    for (int i=0; i<3 ; i++){
        totalMessages=totalMessages+contReceivedBursts[i];
    }
    double Throughput = 8*( averageLength[0]+averageLength[1]+averageLength[2] )/(simTime().dbl()-firstBurst);

    EV << "=================Estadisticas de recepcion para el deconformador del " << getParentModule()->getParentModule()->getParentModule()->getName() << "=================\n";
    EV << "Tiempo en que llega la primera ráfaga: " << firstBurst << "s\n";
    EV << "Throughput: " << Throughput << " bps \n";
    EV << "Ráfagas recibidas: " << totalMessages << "\n";
    EV << " Clasificacion por clase de servicio\n";
    for(int i=0; i<3 ; i++){
        EV << "     Clase " << i+1 << ": " << contReceivedBursts[i] << " con longitud promedio de " << averageLength[i]/contReceivedBursts[i] << " ( Total: " << averageLength[i] << " ) bytes\n";
    }

}

class OEO_Conversor : public cSimpleModule{
    private:
        double additionalDelay; //Tiempo de procesamiento del conversor OEO
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
}; Define_Module(OEO_Conversor);

void OEO_Conversor::initialize(){
    additionalDelay = par("processDelay").doubleValue();
}

void OEO_Conversor::handleMessage(cMessage *msg){
    sendDelayed(msg, additionalDelay, "outOEO");
}

class Sender_Buffer : public cSimpleModule{
    private:
        double additionalDelay;             //Retardo de procesamiento
        double totalConfigurationTime;      //Contador del tiempo total de gestion de recursos
        int totalRequests;                  //Cantidad total de solicitudes de recursos generadas
        int totalRejects;                   //Cantidad total de solicitudes de recursos rechazadas
        int sendedBurst;                    //Cantidad total de rafagas enviadas
        double averageLength[3];            //Longitud promedio de las ráfagas enviadas
        double firstBurst;                  //Tiempo en que se envía la primera ráfaga
        cQueue senderBuffer;                //Buffer para almacenar las rafagas a la espera de recursos
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void sendRequest(obsMessage *msg);
        virtual void handleRequestACK(resourceRequest *msg);
        virtual void handleRequestReject(resourceRequest *msg);
        virtual void finish() override;
}; Define_Module(Sender_Buffer);

void Sender_Buffer::initialize(){
    additionalDelay = par("processDelay").doubleValue();
    totalConfigurationTime=0;
    totalRequests=0;
    sendedBurst=0;
    totalRejects=0;
    averageLength[0]=0;
    averageLength[1]=0;
    averageLength[2]=0;
    firstBurst=0;
}

void Sender_Buffer::handleMessage(cMessage *msg){
    cGate *arrivalGate = msg->getArrivalGate();
    if(arrivalGate == gate("inSenderBuffer")){ //Llega una rafaga de trafico al sender
        EV << "=================Se tiene una rafaga lista en " << getParentModule()->getParentModule()->getParentModule()->getParentModule()->getName() << "=================\n";
        obsMessage *receivedMsg = check_and_cast<obsMessage *>(msg);
        //Se genera una solicitud de recursos
        sendRequest(receivedMsg);
        //Se almacena el mensaje a la espera en el buffer
        senderBuffer.insert(receivedMsg);
    } else if(arrivalGate == gate("inFromControlUnit")){ //Llega un mensaje del controlador
        if(dynamic_cast<resourceRequest *>(msg) != nullptr){
            resourceRequest *receivedMsg = check_and_cast<resourceRequest *>(msg);
            if(receivedMsg->getTypeOfMsg()==2){ //ACK del controlador, se puede enviar la rafaga correspondiente
                EV << "=================Llega una confirmacion de recursos al " << getParentModule()->getParentModule()->getParentModule()->getParentModule()->getName() << "=================\n";
                //Se gestiona el envio de la rafaga correspondiente
                handleRequestACK(receivedMsg);
            } else if(receivedMsg->getTypeOfMsg()==3){ //Aviso de eliminación de solicitud
                EV << "=================Llega una confirmacion de eliminación de solicitud al " << getParentModule()->getParentModule()->getParentModule()->getParentModule()->getName() << "=================\n";
                //Se gestiona el envio de la rafaga correspondiente
                handleRequestReject(receivedMsg);
            }
        }
    } else if(arrivalGate == gate("inFromDeconformer")){ //
        resourceRequest *receivedMsg = check_and_cast<resourceRequest *>(msg);
        if(receivedMsg->getTypeOfMsg()==3){ //Se reenvia el mensaje al controlador para liberar recursos
            sendDelayed(receivedMsg, additionalDelay, "outToControlUnit");
        }
    }
}

void Sender_Buffer::sendRequest(obsMessage *msg){ //Generacion de una solicitud de recursos
    EV << "Se envia una resource request para la siguiente rafaga\n";
    EV << "Nodo de origen: " << msg->getSourceAdd() << "\n";
    EV << "Nodo de destino: " << msg->getDestinationAdd() << "\n";
    EV << "Tipo de servicio: " << msg->getTypeOfService() << "\n";
    EV << "Longitud de la rafaga: " << msg->getPayloadLength() << "+" << msg->getHeaderLength() <<"\n";
    EV << "ID de la rafaga: " << msg->getBurstID() << "\n";
    EV << "Longitud de onda: " << msg->getSignalWavelenght() << "\n";
    //Se crea el mensaje de solicitud de recursos
    resourceRequest *requestMsg = new resourceRequest("resourceRequest");
    requestMsg->setTypeOfMsg(1);
    requestMsg->setSourceNode(msg->getSourceAdd());
    requestMsg->setDestinationNode(msg->getDestinationAdd());
    requestMsg->setBurstID(msg->getBurstID());
    requestMsg->setSignalWavelenght(0);
    requestMsg->setGenerationTime(simTime().dbl());
    requestMsg->setTypeOfService(msg->getTypeOfService());
    //Se envia la solicitud de recursos
    sendDelayed(requestMsg, additionalDelay, "outToControlUnit");
    //Aumenta el contador de solicitudes generadas
    totalRequests++;
}

void Sender_Buffer::handleRequestACK(resourceRequest *receivedMsg){ //Gestionar el envio de una rafaga al confirmar los recursos
    if(receivedMsg->getTypeOfMsg()==2){ //Confirmamos que se trata de un ACK de recursos
        if(sendedBurst==0){
            firstBurst=simTime().dbl();
        }
        //Obtenemos el burstID
        int burstID = receivedMsg->getBurstID();
        //Obtenemos la longitud de onda asignada
        int assignedWavelength=receivedMsg->getSignalWavelenght();
        //Obtenemos el tiempo en que se demora en establecer el recurso
        double generationDelay = simTime().dbl()-receivedMsg->getGenerationTime();
        //Eliminamos el ACK
        delete(receivedMsg);
        //Revisamos las rafagas en espera en busca de aquella con el mismo burstID
        for (int i = 0; i < senderBuffer.getLength(); i++) {
            obsMessage *burstMsg = check_and_cast<obsMessage *>(senderBuffer.get(i));
            if (burstMsg->getBurstID() == burstID) {
                //Calculo del tiempo en establecer los recursos
                totalConfigurationTime=totalConfigurationTime+generationDelay;
                //Enviar la ráfaga correspondiente
                senderBuffer.remove(burstMsg);
                burstMsg->setSignalWavelenght(assignedWavelength);
                EV << "Se envia una rafaga con la siguiente informacion\n";
                EV << "Burst ID: " << burstMsg->getBurstID() << "\n";
                EV << "Nodo de origen: " << burstMsg->getSourceAdd() << "\n";
                EV << "Nodo de destino: " << burstMsg->getDestinationAdd() << "\n";
                EV << "Tipo de servicio: " << burstMsg->getTypeOfService() << "\n";
                EV << "Longitud de la rafaga: " << burstMsg->getPayloadLength() << "+" << burstMsg->getHeaderLength() << "\n";
                averageLength[burstMsg->getTypeOfService()-1]=averageLength[burstMsg->getTypeOfService()-1]+(burstMsg->getPayloadLength()+burstMsg->getHeaderLength());
                EV << "Tiempo de establecimiento de recursos: " << generationDelay << "\n";
                EV << "Longitud de onda: " << burstMsg->getSignalWavelenght() << "\n";
                sendedBurst++;
                sendDelayed(burstMsg, additionalDelay, "outSenderBuffer");
                break;
            }
        }
    }
}

void Sender_Buffer::handleRequestReject(resourceRequest *receivedMsg){ //Gestionar la eliminación de una ráfaga
    if(receivedMsg->getTypeOfMsg()==3){ //Confirmamos que se trata de un rechazo por falta de recursos
        //Obtenemos el burstID
        int burstID = receivedMsg->getBurstID();
        //Eliminamos el mensaje de rechazo
        delete(receivedMsg);
        //Revisamos las rafagas en espera en busca de aquella con el mismo burstID
        for (int i = 0; i < senderBuffer.getLength(); i++) {
            obsMessage *burstMsg = check_and_cast<obsMessage *>(senderBuffer.get(i));
            if (burstMsg->getBurstID() == burstID) {
                senderBuffer.remove(burstMsg);
                EV << "Se elimina una rafaga con la siguiente informacion\n";
                EV << "Burst ID: " << burstMsg->getBurstID() << "\n";
                EV << "Nodo de origen: " << burstMsg->getSourceAdd() << "\n";
                EV << "Nodo de destino: " << burstMsg->getDestinationAdd() << "\n";
                EV << "Tipo de servicio: " << burstMsg->getTypeOfService() << "\n";
                EV << "Longitud de la rafaga: " << burstMsg->getPayloadLength() << "+" << burstMsg->getHeaderLength() << "\n";
                totalRejects++;
                delete(burstMsg);
                break;
            }
        }
    }
}

void Sender_Buffer::finish(){
    double Throughput = 8*( averageLength[0]+averageLength[1]+averageLength[2] )/(simTime().dbl()-firstBurst);
    EV << "=================Estadisticas para el nodo " << getParentModule()->getParentModule()->getParentModule()->getParentModule()->par("nodeID") << "=================\n";
    EV << "Total de request solicitadas: " << totalRequests << "\n";
    EV << "Total de rafagas enviadas: " << sendedBurst << "\n";
    EV << "Throughput: " << Throughput << " bps\n";
    EV << "Tiempo promedio de establecimiento de recursos: " << totalConfigurationTime/sendedBurst << "s \n";
}

class Core_CU : public cSimpleModule{
    private:
        double additionalDelay; //Tiempo de procesamiento
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
}; Define_Module(Core_CU);

void Core_CU::initialize(){
    additionalDelay = par("processDelay").doubleValue();
}

void Core_CU::handleMessage(cMessage *msg){
    cGate *arrivalGate = msg->getArrivalGate();
    if(arrivalGate == gate("inFromEdgeSender")){ //Llega una solicitud de recursos del sender al core, se reenvia al controlador
        resourceRequest *receivedMsg = check_and_cast<resourceRequest *>(msg);
        sendDelayed(receivedMsg, additionalDelay, "outToController");
    }else if(arrivalGate == gate("inFromController")){ //Llega un mensaje del controlador
        if (dynamic_cast<resourceRequest *>(msg) != nullptr) { //Llega un ACK de respuesta resourceRequest
            resourceRequest *receivedMsg = check_and_cast<resourceRequest *>(msg);
            if(receivedMsg->getTypeOfMsg()==2){ //Se confirma que se trata de un ACK de recursos
                //Se redirige el ACK de recursos hacia el sender
                sendDelayed(receivedMsg, additionalDelay, "outToEdgeSender");
            }
        }else if(dynamic_cast<configurationMessage *>(msg) != nullptr){ //Llega un mensaje de configuracion del switch
            configurationMessage *receivedMsg = check_and_cast<configurationMessage *>(msg);
            EV<< "=================Llega un mensaje de configuracion al " << getParentModule()->getParentModule()->getName() << "=================\n";
            sendDelayed(receivedMsg, additionalDelay, "outToSwitch");
        }
    }else if(arrivalGate == gate("inFromSwitch")){ //Llegan mensajes del Switch
        if (dynamic_cast<resourceRequest *>(msg) != nullptr){ //Llega una confirmacion de perdida de ráfaga
            resourceRequest *receivedMsg = check_and_cast<resourceRequest *>(msg);
            sendDelayed(receivedMsg, additionalDelay, "outToController");
        }else if (dynamic_cast<configurationMessage *>(msg) != nullptr){ //Llega un mensaje de confirmacion de configuracion del switch
            configurationMessage *receivedMsg = check_and_cast<configurationMessage *>(msg);
            if(receivedMsg->getTypeOfMsg()==2){
                EV<< "=================Se configura exitosamente el switch del " << getParentModule()->getParentModule()->getName() << "=================\n";
                sendDelayed(receivedMsg, additionalDelay, "outToController");
            }
        }

    }
}

class Optical_Switch : public cSimpleModule{
    private:
        double lossDelay;                       //Delay generado por la perdida de un paquete
        double additionalDelay;                 //Delay de procesamiento
        double lossProbability;                 //Probabilidad de perdida de un paquete
        int numWavelengths;                     //Numero de longitudes de onda en la red
        std::vector<int> inGate;                //Compuerta de entrada para la longitud de onda correspondiente (indice)
        std::vector<int> outGate;               //Compuerta de salida para la longitud de onda correspondiente (indice)
        std::vector<int> lossBurstCont;         //Contador para las rafagas perdidas (por longitud de onda)
        std::vector<bool> configurationValid;   //Bandera para saber si una longitud de onda se encuentra configurada
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void gateConfiguration(configurationMessage *msg);
        virtual void handleTraffic(obsMessage *msg, cGate *arrivalGate);
        virtual void finish() override;
}; Define_Module(Optical_Switch);

void Optical_Switch::initialize(){
    lossDelay = par("lossDelay").doubleValue();
    additionalDelay = par("processDelay").doubleValue();
    lossProbability = par("lossProbability").doubleValue();
    numWavelengths = par("numWavelengths").intValue();
    inGate.resize(numWavelengths, 0);
    outGate.resize(numWavelengths, 0);
    lossBurstCont.resize(numWavelengths, 0);
    configurationValid.resize(numWavelengths, false); //false=inactiva ; true=activa(no se puede usar)
}

void Optical_Switch::handleMessage(cMessage *msg){
    cGate *arrivalGate = msg->getArrivalGate();
    if(arrivalGate == gate("inFromCU")){ //Llega un mensaje para configurar las interfaces de entrada y salida
        configurationMessage *receivedMsg = check_and_cast<configurationMessage *>(msg);
        gateConfiguration(receivedMsg);
    }else{ //Llega una ráfaga de datos
        obsMessage *receivedMsg = check_and_cast<obsMessage *>(msg);
        handleTraffic(receivedMsg, arrivalGate);
    }
}

void Optical_Switch::gateConfiguration(configurationMessage *receivedMsg){ //Manejo de la configuracion de un conmutador optico
    //Longitud de onda de la configuracion
    int signalwavelengthIndex=receivedMsg->getSignalWavelenght()-1;
    configurationValid[signalwavelengthIndex]=true;
    inGate[signalwavelengthIndex]=receivedMsg->getInputTrafficPort();
    outGate[signalwavelengthIndex]=receivedMsg->getOutputTrafficPort();
    receivedMsg->setTypeOfMsg(2);
    sendDelayed(receivedMsg, additionalDelay, "outToCU");
    EV<< "=================Se configura el switch del " << getParentModule()->getParentModule()->getName() << "=================\n";
    EV<< "Longitud de onda: " << signalwavelengthIndex+1 << "\n";
    EV<< "Interfaz de entrada: " << inGate[signalwavelengthIndex] << "\n";
    EV<< "Interfaz de salida: " << outGate[signalwavelengthIndex] << "\n";
    EV<< "Se retorna el ACK de configuracion\n";
}

void Optical_Switch::handleTraffic(obsMessage *receivedMsg, cGate *arrivalGate){ //Manejo de una rafaga de datos que llega al conmutador
    int msgwavelengthIndex=(receivedMsg->getSignalWavelenght())-1;
    if(configurationValid[msgwavelengthIndex]==true){ //Se confirma que el conmutador esta configurado para la longitud de onda
        //int inputGate=arrivalGate->getIndex();
        EV<< "=================Llega una rafaga al " << getParentModule()->getParentModule()->getName() << "=================\n";
        //if(inputGate==inGate[msgwavelengthIndex]){ //Llega un mensaje por la puerta correcta
            double randomValue = uniform(0, 1);
            EV << "RNG escogido: " << randomValue <<"\n";
            EV << "Wavelength de la comunicacion: " << msgwavelengthIndex+1 <<"\n";
            if((randomValue<lossProbability)&&(outGate[msgwavelengthIndex]!=0)){ //Se genera una perdida de la rafaga
                EV<< "Se genera una perdida de rafaga\n";
                //Aumenta el contador de rafagas perdidas en el nodo
                lossBurstCont[msgwavelengthIndex]=lossBurstCont[msgwavelengthIndex]+1;
                //Generamos un mensaje para liberar el recurso
                resourceRequest *releaseMsg=new resourceRequest("obsBurst");
                releaseMsg->setTypeOfMsg(3);
                releaseMsg->setSourceNode(getParentModule()->getParentModule()->par("nodeID").intValue());
                releaseMsg->setDestinationNode(receivedMsg->getSourceAdd());
                releaseMsg->setSignalWavelenght(msgwavelengthIndex+1);
                sendDelayed(releaseMsg, lossDelay, "outToCU");
                configurationValid[msgwavelengthIndex]=false;
                delete(receivedMsg);
            }else{
                EV<< "Se redirige la rafaga hacia su destino\n";
                send(receivedMsg, "outTraffic", outGate[msgwavelengthIndex]);
                //Se inhabilita la configuracion para esa longitud de onda
                configurationValid[msgwavelengthIndex]=false;
            }
        //}else{
            //EV<< "Llega una rafaga por la compuerta equivocada, se descarta la rafaga\n";
            //delete(receivedMsg);
        //}
    }else{
        EV<< "El switch no esta configurado para la rafaga entrante\n";
        EV<< "Longitud de onda: " << receivedMsg->getSignalWavelenght() << "\n";
        EV<< "Longitud de onda configurada: " << configurationValid[msgwavelengthIndex] << "\n";
        EV<< "Nodo de origen: " << receivedMsg->getSourceAdd() << "\n";
    }
}

void Optical_Switch::finish(){
    //EV<<"=================Rafagas perdidas en " << getParentModule()->getParentModule()->getName() << "=================\n";
    //EV<< "Rafagas perdidas con base en la longitud de onda\n";
    //for(int i=0; i<numWavelengths; i++){
    //    EV<< "Longitud de onda [ " << i+1 << " ]: " << lossBurstCont[i] <<"\n";
    //}
}

class Controller_Classifier : public cSimpleModule{
    private:
        double additionalDelay; //Delay de procesamiento
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
}; Define_Module(Controller_Classifier);

void Controller_Classifier::initialize(){
    additionalDelay=par("processDelay").doubleValue();
}

void Controller_Classifier::handleMessage(cMessage *msg){
    int outputGate;
    if (dynamic_cast<configurationMessage *>(msg) != nullptr){ //Llegan mensajes de configuracion a distribución
        configurationMessage *receivedMsg = check_and_cast<configurationMessage *>(msg);
        if (receivedMsg->getTypeOfMsg()==1){ //Se confirma un mensaje destinado a configuracion
            outputGate=(receivedMsg->getDestinationNode())-1;
            sendDelayed(receivedMsg, additionalDelay, "outClassifier", outputGate);
        }
    }else if(dynamic_cast<resourceRequest *>(msg) != nullptr){ //Llega un ACK de confirmacion de configuracion, el cual permite el envio de la rafaga
        resourceRequest *receivedMsg = check_and_cast<resourceRequest *>(msg);
        if (receivedMsg->getTypeOfMsg()==2){ //Se confirma un ACK destinado a permitir el envio de la ráfaga
            outputGate=(receivedMsg->getDestinationNode())-1;
            sendDelayed(receivedMsg, additionalDelay, "outClassifier", outputGate);
        }
    }
}

class Message_Processor : public cSimpleModule{
    private:
        int numWavelengths;                     //Numero de longitudes de onda en la red
        int requestCont;                        //Contador para el numero de solicitudes de recursos recibidas
        int requestRejectCont[3];               //Contador para el numero de solicitudes de recursos rechazadas
        int processedRequests;                  //Contador de las solicitudes procesadas
        int resourceDelayedMessages[3];            //Contador para promediar el retardo de las solicitudes procesadas (no eliminadas) que tuvieron que esperar recurso
        bool availableIA;                       //Bandera de disponibilidad del AI
        bool requestWaitTimeIA_Flag;            //Tiempo de espera para manejar una solicitud (AI)
        bool requestWaitTimeWavelength_Flag;    //Tiempo de espera para manejar una solicitud (Wavelength)
        double requestWaitTimeIA_S;             //Tiempo de inicio de espera por el AI
        double requestWaitTimeIA_T;             //Tiempo en que se asigna al AI la solicitud
        double requestWaitTimeWavelength_S;     //Tiempo de inicio de espera por longitud de onda
        double requestWaitTimeWavelength[3];     //Tiempo en que se asigna una longitud de onda
        double additionalDelay;                 //Delay de procesamiento
        double configurationOpticalPath;        //Retardo por configuración del camino óptico
        double delayExecuteAI;                  //Tiempo en que demora en ejecutarse el AI/Algoritmo
        double timeLimitProcess;                //Tiempo limite de ejecucion de la simulacion
        double resourceTolerationTime1;         //Tiempos de tolerancia por espera de recursos (Clase 1)
        double resourceTolerationTime2;         //Tiempos de tolerancia por espera de recursos (Clase 1)
        double resourceTolerationTime3;         //Tiempos de tolerancia por espera de recursos (Clase 1)
        cQueue AIQueue;                         //Buffer de solicitudes al AI
        cQueue resourceQueue;                   //Buffer de solicitudes para wavelength
        std::vector<cQueue> configurationMsg;           //Cantidad de buffers destinados a mensajes de configuracion
        std::vector<bool> availableResources;           //Bandera para disponibilidad de longitud de onda
        std::vector<int> sourceNodeRequest;             //Origen de la solicitud
        std::vector<int> nodeConfigurationCount;        //Cantidad de nodos configurados para una solicitud (ACKs recibidos)
        std::vector<int> nodeConfigurationQuantity;     //Cantidad total de nodos a configurar para una solicitud
        std::vector<double> wavelengthUsageTime;        //Ocupacion de una longitud de onda en tiempo (por request)
        std::vector<double> wavelengthTotalUsageTime;   //Ocupacion total de una longitud de onda en tiempo
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual int firstFit();
        virtual void handleResourceRequest(resourceRequest *msg);
        virtual void handleResourceLiberation(resourceRequest *msg);
        virtual void handleAI(resourceRequest *msg);
        virtual void handleConfigurationMessage(configurationMessage *msg);
        virtual void handleConfigurationACK(configurationMessage *msg);
        virtual void finish() override;
}; Define_Module(Message_Processor);

void Message_Processor::initialize(){
    numWavelengths=par("numWavelengths").intValue();
    additionalDelay=par("processDelay").doubleValue();
    timeLimitProcess=par("timeLimitProcess").doubleValue();
    resourceTolerationTime1 = par("resourseTolerationTime1").doubleValue();
    resourceTolerationTime2 = par("resourseTolerationTime2").doubleValue();
    resourceTolerationTime3 = par("resourseTolerationTime3").doubleValue();
    availableIA=true;
    requestWaitTimeIA_Flag=true;
    requestWaitTimeIA_S=0;
    requestWaitTimeIA_T=0;
    requestWaitTimeWavelength_Flag=true;
    requestWaitTimeWavelength_S=0;
    requestWaitTimeWavelength[0]=0;
    requestWaitTimeWavelength[1]=0;
    requestWaitTimeWavelength[2]=0;
    resourceDelayedMessages[0]=0;
    resourceDelayedMessages[1]=0;
    resourceDelayedMessages[2]=0;
    requestCont=0;
    processedRequests=0;
    delayExecuteAI=0;
    configurationOpticalPath=0;
    requestRejectCont[0]=0;
    requestRejectCont[1]=0;
    requestRejectCont[2]=0;
    configurationMsg.resize(numWavelengths);
    availableResources.resize(numWavelengths, true);
    sourceNodeRequest.resize(numWavelengths, 0);
    wavelengthUsageTime.resize(numWavelengths, 0);
    wavelengthTotalUsageTime.resize(numWavelengths, 0);
    nodeConfigurationCount.resize(numWavelengths, 0);
    nodeConfigurationQuantity.resize(numWavelengths, 0);
}

void Message_Processor::handleMessage(cMessage *msg){
    if (simTime().dbl() >= timeLimitProcess) {
        endSimulation();
    }
    if (dynamic_cast<resourceRequest *>(msg) != nullptr) { //Llega un mensaje de tipo resourceRequest
        resourceRequest *receivedMsg = check_and_cast<resourceRequest *>(msg);
        if (receivedMsg->getTypeOfMsg()==1){ //Un mensaje para solicitar recursos (typeOfMsg=1)
            EV<<"=================Llega una solicitud de recursos al controlador=================\n";
            handleResourceRequest(receivedMsg);
        }else if (receivedMsg->getTypeOfMsg()==3){ //ACK para confirmar la finalizacion de una comunicacion
            EV<<"=================Llega una ACK para liberar recursos al controlador=================\n";
            handleResourceLiberation(receivedMsg);
        }
    }else if (dynamic_cast<configurationMessage *>(msg) != nullptr) { //Llegan mensajes de configuracion de nodos
        configurationMessage *receivedMsg = check_and_cast<configurationMessage *>(msg);
        if (receivedMsg->getTypeOfMsg()==1){ //Se deben reenviar los mensajes de configuracion provenientes del AI hacia la red
            handleConfigurationMessage(receivedMsg);
        }else if(receivedMsg->getTypeOfMsg()==2){ //Se recibe un ACK de configuracion de los switches
            handleConfigurationACK(receivedMsg);
        }
    }
}

int Message_Processor::firstFit(){
    //Se crea una variable que guarde la longitud de onda asignada
    int assignedWavelength=0;
    //Asignacion de espectro first-fit
    for (int i=0; i<numWavelengths; i++){
        if (availableResources[i]==true){ //El recurso esta disponible y se asigna
            assignedWavelength=i+1;
            //El recurso pasa a estar asignado
            availableResources[i]=false;
            //Se contabiliza el uso del recurso
            wavelengthUsageTime[i]=simTime().dbl();
            break;
        }
    }
    return(assignedWavelength);
}

void Message_Processor::handleAI(resourceRequest *msg){
    if(availableIA==true){ //El AI se encuentra disponible
        EV << "Se reenvia la solicitud al AI\n";
        resourceRequest *receivedMsg = check_and_cast<resourceRequest *>(msg);
        availableIA=false;

        int msgSourceNode=receivedMsg->getSourceNode();
        int msgDestinationNode=receivedMsg->getDestinationNode();
        int typeOfMsg=receivedMsg->getTypeOfMsg();
        int typeOfService=receivedMsg->getTypeOfService();

        EV << "El AI recibe una solicitud de recursos con la siguiente informacion: \n";
        EV << "Nodo origen: " << msgSourceNode << "\n";
        EV << "Nodo destino: " << msgDestinationNode << "\n";
        EV << "Clase de servicio: " << typeOfService << "\n";

        sendDelayed(receivedMsg, additionalDelay, "outToIA");
    }else{ //El AI se encuentra manejando una solicitud
        if(requestWaitTimeIA_Flag==true){ //Se contabiliza la espera por manejo del AI
            requestWaitTimeIA_Flag=false;
            requestWaitTimeIA_S=simTime().dbl();
        }
        EV << "El AI se encuentra ocupado, almacenando la solicitud\n";
        AIQueue.insert(msg);
    }
}

void Message_Processor::handleResourceRequest(resourceRequest *receivedMsg){
    requestCont=requestCont+1;
    int assignedWavelength=firstFit();
    receivedMsg->setResourceDelay(simTime().dbl());
    if(assignedWavelength==0){ //No hay recursos disponibles para atender la peticion
        if(requestWaitTimeWavelength_Flag==true){ //Se contabiliza la espera por recurso
            requestWaitTimeWavelength_Flag=false;
        }
        EV << "No hay recursos para realizar el envio de la rafaga, se almacena en un buffer\n";
        resourceQueue.insert(receivedMsg);
    } else{ //Hay recursos disponibles para atender la peticion
        processedRequests++;
        EV << "Hay recursos para realizar el envio de la rafaga\n";
        //Se asigna la longitud de onda a la solicitud
        receivedMsg->setSignalWavelenght(assignedWavelength);
        //Se guarda el origen de la solicitud
        sourceNodeRequest[assignedWavelength-1]=receivedMsg->getSourceNode();
        handleAI(receivedMsg);
    }
}

void Message_Processor::handleResourceLiberation(resourceRequest *receivedMsg){
    int wavelengthIndex=receivedMsg->getSignalWavelenght()-1;
    double actualUsageTime=wavelengthUsageTime[wavelengthIndex];
    //Tiempo total de ocupacion del recurso
    wavelengthUsageTime[wavelengthIndex]=simTime().dbl()-actualUsageTime;
    //Tiempo acumulado de utilizacion del recurso
    wavelengthTotalUsageTime[wavelengthIndex]=wavelengthTotalUsageTime[wavelengthIndex]+wavelengthUsageTime[wavelengthIndex];
    EV<<"Se libera la longitud de onda "<< receivedMsg->getSignalWavelenght() << "\n";
    availableResources[(receivedMsg->getSignalWavelenght())-1]=true;
    //Se elimina el ACK de liberacion de recursos
    delete(receivedMsg);
    EV << "Elementos en espera por recursos: " << resourceQueue.getLength() << endl;
    if (!resourceQueue.isEmpty()){ //Hay mensajes en espera, se asigna y envia al AI la solicitud
        double resourceBufferTime = 0; //Tiempo en que la solicitud estuvo en espera desde su creación
        int ToS = 0; //Tipo de servicio de la solicitud
        bool flagRequest=true;
        bool flagBuffer=true;
        double waitTime=0;
        resourceRequest *bufferMsg = nullptr;
        do{
            //Se comprueba si las iteraciones provocan que el buffer se vacíe
            if(resourceQueue.isEmpty()){ //Ya no hay mensajes en espera
                flagBuffer = false;
                flagRequest = false;
            }else{
                //Se extrae la siguiente solicitud en cola
                processedRequests++;
                resourceRequest *bufferRequest=(resourceRequest *) resourceQueue.pop();
                resourceBufferTime = simTime().dbl()-(bufferRequest->getGenerationTime());
                ToS = bufferRequest->getTypeOfService();
                switch(ToS){
                    case 1:
                        if(resourceBufferTime > resourceTolerationTime1){
                            bufferRequest->setDestinationNode( bufferRequest->getSourceNode());
                            bufferRequest->setTypeOfMsg(3);
                            requestRejectCont[0]++;
                            send(bufferRequest, "outToNetwork");
                        } else{
                            waitTime = simTime().dbl()-(bufferRequest->getResourceDelay());
                            requestWaitTimeWavelength[0] = requestWaitTimeWavelength[0] + waitTime;
                            resourceDelayedMessages[0]++;
                            flagBuffer = false;
                            bufferMsg = bufferRequest;
                        }
                        break;
                    case 2:
                        if(resourceBufferTime > resourceTolerationTime2){
                            bufferRequest->setDestinationNode( bufferRequest->getSourceNode());
                            bufferRequest->setTypeOfMsg(3);
                            requestRejectCont[1]++;
                            send(bufferRequest, "outToNetwork");
                        } else{
                            waitTime = simTime().dbl()-(bufferRequest->getResourceDelay());
                            requestWaitTimeWavelength[1] = requestWaitTimeWavelength[1] + waitTime;
                            resourceDelayedMessages[1]++;
                            flagBuffer = false;
                            bufferMsg = bufferRequest;
                        }
                        break;
                    case 3:
                        if(resourceBufferTime > resourceTolerationTime3){
                            bufferRequest->setDestinationNode( bufferRequest->getSourceNode());
                            bufferRequest->setTypeOfMsg(3);
                            requestRejectCont[2]++;
                            send(bufferRequest, "outToNetwork");
                        } else{
                            waitTime = simTime().dbl()-(bufferRequest->getResourceDelay());
                            requestWaitTimeWavelength[2] = requestWaitTimeWavelength[2] + waitTime;
                            resourceDelayedMessages[2]++;
                            flagBuffer = false;
                            bufferMsg = bufferRequest;
                        }
                        break;
                }
            }
        }while( flagBuffer == true );

        if ( flagRequest == true ){
            EV << "Se extrae el siguiente mensaje en espera y se envia la resourceRequest al AI\n";
            //Tiempo total de espera por asignacion de recurso
            //Tiempo total acumulado de espera por asignacion de recurso
            requestWaitTimeWavelength_Flag=true;
            //Se asigna la longitud de onda a la solicitud
            int assignedWavelength=firstFit();
            bufferMsg->setSignalWavelenght(assignedWavelength);
            //Se guarda el origen de la solicitud
            sourceNodeRequest[assignedWavelength-1]=bufferMsg->getSourceNode();
            //Se envia el mensaje al AI
            EV << "Tiempo de espera por recurso: " << waitTime << "s\n";
            handleAI(bufferMsg);
        } else{
            //No hay más mensajes en espera
        }
    }
}

void Message_Processor::handleConfigurationMessage(configurationMessage *receivedMsg){ //Llegan mensajes de configuracion desde el AI
    int wavelengthIndex=(receivedMsg->getSignalWavelenght())-1;
    if(nodeConfigurationCount[wavelengthIndex]==0){ //Si es el primer mensaje de configuracion para determinada solicitud
        EV<<"=================Llegan mensajes de configuracion desde el AI=================\n";
        EV<< "Se establece el numero de nodos a configurar en: " << receivedMsg->getNumberOfNodes() << "\n";
        nodeConfigurationQuantity[wavelengthIndex]=receivedMsg->getNumberOfNodes();
        delayExecuteAI=delayExecuteAI+(receivedMsg->getDelayAI());
    }
    if(nodeConfigurationCount[wavelengthIndex]<nodeConfigurationQuantity[wavelengthIndex]){ //Almacena todos los mensajes de cofiguracion antes de enviarlos
        //Realiza un conteo de los mensajes de configuracion recibidos
        nodeConfigurationCount[wavelengthIndex]=nodeConfigurationCount[wavelengthIndex]+1;
        //Inserta los mensajes de configuracion en el buffer correspondiente a la longitud de onda
        configurationMsg[wavelengthIndex].insert(receivedMsg);
    }
    if(nodeConfigurationCount[wavelengthIndex]==nodeConfigurationQuantity[wavelengthIndex]){ //Si se han almacenado todos los mensajes de configuracion requeridos
        EV << "Se tienen todos los mensajes de configuracion correspondientes a la longitud de onda " << receivedMsg->getSignalWavelenght() << "\n";
        if(requestWaitTimeIA_Flag==false){ //Se calcula el tiempo de espera por manejo de solicitud por el AI
            double waitTime=simTime().dbl()-requestWaitTimeIA_S;
            requestWaitTimeIA_T=requestWaitTimeIA_T+waitTime;
        }
        while(!configurationMsg[wavelengthIndex].isEmpty()){ //Se extraen y envian los mensajes de configuracion
            configurationMessage *bufferMsg;
            bufferMsg=(configurationMessage *) configurationMsg[wavelengthIndex].pop();
            EV <<"Se envia una configuracion a " << bufferMsg->getDestinationNode() <<"\n";
            double delayAI = bufferMsg->getDelayAI();
            sendDelayed(bufferMsg, delayAI, "outToNetwork");
        }
        if(!AIQueue.isEmpty()){ //Se revisa la lista de espera por manejo del AI
            EV<<"Se tienen solicitudes pendientes por pasar al AI, se reenvía la solicitud\n";
            resourceRequest *resourceReq=(resourceRequest *) AIQueue.pop();
            requestWaitTimeIA_S=simTime().dbl();
            sendDelayed(resourceReq, additionalDelay, "outToIA");
        }else{
            availableIA=true;
            requestWaitTimeIA_Flag=true;
        }
    }
}

void Message_Processor::handleConfigurationACK(configurationMessage *receivedMsg){
    int wavelengthIndex=(receivedMsg->getSignalWavelenght())-1;
    //Se maneja un contador para el numero de ACKs recibidos para una longitud de onda
    nodeConfigurationQuantity[wavelengthIndex]=nodeConfigurationQuantity[wavelengthIndex]-1;
    if(nodeConfigurationQuantity[wavelengthIndex]==0){ //Se reciben todos los ACKs relacionados a una wavelength
        //Se genera un ACK de solicitud de recursos
        resourceRequest *requestResponse=new resourceRequest("resourceACK");
        requestResponse->setTypeOfMsg(2);
        requestResponse->setSourceNode(0);
        requestResponse->setDestinationNode(sourceNodeRequest[wavelengthIndex]);
        requestResponse->setSignalWavelenght(wavelengthIndex+1);
        requestResponse->setBurstID(receivedMsg->getBurstID());
        requestResponse->setGenerationTime(receivedMsg->getRequestGenerationDelay());

        configurationOpticalPath=configurationOpticalPath+(simTime().dbl()-receivedMsg->getConfigurationDelay());
        EV<< "=================Se envia un ACK de solicitud de recursos hacia el nodo" << sourceNodeRequest[wavelengthIndex] << "=================\n";
        EV<< "Longitud de onda asignada: " << requestResponse->getSignalWavelenght() << "\n";
        send(requestResponse, "outToNetwork");
        // Se reinician los contadores e indicadores
        nodeConfigurationCount[wavelengthIndex]=0;
        nodeConfigurationQuantity[wavelengthIndex]=0;
        sourceNodeRequest[wavelengthIndex]=0;
    }
    //Se elimina el mensaje para liberar recursos
    delete(receivedMsg);
}

void Message_Processor::finish(){
    EV << "=================Manejo de los recursos en el controlador=================\n";
    EV << "Tiempo total de la simulacion: " << simTime().dbl() << "\n";
    EV << "Total de solicitudes de recursos: " << requestCont << "\n";
    EV << "Total de solicitudes de recursos procesadas: " << processedRequests << "\n";
    EV << "Total de solicitudes de recursos rechazadas:\n";
    EV << "     Clase 1: " << requestRejectCont[0] << "\n";
    EV << "     Clase 2: " << requestRejectCont[1] << "\n";
    EV << "     Clase 3: " << requestRejectCont[2] << "\n";
    EV << "Tiempo promedio de espera para recursos:\n";
    EV << "     Clase 1: " << requestWaitTimeWavelength[0]/resourceDelayedMessages[0] << "s\n";
    EV << "     Clase 2: " << requestWaitTimeWavelength[1]/resourceDelayedMessages[1] << "s\n";
    EV << "     Clase 3: " << requestWaitTimeWavelength[2]/resourceDelayedMessages[2] << "s\n";
    EV << "Tiempo promedio de configuracion del camino optico: " << configurationOpticalPath/processedRequests << "\n";
    //EV << "Tiempo total de ocupacion de las longitudes de onda:\n";
    //for(int i=0; i<numWavelengths; i++){
        //EV << "[ " << i+1 << "]: " << wavelengthUsageTime[i] << "s\n";
    //}
}

class Intelligent_Agent : public cSimpleModule{
    private:
        std::string priorityRoutes[14][14]; //Variable usada para almacenar rutas prioritarias
        std::map<std::string, int> nodeMap; //Mapa para almacenar una relacion nodo-numero
        int signalWavelenght;               //Longitud de onda asignada a la solicitud
        int burstID;                        //Burst ID de la solicitud
        int handledRequests;                //Numero de solicitudes manejadas por el AI
        double delayAI;                     //Delay inducido por el AI
        double requestDelay;
        double processDelay;                //Tiempo de procesamiento del AI
        cQueue configurationBuffer;         //Buffer para guardar los mensajes de configuracion hasta tener el delay
        bool savedRoute;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void finish() override;
        virtual std::string executeIA(int sourceNode, int destinationNode, int msgClass);
        virtual void handlePythonOutput(std::string result, int sourceNode, int destinationNode, int msgClass);
        virtual void processRoute(std::string generatedRoute, bool SavedRoute);
        virtual void popOutConfigurationMsg();
}; Define_Module(Intelligent_Agent);

void Intelligent_Agent::initialize(){
    int numNodes = 14;
    //Inicializar la matriz de rutas
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            priorityRoutes[i][j] = "";
        }
    }
    //Inicializar el mapeo de nodos
    for (int i = 1; i <= numNodes; ++i) {
        std::string nodeName = "Nodo" + std::to_string(i); // Crear el nombre del nodo, e.g., "Nodo1"
        nodeMap[nodeName] = i; // Asociar el nodo con su número
    }
    //
    savedRoute=false;
    processDelay=0;
    delayAI=0;
    handledRequests=0;
    signalWavelenght=0;
    requestDelay=0;
    burstID=0;
}

void Intelligent_Agent::handleMessage(cMessage *msg){
    //Solo recibe mensajes de solicitud de recursos, y entrega mensajes de configuracion
    EV << "Llega un mensaje al IA\n";
    resourceRequest *receivedMsg = check_and_cast<resourceRequest *>(msg);
    if (receivedMsg->getTypeOfMsg()==1){
        int msgSourceNode=receivedMsg->getSourceNode();
        int msgDestinationNode=receivedMsg->getDestinationNode();
        int typeOfMsg=receivedMsg->getTypeOfMsg();
        int typeOfService=receivedMsg->getTypeOfService();
        signalWavelenght=receivedMsg->getSignalWavelenght();
        burstID=receivedMsg->getBurstID();
        requestDelay=receivedMsg->getGenerationTime();

        EV << "El AI recibe una solicitud de recursos con la siguiente informacion: \n";
        EV << "Nodo origen: " << msgSourceNode << "\n";
        EV << "Nodo destino: " << msgDestinationNode << "\n";
        EV << "Clase de servicio: " << typeOfService << "\n";
        EV << "Longitud de onda asignada: " << signalWavelenght << "\n";

        if(typeOfMsg==1){ //Se trata una solicitud prioritaria (Clase 1)
            if(priorityRoutes[msgSourceNode-1][msgDestinationNode-1]!=""){ //Existe una ruta almacenada
                EV << "Se tiene guardada la siguiente ruta prioritaria para la solicitud\n";
                EV << priorityRoutes[msgSourceNode-1][msgDestinationNode-1] << "\n";
                savedRoute=true;
                processRoute(priorityRoutes[msgSourceNode-1][msgDestinationNode-1], savedRoute);
            } else{ //No existe una ruta almacenada
                EV << "Se tiene una solicitud prioritaria, pero no existe una ruta almacenada\n";
                //El mensaje tiene prioridad, pero no hay una ruta almacenada, se ejecuta el AI
                std::string result=executeIA(msgSourceNode, msgDestinationNode, typeOfMsg);
                //Se procesa la informacion obtenida por el AI
                handlePythonOutput(result, msgSourceNode, msgDestinationNode, typeOfMsg);
            }
        } else{
            //Se llama al AI
            std::string result=executeIA(msgSourceNode, msgDestinationNode, typeOfMsg);
            //Se procesa la informacion obtenida por el AI
            handlePythonOutput(result, msgSourceNode, msgDestinationNode, typeOfMsg);
        }

        delete receivedMsg;

    }
}

std::string Intelligent_Agent::executeIA(int sourceNode, int destinationNode, int msgClass){
    //Crear una funcion para ejecutar el python
    //Construir la cadena de comando con los argumentos
    std::stringstream command;

    //Comando AI
    //command << "python pythonIA.py " << sourceNode << " " << destinationNode << " " << msgClass;
    //Comando Dijkstra
    command << "python Dijkstra.py " << sourceNode << " " << destinationNode << " " << msgClass;

    //Ejecutar el script Python
    FILE *pipe = popen(command.str().c_str(), "r");
    if (!pipe) {
        EV << "Falla en ejecucion del codigo de python\n";
    }

    //Capturar la salida del script Python
    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);

    // Limpiar la salida (eliminar espacios adicionales o saltos de línea)
    result.erase(result.find_last_not_of(" \n\r\t") + 1);

    return(result);
}

void Intelligent_Agent::handlePythonOutput(std::string result, int sourceNode, int destinationNode, int msgClass){
    std::istringstream stream(result);
    std::string line;
    bool flagRO=true;   //Solo se lee una ruta optima
    bool flagR=true;    //Solo se lee una ruta
    bool flagD=true;    //Solo se lee un delay

    //Funcion para distinguir a que corresponde la cadena
    while (std::getline(stream, line)) {

        // Procesar cada línea según su contenido
        if ((line.find("Ruta Optima:") != std::string::npos)&&(flagRO==true)) { //Se identifica una ruta prioritaria y se almacena
            EV << line << "\n";
            //Se almacena la ruta optima obtenida como ruta prioritaria
            priorityRoutes[sourceNode-1][destinationNode-1]=line;
            //Si el mensaje es clase 1, se ejecuta el procesamiento de la ruta, puesto que no habria almacenada una ruta
            if(msgClass==1){
                processRoute(line, savedRoute);
            }
            //Se inhabilita el procesar mas rutas optimas
            flagRO=false;
        } else if ((line.find("Ruta:") != std::string::npos)&&(flagR==true)) { //Se obtiene del AI una ruta a usar
            EV << line << "\n";
            if(msgClass==1){
                EV << "No se consideran rutas a usar en un mensaje clase 1\n";
            } else{
                processRoute(line, savedRoute);
            }
            flagR=false;
        } else if ((line.find("Delay:") != std::string::npos)&&(flagD==true)) { //Se identifica el delay
            EV << line << "\n";
            //Se debe transformar el delay a solo el valor
            processRoute(line, savedRoute);
            flagD=false;
        } else {
            EV << "Linea desconocida: " << line << "\n";
            // Procesar cualquier línea adicional que no encaje en las anteriores
        }
    }

}

void Intelligent_Agent::processRoute(std::string generatedRoute, bool savedRoute){
    // Identificar el tipo de cadena (prefijo antes de ':')
    size_t colonPos = generatedRoute.find(':');
    if (colonPos == std::string::npos) {
        std::cerr << "Cadena inválida, no se encontró ':'.\n";
        return;
    }

    std::string routeType = generatedRoute.substr(0, colonPos); // Ruta, Ruta Optima, Delay
    std::string data = generatedRoute.substr(colonPos + 1); // Contenido después de ':'
    data.erase(0, data.find_first_not_of(" \t\n\r")); // Quitar espacios iniciales
    data.erase(data.find_last_not_of(" \t\n\r") + 1); // Quitar espacios finales

    if (routeType == "Ruta" || routeType == "Ruta Optima") {
        //Reemplazar nodoMap por nodeMap
        // Separar subrutas por ';'
        EV << "Se procesa una ruta para generar los mensajes de configuracion\n";
        std::vector<std::vector<int>> Nodes;
        std::istringstream routeStream(data);
        std::string subroute;

        while (std::getline(routeStream, subroute, ';')) {
            // Limpiar subruta y quitar corchetes
            subroute.erase(0, subroute.find_first_not_of(" \t\n\r"));
            subroute.erase(subroute.find_last_not_of(" \t\n\r") + 1);
            if (subroute.front() == '[' && subroute.back() == ']') {
                subroute = subroute.substr(1, subroute.length() - 2); // Eliminar "[" y "]"
            }

            std::vector<int> node;
            std::istringstream subrouteStream(subroute);
            std::string element;

            while (std::getline(subrouteStream, element, ',')) {
                element.erase(0, element.find_first_not_of(" \t\n\r")); // Limpiar
                element.erase(element.find_last_not_of(" \t\n\r") + 1);

                // Reemplazar nombres por enteros si están en el mapa
                if (nodeMap.find(element) != nodeMap.end()) {
                    node.push_back(nodeMap[element]);
                } else {
                    try {
                        node.push_back(std::stoi(element));
                    } catch (const std::invalid_argument &e) {
                        std::cerr << "Elemento inválido en la subruta: " << element << "\n";
                        return;
                    }
                }
            }
            if (node.size() == 3) {
                Nodes.push_back(node);
            } else {
                std::cerr << "Subruta mal formada: " << subroute << "\n";
            }
        }
        // Procesar el resultado
        int inputGate;
        int nodeID;
        int outputGate;
        EV << "Ruta generada: " << generatedRoute << "\n";
        for (size_t i = 0; i < Nodes.size(); ++i) {
            inputGate=Nodes[i][0];
            nodeID=Nodes[i][1];
            outputGate=Nodes[i][2];

            //Crear los mensajes
            configurationMessage *configMsg=new configurationMessage("configMSG");
            configMsg->setTypeOfMsg(1);
            configMsg->setDestinationNode(nodeID);
            configMsg->setInputTrafficPort(inputGate);
            configMsg->setOutputTrafficPort(outputGate);
            configMsg->setNumberOfNodes(Nodes.size());
            configMsg->setSignalWavelenght(signalWavelenght);
            configMsg->setBurstID(burstID);
            configMsg->setRequestGenerationDelay(requestDelay);
            configMsg->setConfigurationDelay(simTime().dbl());
            configurationBuffer.insert(configMsg);

        }
        if(savedRoute==true){
            processDelay=0;
            popOutConfigurationMsg();
        }
    } else if (routeType == "Delay") {
        try {
            double delay = std::stod(data);
            delay *= 1e-3; // Convertir a milisegundos
            EV << std::fixed << std::setprecision(6); // Formato de salida
            EV << "Delay en segundos: " << delay << "\n";
            processDelay=delay;
            handledRequests++;
            delayAI=delayAI+processDelay;
            popOutConfigurationMsg();

        } catch (const std::invalid_argument &e) {
            std::cerr << "Error al convertir Delay a double: " << data << "\n";
        }
    } else {
        std::cerr << "Tipo de cadena no reconocido: " << routeType << "\n";
    }
}

void Intelligent_Agent::popOutConfigurationMsg(){
    while (!configurationBuffer.isEmpty()){
        configurationMessage *bufferMsg=(configurationMessage *)configurationBuffer.pop(); //Extrae el mensaje del buffer
        bufferMsg->setDelayAI(processDelay);
        send(bufferMsg, "outIA");
    }
    signalWavelenght=0;
    processDelay=0;
    burstID=0;
    savedRoute=false;
}

void Intelligent_Agent::finish(){
    EV << "======================Estadisticas del agente inteligente======================\n";
    EV << "Tiempo promedio de ejecución del AI/Algoritmo: " << delayAI/handledRequests << "\n";
}
