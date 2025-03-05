// Universidad del Cauca
// "AGENTE INTELIGENTE PARA LA ASIGNACION DE RUTAS EN UNA ARQUITECTURA SD-EON"
// Trabajo de grado
// Autores:	David Santiago Pismag Imbachi
//			Andres Fernando Medina Pino
import ned.DelayChannel;
import ned.IdealChannel;


simple Source
{
    parameters:
        @display("i=block/source");
        int messagesToSend = default(20);
        double messageTimeGeneration = default(1e-3);
        int numberOfNodes = default(0);
    gates:
        output outSource;
}

simple Sink
{
    parameters:
        @display("i=block/sink");
        int numberOfNodes = default(0);
    gates:
        input inSink;
}

module Host
{
    parameters:
        @display("i=device/pc2;bgb=151.84001,48.88");
        int hostID = default(0);
    gates:
        input inHost;
        output outHost;
    submodules:
        source: Source {
            @display("p=52.52,18.2");
        }
        sink: Sink {
            @display("p=95.68,18.2");
        }
    connections:
        source.outSource --> IdealChannel --> outHost;
        inHost --> IdealChannel --> sink.inSink;
}

simple Classifier
{
    parameters:
        @display("i=block/fork");
        double processDelay = default(1e-6);
    gates:
        input inClassifier;
        output outClassifier[];
}

simple MUX
{
    parameters:
        @display("i=block/rightarrow");
    gates:
        input inMux[];
        output outMux;
}

simple Buffer
{
    parameters:
        @display("i=block/buffer");
        int msgLimitClass = default(100);
        int headerLength = default(0);
        double processDelay = default(2e-6);
        double timeLimitClass = default(100e-3);
    gates:
        input inBuffer;
        output outBuffer;
}

module OBS_Conformer
{
    parameters:
        @display("i=msg/packet;bgb=401,266");
    gates:
        input inOBSConformer;
        output outOBSConformer;
    submodules:
        CoS_Classifier: Classifier {
            @display("p=71,127");
        }
        bufferMUX: MUX {
            @display("p=330,127");
        }
        bufferClass1: Buffer {
            @display("p=199,45");
        }
        bufferClass2: Buffer {
            @display("p=199,127");
        }
        bufferClass3: Buffer {
            @display("p=199,213");
        }
    connections:
        inOBSConformer --> IdealChannel --> CoS_Classifier.inClassifier;
        CoS_Classifier.outClassifier++ --> IdealChannel --> bufferClass1.inBuffer;
        CoS_Classifier.outClassifier++ --> IdealChannel --> bufferClass2.inBuffer;
        CoS_Classifier.outClassifier++ --> IdealChannel --> bufferClass3.inBuffer;
        bufferClass1.outBuffer --> IdealChannel --> bufferMUX.inMux++;
        bufferClass2.outBuffer --> IdealChannel --> bufferMUX.inMux++;
        bufferClass3.outBuffer --> IdealChannel --> bufferMUX.inMux++;
        bufferMUX.outMux --> IdealChannel --> outOBSConformer;
}

module Conformer
{
    parameters:
        @display("i=msg/packet;bgb=351,698");
    gates:
        input inConformer[];
        output outConformer;
    submodules:
        conformer1: OBS_Conformer {
            @display("p=85,88");
        }
        conformer2: OBS_Conformer {
            @display("p=85,128");
        }
        conformer3: OBS_Conformer {
            @display("p=85,168");
        }
        conformer4: OBS_Conformer {
            @display("p=85,208");
        }
        conformer5: OBS_Conformer {
            @display("p=85,248");
        }
        conformer6: OBS_Conformer {
            @display("p=85,288");
        }
        conformer7: OBS_Conformer {
            @display("p=85,328");
        }
        conformer8: OBS_Conformer {
            @display("p=85,368");
        }
        conformer9: OBS_Conformer {
            @display("p=85,408");
        }
        conformer10: OBS_Conformer {
            @display("p=85,448");
        }
        conformer11: OBS_Conformer {
            @display("p=85,488");
        }
        conformer12: OBS_Conformer {
            @display("p=85,528");
        }
        conformer13: OBS_Conformer {
            @display("p=85,568");
        }
        conformer14: OBS_Conformer {
            @display("p=85,608");
        }
        ConformerMUX: MUX {
            @display("p=215,369");
        }
    connections:
        inConformer++ --> IdealChannel --> conformer1.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer2.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer3.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer4.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer5.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer6.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer7.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer8.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer9.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer10.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer11.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer12.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer13.inOBSConformer;
        inConformer++ --> IdealChannel --> conformer14.inOBSConformer;
        conformer1.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer2.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer3.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer4.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer5.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer6.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer7.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer8.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer9.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer10.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer11.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer12.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer13.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        conformer14.outOBSConformer --> IdealChannel --> ConformerMUX.inMux++;
        ConformerMUX.outMux --> IdealChannel --> outConformer;
}

simple OEO_Conversor
{
    parameters:
        @display("i=block/classifier2");
        double processDelay = default(2e-6);
    gates:
        input inOEO;
        output outOEO;
}

simple Sender_Buffer
{
    parameters:
        @display("i=block/buffer");
        double processDelay = default(2e-6);
    gates:
        input inSenderBuffer;
        output outSenderBuffer;
        input inFromControlUnit;
        input inFromDeconformer;
        output outToControlUnit;
}

module Sender
{
    parameters:
        @display("i=block/departure");
    gates:
        input inSender;
        output outSender;
        input inFromControlUnit;
        input inFromDeconformer;
        output outToControlUnit;
    submodules:
        buffer: Sender_Buffer {
            @display("p=96,108");
        }
        OEO: OEO_Conversor {
            @display("p=213,108");
        }
    connections:
        inSender --> IdealChannel --> buffer.inSenderBuffer;
        buffer.outSenderBuffer --> IdealChannel --> OEO.inOEO;
        OEO.outOEO --> IdealChannel --> outSender;
        buffer.outToControlUnit --> IdealChannel --> outToControlUnit;
        inFromControlUnit --> IdealChannel --> buffer.inFromControlUnit;
        inFromDeconformer --> IdealChannel --> buffer.inFromDeconformer;
}

module Assembler
{
    parameters:
        @display("bgb=436.355,193.06001;i=block/segm");
    gates:
        input inAssembler;
        output outAssembler;
        input inFromControlUnit;
        input inFromDeconformer;
        output outToControlUnit;
    submodules:
        Destination_Classifier: Classifier {
            @display("p=84.549995,89.299995");
        }
        Burst_Conformer: Conformer {
            @display("p=215.65,88.35");
        }
        sender: Sender {
            @display("p=347.70502,88.65");
        }
    connections:
        inAssembler --> IdealChannel --> Destination_Classifier.inClassifier;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Destination_Classifier.outClassifier++ --> IdealChannel --> Burst_Conformer.inConformer++;
        Burst_Conformer.outConformer --> IdealChannel --> sender.inSender;
        sender.outSender --> IdealChannel --> outAssembler;
        inFromControlUnit --> IdealChannel --> sender.inFromControlUnit;
        sender.outToControlUnit --> IdealChannel --> outToControlUnit;
        inFromDeconformer --> IdealChannel --> sender.inFromDeconformer;
}

simple Deconformer
{
    parameters:
        @display("i=block/boundedqueue");
        double processDelay = default(2e-6);
    gates:
        input inDeconformer;
        output outDeconformer;
        output outToAssembler;
}

module Disassembler
{
    parameters:
        @display("i=block/boundedqueue;bgb=306,194");
    gates:
        input inDisassembler;
        output outDisassembler;
        output outToAssembler;
    submodules:
        deconformer: Deconformer {
            @display("p=84,89");
        }
        OEO: OEO_Conversor {
            @display("p=217,89");
        }
    connections:
        deconformer.outDeconformer --> IdealChannel --> outDisassembler;
        inDisassembler --> IdealChannel --> OEO.inOEO;
        OEO.outOEO --> IdealChannel --> deconformer.inDeconformer;
        deconformer.outToAssembler --> IdealChannel --> outToAssembler;
}

module Edge_Node
{
    parameters:
        @display("i=abstract/opticalswitch");
    gates:
        input inFromHost;
        input inToDisassembler;
        output outAssembler;
        output outToHost;
        input inFromCoreControlUnit;
        output outToCoreControlUnit;
    submodules:
        assembler: Assembler {
            @display("p=94,71");
        }
        disassembler: Disassembler {
            @display("p=94,164");
        }
    connections:

        inFromHost --> IdealChannel --> assembler.inAssembler;
        disassembler.outDisassembler --> IdealChannel --> outToHost;
        inFromCoreControlUnit --> IdealChannel --> assembler.inFromControlUnit;
        inToDisassembler --> IdealChannel --> disassembler.inDisassembler;
        assembler.outAssembler --> IdealChannel --> outAssembler;
        assembler.outToControlUnit --> IdealChannel --> outToCoreControlUnit;
        disassembler.outToAssembler --> IdealChannel --> assembler.inFromDeconformer;
}

simple Core_CU
{
    parameters:
        @display("i=device/clock");
        double processDelay = default(2e-6);
    gates:
        input inFromEdgeSender;
        output outToEdgeSender;
        input inFromController;
        output outToController;
        input inFromSwitch;
        output outToSwitch;
}

simple Optical_Switch
{
    parameters:
        @display("i=abstract/switch");
        int numWavelengths = default(1);
        double processDelay = default(2e-6);
        double lossProbability = default(0);
        double lossDelay = default(100e-6);
    gates:
        input inTraffic[];
        output outTraffic[];
        input inFromCU;
        output outToCU;
}

module Core_Node
{
    parameters:
        @display("i=abstract/opticalrouter;bgb=325,314");
    gates:
        input inFromEdgeSender;
        output outToEdgeSender;
        input inTraffic[];
        output outTraffic[];
        input inFromController;
        output outToController;
    submodules:
        optical_Switch: Optical_Switch {
            @display("p=160,228");
        }
        core_CU: Core_CU {
            @display("p=160,69");
        }
        inOEO: OEO_Conversor {
            @display("p=44,117");
        }
        outOEO: OEO_Conversor {
            @display("p=276,117");
        }
    connections:
        inFromController --> IdealChannel --> inOEO.inOEO;
        outOEO.outOEO --> IdealChannel --> outToController;
        inOEO.outOEO --> IdealChannel --> core_CU.inFromController;
        core_CU.outToController --> IdealChannel --> outOEO.inOEO;
        inFromEdgeSender --> IdealChannel --> core_CU.inFromEdgeSender;
        core_CU.outToEdgeSender --> IdealChannel --> outToEdgeSender;
        core_CU.outToSwitch --> IdealChannel --> optical_Switch.inFromCU;
        optical_Switch.outToCU --> IdealChannel --> core_CU.inFromSwitch;
        inTraffic++ --> IdealChannel --> optical_Switch.inTraffic++;	//Entrada del trafico del Host
        optical_Switch.outTraffic++ --> IdealChannel --> outTraffic++;	//Salida del trafico hacia Host
        //Entradas de trafico al nodo
        inTraffic++ --> IdealChannel --> optical_Switch.inTraffic++;
        inTraffic++ --> IdealChannel --> optical_Switch.inTraffic++;
        inTraffic++ --> IdealChannel --> optical_Switch.inTraffic++;
        inTraffic++ --> IdealChannel --> optical_Switch.inTraffic++;
        //Salidas de trafico hacia la red
        optical_Switch.outTraffic++ --> IdealChannel --> outTraffic++;
        optical_Switch.outTraffic++ --> IdealChannel --> outTraffic++;
        optical_Switch.outTraffic++ --> IdealChannel --> outTraffic++;
        optical_Switch.outTraffic++ --> IdealChannel --> outTraffic++;
}

module OBS_Node
{
    parameters:
        int nodeID = default(0);
        @display("i=device/mainframe");
    gates:
        input inFromHost;
        output outToHost;
        input inFromNetwork[];
        output outToNetwork[];
        input inFromController;
        output outToController;
    submodules:
        core_Node: Core_Node {
            @display("p=242,126");
        }
        edge_Node: Edge_Node {
            @display("p=102,126");
        }
    connections:
        inFromHost --> IdealChannel --> edge_Node.inFromHost;
        edge_Node.outToHost --> IdealChannel --> outToHost;
        edge_Node.outToCoreControlUnit --> IdealChannel --> core_Node.inFromEdgeSender;
        core_Node.outToEdgeSender --> IdealChannel --> edge_Node.inFromCoreControlUnit;
        core_Node.outToController --> IdealChannel --> outToController;
        inFromController --> IdealChannel --> core_Node.inFromController;
        //Interfaces del host
        edge_Node.outAssembler --> IdealChannel --> core_Node.inTraffic++; //Salida del host (gate 0)
        core_Node.outTraffic++ --> IdealChannel --> edge_Node.inToDisassembler; //Entrada al host (gate 0)
        //Salidas de trafico en el nodo
        core_Node.outTraffic++ --> IdealChannel --> outToNetwork++;
        core_Node.outTraffic++ --> IdealChannel --> outToNetwork++;
        core_Node.outTraffic++ --> IdealChannel --> outToNetwork++;
        core_Node.outTraffic++ --> IdealChannel --> outToNetwork++;
        //Entradas de trafico en el nodo
        inFromNetwork++ --> IdealChannel --> core_Node.inTraffic++;
        inFromNetwork++ --> IdealChannel --> core_Node.inTraffic++;
        inFromNetwork++ --> IdealChannel --> core_Node.inTraffic++;
        inFromNetwork++ --> IdealChannel --> core_Node.inTraffic++;
}

simple Dump
{
    @display("i=block/bucket");
    gates:
        input inDump;
        output outDump;
}

simple Message_Processor
{
    parameters:
        @display("i=msg/mail");
        int numWavelengths = default(1);
        double processDelay = default(2e-6);
        double timeLimitProcess = default(100e-3);
        double resourseTolerationTime1 = default(10e-3);
        double resourseTolerationTime2 = default(10e-3);
        double resourseTolerationTime3 = default(10e-3);
    gates:
        input inFromNetwork;
        output outToNetwork;
        input inFromIA;
        output outToIA;
}

simple Intelligent_Agent
{
    parameters:
        @display("i=block/cogwheel");
        double processDelay = default(2e-6);
    gates:
        input inIA;
        output outIA;
}

module Controller_CU
{
    parameters:
        @display("i=device/clock");
    gates:
        input inController;
        output outController;
    submodules:
        message_Processor: Message_Processor {
            @display("p=130,149");
        }
        intelligent_Agent: Intelligent_Agent {
            @display("p=130,49");
        }
    connections:
        message_Processor.outToIA --> IdealChannel --> intelligent_Agent.inIA;
        intelligent_Agent.outIA --> IdealChannel --> message_Processor.inFromIA;
        message_Processor.outToNetwork --> IdealChannel --> outController;
        inController --> IdealChannel --> message_Processor.inFromNetwork;
}

simple Controller_Classifier
{
    parameters:
        @display("i=abstract/dispatcher");
        double processDelay = default(2e-6);
    gates:
        input inClassifier;
        output outClassifier[];
}

module Controller
{
    parameters:
        @display("i=device/server;bgb=465,302");
    gates:
        input inController[];
        output outController[];
    submodules:
        inOEO: OEO_Conversor {
            @display("p=67,90");
        }
        outOEO: OEO_Conversor {
            @display("p=385,90");
        }
        controller_CU: Controller_CU {
            @display("p=224,89");
        }
        mux: MUX {
            @display("p=67,196");
        }
        controller_Classifier: Controller_Classifier {
            @display("p=385,196");
        }
    connections:
        inOEO.outOEO --> IdealChannel --> controller_CU.inController;
        controller_CU.outController --> IdealChannel --> outOEO.inOEO;
        mux.outMux --> IdealChannel --> inOEO.inOEO;
        //Compuerta de salida del clasificador
        outOEO.outOEO --> IdealChannel --> controller_Classifier.inClassifier;
        //Compuertas de entrada de los nodos
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        inController++ --> IdealChannel --> mux.inMux++;
        //Compuertas desalida hacia los nodos
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
        controller_Classifier.outClassifier++ --> IdealChannel --> outController++;
}

channel opticalFiber extends ned.DelayChannel
{
    parameters:
        @display("ls=red");
        double distance @unit(m); // distancia en metros
        double speedOfLightFactor = default(0.7); // velocidad de la luz en la fibra como porcentaje de la velocidad de la luz en el vacío
        delay = (distance / (speedOfLightFactor * 3e8m))*1s; // 3e8 m/s es la velocidad de la luz en vacío
}

channel opticalFiberC extends ned.DelayChannel
{
    parameters:
        @display("ls=#004080,1,s");
        double distance @unit(m); // distancia en metros
        double speedOfLightFactor = default(0.7); // velocidad de la luz en la fibra como porcentaje de la velocidad de la luz en el vacío
        delay = (distance / (speedOfLightFactor * 3e8m))*1s; // 3e8 m/s es la velocidad de la luz en vacío
}

network Test_Network
{
    submodules:
        Node1: OBS_Node {
            @display("p=179,166");
            nodeID = 1;
        }
        Node2: OBS_Node {
            @display("p=384,166");
            nodeID = 2;
        }
        Node3: OBS_Node {
            @display("p=179,297");
            nodeID = 3;
        }
        Node4: OBS_Node {
            @display("p=384,297");
            nodeID = 4;
        }
        controller: Controller {
            @display("p=280,41");
        }
        Host1: Host {
            @display("p=55,164");
            hostID = 1;
        }
        Host2: Host {
            @display("p=518,166");
            hostID = 2;
        }
        Host3: Host {
            @display("p=55,297");
            hostID = 3;
        }
        Host4: Host {
            @display("p=518,297");
            hostID = 4;
        }
    connections:
        //Conexiones de los host
        Host1.outHost --> DelayChannel {  delay = 200us; } --> Node1.inFromHost;
        Host2.outHost --> DelayChannel {  delay = 200us; } --> Node2.inFromHost;
        Host3.outHost --> DelayChannel {  delay = 200us; } --> Node3.inFromHost;
        Host4.outHost --> DelayChannel {  delay = 200us; } --> Node4.inFromHost;
        Node1.outToHost --> DelayChannel {  delay = 200us; } --> Host1.inHost;
        Node3.outToHost --> DelayChannel {  delay = 200us; } --> Host3.inHost;
        Node4.outToHost --> DelayChannel {  delay = 200us; } --> Host4.inHost;
        Node2.outToHost --> DelayChannel {  delay = 200us; } --> Host2.inHost;
        //Conexiones de los nodos al controlador
        Node1.outToController --> opticalFiber {  distance = 2000000m; } --> controller.inController++;
        Node2.outToController --> opticalFiber {  distance = 2000000m; } --> controller.inController++;
        Node3.outToController --> opticalFiber {  distance = 2000000m; } --> controller.inController++;
        Node4.outToController --> opticalFiber {  distance = 2000000m; } --> controller.inController++;
        controller.outController++ --> opticalFiber {  distance = 2000000m; } --> Node1.inFromController;
        controller.outController++ --> opticalFiber {  distance = 2000000m; } --> Node2.inFromController;
        controller.outController++ --> opticalFiber {  distance = 2000000m; } --> Node3.inFromController;
        controller.outController++ --> opticalFiber {  distance = 2000000m; } --> Node4.inFromController;
		//Conexiones entre nodos
        Node1.outToNetwork++ --> opticalFiber {  distance = 5000000m; } --> Node2.inFromNetwork++;
        Node2.outToNetwork++ --> opticalFiber {  distance = 5000000m; } --> Node1.inFromNetwork++;
        Node3.outToNetwork++ --> opticalFiber {  distance = 5000000m; } --> Node4.inFromNetwork++;
        Node4.outToNetwork++ --> opticalFiber {  distance = 5000000m; } --> Node3.inFromNetwork++;
        Node1.outToNetwork++ --> opticalFiber {  distance = 5000000m; } --> Node3.inFromNetwork++;
        Node3.outToNetwork++ --> opticalFiber {  distance = 5000000m; } --> Node1.inFromNetwork++;
        Node2.outToNetwork++ --> opticalFiber {  distance = 5000000m; } --> Node4.inFromNetwork++;
        Node4.outToNetwork++ --> opticalFiber {  distance = 5000000m; } --> Node2.inFromNetwork++;
}

network NSFNet_Network_MAN
{
    @display("bgb=754,704;bgi=maps/usa,c");
    submodules:
        Node1: OBS_Node {
            @display("p=66,176");
            nodeID = 1;
        }
        Node2: OBS_Node {
            @display("p=47,330");
            nodeID = 2;
        }
        Node3: OBS_Node {
            @display("p=158,441");
            nodeID = 3;
        }
        Node4: OBS_Node {
            @display("p=192,304");
            nodeID = 4;
        }
        Node5: OBS_Node {
            @display("p=299,389");
            nodeID = 5;
        }
        Node6: OBS_Node {
            @display("p=348,549");
            nodeID = 6;
        }
        Node7: OBS_Node {
            @display("p=406,382");
            nodeID = 7;
        }
        Node8: OBS_Node {
            @display("p=498,343");
            nodeID = 8;
        }
        Node9: OBS_Node {
            @display("p=588,284");
            nodeID = 9;
        }
        Node10: OBS_Node {
            @display("p=614,527");
            nodeID = 10;
        }
        Node11: OBS_Node {
            @display("p=470,236");
            nodeID = 11;
        }
        Node12: OBS_Node {
            @display("p=707,197");
            nodeID = 12;
        }
        Node13: OBS_Node {
            @display("p=633,350");
            nodeID = 13;
        }
        Node14: OBS_Node {
            @display("p=627,428");
            nodeID = 14;
        }
        controller: Controller {
            @display("p=486,29");
        }
        Host1: Host {
            @display("p=18,125");
            hostID = 1;
        }
        Host2: Host {
            @display("p=18,402");
            hostID = 2;
        }
        Host3: Host {
            @display("p=148,510");
            hostID = 3;
        }
        Host4: Host {
            @display("p=176,236");
            hostID = 4;
        }
        Host5: Host {
            @display("p=243,428");
            hostID = 5;
        }
        Host6: Host {
            @display("p=282,566");
            hostID = 6;
        }
        Host7: Host {
            @display("p=452,441");
            hostID = 7;
        }
        Host8: Host {
            @display("p=542,402");
            hostID = 8;
        }
        Host9: Host {
            @display("p=643,284");
            hostID = 9;
        }
        Host10: Host {
            @display("p=559,576");
            hostID = 10;
        }
        Host11: Host {
            @display("p=425,197");
            hostID = 11;
        }
        Host12: Host {
            @display("p=726,137");
            hostID = 12;
        }
        Host13: Host {
            @display("p=697,350");
            hostID = 13;
        }
        Host14: Host {
            @display("p=697,455");
            hostID = 14;
        }
    connections:
        //Conexiones entre nodos segun la topologia del trabajo de grado
        //Nodo1
        Host1.outHost --> opticalFiber {  distance = 200m; } --> Node1.inFromHost;
        Node1.outToHost --> opticalFiber {  distance = 200m; } --> Host1.inHost;
        Node1.outToController --> opticalFiberC {  distance = 630000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 630000m; } --> Node1.inFromController;
        Node1.outToNetwork++ --> opticalFiber {  distance = 210000m; } --> Node2.inFromNetwork++;
        Node1.outToNetwork++ --> opticalFiber {  distance = 300000m; } --> Node3.inFromNetwork++;
        Node1.outToNetwork++ --> opticalFiber {  distance = 480000m; } --> Node8.inFromNetwork++;
        Node1.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node1.inFromNetwork++;
        //Nodo2
        Host2.outHost --> opticalFiber {  distance = 200m; } --> Node2.inFromHost;
        Node2.outToHost --> opticalFiber {  distance = 200m; } --> Host2.inHost;
        Node2.outToController --> opticalFiberC {  distance = 390000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 390000m; } --> Node2.inFromController;
        Node2.outToNetwork++ --> opticalFiber {  distance = 210000m; } --> Node1.inFromNetwork++;
        Node2.outToNetwork++ --> opticalFiber {  distance = 150000m; } --> Node4.inFromNetwork++;
        Node2.outToNetwork++ --> opticalFiber {  distance = 120000m; } --> Node3.inFromNetwork++;
        Node2.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node2.inFromNetwork++;
        //Nodo3
        Host3.outHost --> opticalFiber {  distance = 200m; } --> Node3.inFromHost;
        Node3.outToHost --> opticalFiber {  distance = 200m; } --> Host3.inHost;
        Node3.outToController --> opticalFiberC {  distance = 510000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 510000m; } --> Node3.inFromController;
        Node3.outToNetwork++ --> opticalFiber {  distance = 360000m; } --> Node6.inFromNetwork++;
        Node3.outToNetwork++ --> opticalFiber {  distance = 300000m; } --> Node1.inFromNetwork++;
        Node3.outToNetwork++ --> opticalFiber {  distance = 120000m; } --> Node2.inFromNetwork++;
        Node3.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node3.inFromNetwork++;
        //Nodo4
        Host4.outHost --> opticalFiber {  distance = 200m; } --> Node4.inFromHost;
        Node4.outToHost --> opticalFiber {  distance = 200m; } --> Host4.inHost;
        Node4.outToController --> opticalFiberC {  distance = 240000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 240000m; } --> Node4.inFromController;
        Node4.outToNetwork++ --> opticalFiber {  distance = 120000m; } --> Node5.inFromNetwork++;
        Node4.outToNetwork++ --> opticalFiber {  distance = 150000m; } --> Node2.inFromNetwork++;
        Node4.outToNetwork++ --> opticalFiber {  distance = 390000m; } --> Node11.inFromNetwork++;
        Node4.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node4.inFromNetwork++;
        //Nodo5
        Host5.outHost --> opticalFiber {  distance = 200m; } --> Node5.inFromHost;
        Node5.outToHost --> opticalFiber {  distance = 200m; } --> Host5.inHost;
        Node5.outToController --> opticalFiberC {  distance = 120000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 120000m; } --> Node5.inFromController;
        Node5.outToNetwork++ --> opticalFiber {  distance = 120000m; } --> Node4.inFromNetwork++;
        Node5.outToNetwork++ --> opticalFiber {  distance = 120000m; } --> Node7.inFromNetwork++;
        Node5.outToNetwork++ --> opticalFiber {  distance = 240000m; } --> Node6.inFromNetwork++;
        Node5.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node5.inFromNetwork++;
        //Nodo6
        Host6.outHost --> opticalFiber {  distance = 200m; } --> Node6.inFromHost;
        Node6.outToHost --> opticalFiber {  distance = 200m; } --> Host6.inHost;
        Node6.outToController --> opticalFiberC {  distance = 360000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 360000m; } --> Node6.inFromController;
        Node6.outToNetwork++ --> opticalFiber {  distance = 360000m; } --> Node3.inFromNetwork++;
        Node6.outToNetwork++ --> opticalFiber {  distance = 210000m; } --> Node10.inFromNetwork++;
        Node6.outToNetwork++ --> opticalFiber {  distance = 240000m; } --> Node5.inFromNetwork++;
        Node6.outToNetwork++ --> opticalFiber {  distance = 360000m; } --> Node14.inFromNetwork++;
        //Nodo7
        Host7.outHost --> opticalFiber {  distance = 200m; } --> Node7.inFromHost;
        Node7.outToHost --> opticalFiber {  distance = 200m; } --> Host7.inHost;
        Node7.outToController --> opticalFiberC {  distance = 10m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 10m; } --> Node7.inFromController;
        Node7.outToNetwork++ --> opticalFiber {  distance = 150000m; } --> Node8.inFromNetwork++;
        Node7.outToNetwork++ --> opticalFiber {  distance = 120000m; } --> Node5.inFromNetwork++;
        Node7.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node7.inFromNetwork++;
        Node7.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node7.inFromNetwork++;
        //Nodo8
        Host8.outHost --> opticalFiber {  distance = 200m; } --> Node8.inFromHost;
        Node8.outToHost --> opticalFiber {  distance = 200m; } --> Host8.inHost;
        Node8.outToController --> opticalFiberC {  distance = 150000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 150000m; } --> Node8.inFromController;
        Node8.outToNetwork++ --> opticalFiber {  distance = 150000m; } --> Node7.inFromNetwork++;
        Node8.outToNetwork++ --> opticalFiber {  distance = 150000m; } --> Node9.inFromNetwork++;
        Node8.outToNetwork++ --> opticalFiber {  distance = 480000m; } --> Node1.inFromNetwork++;
        Node8.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node8.inFromNetwork++;
        //Nodo9
        Host9.outHost --> opticalFiber {  distance = 200m; } --> Node9.inFromHost;
        Node9.outToHost --> opticalFiber {  distance = 200m; } --> Host9.inHost;
        Node9.outToController --> opticalFiberC {  distance = 300000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 300000m; } --> Node9.inFromController;
        Node9.outToNetwork++ --> opticalFiber {  distance = 150000m; } --> Node10.inFromNetwork++;
        Node9.outToNetwork++ --> opticalFiber {  distance = 150000m; } --> Node8.inFromNetwork++;
        Node9.outToNetwork++ --> opticalFiber {  distance = 60000m; } --> Node12.inFromNetwork++;
        Node9.outToNetwork++ --> opticalFiber {  distance = 60000m; } --> Node13.inFromNetwork++;
        //Nodo10
        Host10.outHost --> opticalFiber {  distance = 200m; } --> Node10.inFromHost;
        Node10.outToHost --> opticalFiber {  distance = 200m; } --> Host10.inHost;
        Node10.outToController --> opticalFiberC {  distance = 450000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 450000m; } --> Node10.inFromController;
        Node10.outToNetwork++ --> opticalFiber {  distance = 150000m; } --> Node9.inFromNetwork++;
        Node10.outToNetwork++ --> opticalFiber {  distance = 210000m; } --> Node6.inFromNetwork++;
        Node10.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node10.inFromNetwork++;
        Node10.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node10.inFromNetwork++;
        //Nodo11
        Host11.outHost --> opticalFiber {  distance = 200m; } --> Node11.inFromHost;
        Node11.outToHost --> opticalFiber {  distance = 200m; } --> Host11.inHost;
        Node11.outToController --> opticalFiberC {  distance = 480000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 480000m; } --> Node11.inFromController;
        Node11.outToNetwork++ --> opticalFiber {  distance = 120000m; } --> Node12.inFromNetwork++;
        Node11.outToNetwork++ --> opticalFiber {  distance = 150000m; } --> Node13.inFromNetwork++;
        Node11.outToNetwork++ --> opticalFiber {  distance = 390000m; } --> Node4.inFromNetwork++;
        Node11.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node11.inFromNetwork++;
        //Nodo12
        Host12.outHost --> opticalFiber {  distance = 200m; } --> Node12.inFromHost;
        Node12.outToHost --> opticalFiber {  distance = 200m; } --> Host12.inHost;
        Node12.outToController --> opticalFiberC {  distance = 360000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 360000m; } --> Node12.inFromController;
        Node12.outToNetwork++ --> opticalFiber {  distance = 120000m; } --> Node11.inFromNetwork++;
        Node12.outToNetwork++ --> opticalFiber {  distance = 60000m; } --> Node14.inFromNetwork++;
        Node12.outToNetwork++ --> opticalFiber {  distance = 60000m; } --> Node9.inFromNetwork++;
        Node12.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node12.inFromNetwork++;
        //Nodo13
        Host13.outHost --> opticalFiber {  distance = 200m; } --> Node13.inFromHost;
        Node13.outToHost --> opticalFiber {  distance = 200m; } --> Host13.inHost;
        Node13.outToController --> opticalFiberC {  distance = 360000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 360000m; } --> Node13.inFromController;
        Node13.outToNetwork++ --> opticalFiber {  distance = 100m; } --> Node13.inFromNetwork++;
        Node13.outToNetwork++ --> opticalFiber {  distance = 150000m; } --> Node11.inFromNetwork++;
        Node13.outToNetwork++ --> opticalFiber {  distance = 30000m; } --> Node14.inFromNetwork++;
        Node13.outToNetwork++ --> opticalFiber {  distance = 60000m; } --> Node9.inFromNetwork++;
        //Nodo14
        Host14.outHost --> opticalFiber {  distance = 200m; } --> Node14.inFromHost;
        Node14.outToHost --> opticalFiber {  distance = 200m; } --> Host14.inHost;
        Node14.outToController --> opticalFiberC {  distance = 390000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 390000m; } --> Node14.inFromController;
        Node14.outToNetwork++ --> opticalFiber {  distance = 100m; } --> Node14.inFromNetwork++;
        Node14.outToNetwork++ --> opticalFiber {  distance = 60000m; } --> Node12.inFromNetwork++;
        Node14.outToNetwork++ --> opticalFiber {  distance = 30000m; } --> Node13.inFromNetwork++;
        Node14.outToNetwork++ --> opticalFiber {  distance = 360000m; } --> Node6.inFromNetwork++;

}

network NSFNet_Network_WAN
{
    @display("bgb=817.03204,691.008;bgi=maps/usa,c");
    submodules:
        Node1: OBS_Node {
            @display("p=66,176");
            nodeID = 1;
        }
        Node2: OBS_Node {
            @display("p=47,330");
            nodeID = 2;
        }
        Node3: OBS_Node {
            @display("p=158,441");
            nodeID = 3;
        }
        Node4: OBS_Node {
            @display("p=192,304");
            nodeID = 4;
        }
        Node5: OBS_Node {
            @display("p=299,389");
            nodeID = 5;
        }
        Node6: OBS_Node {
            @display("p=348,549");
            nodeID = 6;
        }
        Node7: OBS_Node {
            @display("p=406,382");
            nodeID = 7;
        }
        Node8: OBS_Node {
            @display("p=498,343");
            nodeID = 8;
        }
        Node9: OBS_Node {
            @display("p=588,284");
            nodeID = 9;
        }
        Node10: OBS_Node {
            @display("p=614,527");
            nodeID = 10;
        }
        Node11: OBS_Node {
            @display("p=470,236");
            nodeID = 11;
        }
        Node12: OBS_Node {
            @display("p=707,197");
            nodeID = 12;
        }
        Node13: OBS_Node {
            @display("p=633,350");
            nodeID = 13;
        }
        Node14: OBS_Node {
            @display("p=627,428");
            nodeID = 14;
        }
        controller: Controller {
            @display("p=486,29");
        }
        Host1: Host {
            @display("p=18,125");
            hostID = 1;
        }
        Host2: Host {
            @display("p=18,402");
            hostID = 2;
        }
        Host3: Host {
            @display("p=148,510");
            hostID = 3;
        }
        Host4: Host {
            @display("p=176,236");
            hostID = 4;
        }
        Host5: Host {
            @display("p=243,428");
            hostID = 5;
        }
        Host6: Host {
            @display("p=282,566");
            hostID = 6;
        }
        Host7: Host {
            @display("p=452,441");
            hostID = 7;
        }
        Host8: Host {
            @display("p=542,402");
            hostID = 8;
        }
        Host9: Host {
            @display("p=643,284");
            hostID = 9;
        }
        Host10: Host {
            @display("p=559,576");
            hostID = 10;
        }
        Host11: Host {
            @display("p=425,197");
            hostID = 11;
        }
        Host12: Host {
            @display("p=726,137");
            hostID = 12;
        }
        Host13: Host {
            @display("p=697,350");
            hostID = 13;
        }
        Host14: Host {
            @display("p=697,455");
            hostID = 14;
        }
    connections:
        //Conexiones entre nodos segun la topologia del trabajo de grado
        //Nodo1
        Host1.outHost --> opticalFiber {  distance = 200m; } --> Node1.inFromHost;
        Node1.outToHost --> opticalFiber {  distance = 200m; } --> Host1.inHost;
        Node1.outToController --> opticalFiberC {  distance = 6300000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 6300000m; } --> Node1.inFromController;
        Node1.outToNetwork++ --> opticalFiber {  distance = 2100000m; } --> Node2.inFromNetwork++;
        Node1.outToNetwork++ --> opticalFiber {  distance = 3000000m; } --> Node3.inFromNetwork++;
        Node1.outToNetwork++ --> opticalFiber {  distance = 4800000m; } --> Node8.inFromNetwork++;
        Node1.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node1.inFromNetwork++;
        //Nodo2
        Host2.outHost --> opticalFiber {  distance = 200m; } --> Node2.inFromHost;
        Node2.outToHost --> opticalFiber {  distance = 200m; } --> Host2.inHost;
        Node2.outToController --> opticalFiberC {  distance = 3900000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 3900000m; } --> Node2.inFromController;
        Node2.outToNetwork++ --> opticalFiber {  distance = 2100000m; } --> Node1.inFromNetwork++;
        Node2.outToNetwork++ --> opticalFiber {  distance = 1500000m; } --> Node4.inFromNetwork++;
        Node2.outToNetwork++ --> opticalFiber {  distance = 1200000m; } --> Node3.inFromNetwork++;
        Node2.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node2.inFromNetwork++;
        //Nodo3
        Host3.outHost --> opticalFiber {  distance = 200m; } --> Node3.inFromHost;
        Node3.outToHost --> opticalFiber {  distance = 200m; } --> Host3.inHost;
        Node3.outToController --> opticalFiberC {  distance = 5100000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 5100000m; } --> Node3.inFromController;
        Node3.outToNetwork++ --> opticalFiber {  distance = 3600000m; } --> Node6.inFromNetwork++;
        Node3.outToNetwork++ --> opticalFiber {  distance = 3000000m; } --> Node1.inFromNetwork++;
        Node3.outToNetwork++ --> opticalFiber {  distance = 1200000m; } --> Node2.inFromNetwork++;
        Node3.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node3.inFromNetwork++;
        //Nodo4
        Host4.outHost --> opticalFiber {  distance = 200m; } --> Node4.inFromHost;
        Node4.outToHost --> opticalFiber {  distance = 200m; } --> Host4.inHost;
        Node4.outToController --> opticalFiberC {  distance = 2400000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 2400000m; } --> Node4.inFromController;
        Node4.outToNetwork++ --> opticalFiber {  distance = 1200000m; } --> Node5.inFromNetwork++;
        Node4.outToNetwork++ --> opticalFiber {  distance = 1500000m; } --> Node2.inFromNetwork++;
        Node4.outToNetwork++ --> opticalFiber {  distance = 3900000m; } --> Node11.inFromNetwork++;
        Node4.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node4.inFromNetwork++;
        //Nodo5
        Host5.outHost --> opticalFiber {  distance = 200m; } --> Node5.inFromHost;
        Node5.outToHost --> opticalFiber {  distance = 200m; } --> Host5.inHost;
        Node5.outToController --> opticalFiberC {  distance = 1200000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 1200000m; } --> Node5.inFromController;
        Node5.outToNetwork++ --> opticalFiber {  distance = 1200000m; } --> Node4.inFromNetwork++;
        Node5.outToNetwork++ --> opticalFiber {  distance = 1200000m; } --> Node7.inFromNetwork++;
        Node5.outToNetwork++ --> opticalFiber {  distance = 2400000m; } --> Node6.inFromNetwork++;
        Node5.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node5.inFromNetwork++;
        //Nodo6
        Host6.outHost --> opticalFiber {  distance = 200m; } --> Node6.inFromHost;
        Node6.outToHost --> opticalFiber {  distance = 200m; } --> Host6.inHost;
        Node6.outToController --> opticalFiberC {  distance = 3600000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 3600000m; } --> Node6.inFromController;
        Node6.outToNetwork++ --> opticalFiber {  distance = 3600000m; } --> Node3.inFromNetwork++;
        Node6.outToNetwork++ --> opticalFiber {  distance = 2100000m; } --> Node10.inFromNetwork++;
        Node6.outToNetwork++ --> opticalFiber {  distance = 2400000m; } --> Node5.inFromNetwork++;
        Node6.outToNetwork++ --> opticalFiber {  distance = 3600000m; } --> Node14.inFromNetwork++;
        //Nodo7
        Host7.outHost --> opticalFiber {  distance = 200m; } --> Node7.inFromHost;
        Node7.outToHost --> opticalFiber {  distance = 200m; } --> Host7.inHost;
        Node7.outToController --> opticalFiberC {  distance = 10m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 10m; } --> Node7.inFromController;
        Node7.outToNetwork++ --> opticalFiber {  distance = 1500000m; } --> Node8.inFromNetwork++;
        Node7.outToNetwork++ --> opticalFiber {  distance = 1200000m; } --> Node5.inFromNetwork++;
        Node7.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node7.inFromNetwork++;
        Node7.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node7.inFromNetwork++;
        //Nodo8
        Host8.outHost --> opticalFiber {  distance = 200m; } --> Node8.inFromHost;
        Node8.outToHost --> opticalFiber {  distance = 200m; } --> Host8.inHost;
        Node8.outToController --> opticalFiberC {  distance = 1500000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 1500000m; } --> Node8.inFromController;
        Node8.outToNetwork++ --> opticalFiber {  distance = 1500000m; } --> Node7.inFromNetwork++;
        Node8.outToNetwork++ --> opticalFiber {  distance = 1500000m; } --> Node9.inFromNetwork++;
        Node8.outToNetwork++ --> opticalFiber {  distance = 4800000m; } --> Node1.inFromNetwork++;
        Node8.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node8.inFromNetwork++;
        //Nodo9
        Host9.outHost --> opticalFiber {  distance = 200m; } --> Node9.inFromHost;
        Node9.outToHost --> opticalFiber {  distance = 200m; } --> Host9.inHost;
        Node9.outToController --> opticalFiberC {  distance = 3000000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 3000000m; } --> Node9.inFromController;
        Node9.outToNetwork++ --> opticalFiber {  distance = 1500000m; } --> Node10.inFromNetwork++;
        Node9.outToNetwork++ --> opticalFiber {  distance = 1500000m; } --> Node8.inFromNetwork++;
        Node9.outToNetwork++ --> opticalFiber {  distance = 600000m; } --> Node12.inFromNetwork++;
        Node9.outToNetwork++ --> opticalFiber {  distance = 600000m; } --> Node13.inFromNetwork++;
        //Nodo10
        Host10.outHost --> opticalFiber {  distance = 200m; } --> Node10.inFromHost;
        Node10.outToHost --> opticalFiber {  distance = 200m; } --> Host10.inHost;
        Node10.outToController --> opticalFiberC {  distance = 4500000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 4500000m; } --> Node10.inFromController;
        Node10.outToNetwork++ --> opticalFiber {  distance = 1500000m; } --> Node9.inFromNetwork++;
        Node10.outToNetwork++ --> opticalFiber {  distance = 2100000m; } --> Node6.inFromNetwork++;
        Node10.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node10.inFromNetwork++;
        Node10.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node10.inFromNetwork++;
        //Nodo11
        Host11.outHost --> opticalFiber {  distance = 200m; } --> Node11.inFromHost;
        Node11.outToHost --> opticalFiber {  distance = 200m; } --> Host11.inHost;
        Node11.outToController --> opticalFiberC {  distance = 4800000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 4800000m; } --> Node11.inFromController;
        Node11.outToNetwork++ --> opticalFiber {  distance = 1200000m; } --> Node12.inFromNetwork++;
        Node11.outToNetwork++ --> opticalFiber {  distance = 1500000m; } --> Node13.inFromNetwork++;
        Node11.outToNetwork++ --> opticalFiber {  distance = 3900000m; } --> Node4.inFromNetwork++;
        Node11.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node11.inFromNetwork++;
        //Nodo12
        Host12.outHost --> opticalFiber {  distance = 200m; } --> Node12.inFromHost;
        Node12.outToHost --> opticalFiber {  distance = 200m; } --> Host12.inHost;
        Node12.outToController --> opticalFiberC {  distance = 3600000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 3600000m; } --> Node12.inFromController;
        Node12.outToNetwork++ --> opticalFiber {  distance = 1200000m; } --> Node11.inFromNetwork++;
        Node12.outToNetwork++ --> opticalFiber {  distance = 600000m; } --> Node14.inFromNetwork++;
        Node12.outToNetwork++ --> opticalFiber {  distance = 600000m; } --> Node9.inFromNetwork++;
        Node12.outToNetwork++ --> opticalFiber {  distance = 10m; } --> Node12.inFromNetwork++;
        //Nodo13
        Host13.outHost --> opticalFiber {  distance = 200m; } --> Node13.inFromHost;
        Node13.outToHost --> opticalFiber {  distance = 200m; } --> Host13.inHost;
        Node13.outToController --> opticalFiberC {  distance = 3600000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 3600000m; } --> Node13.inFromController;
        Node13.outToNetwork++ --> opticalFiber {  distance = 100m; } --> Node13.inFromNetwork++;
        Node13.outToNetwork++ --> opticalFiber {  distance = 1500000m; } --> Node11.inFromNetwork++;
        Node13.outToNetwork++ --> opticalFiber {  distance = 300000m; } --> Node14.inFromNetwork++;
        Node13.outToNetwork++ --> opticalFiber {  distance = 600000m; } --> Node9.inFromNetwork++;
        //Nodo14
        Host14.outHost --> opticalFiber {  distance = 200m; } --> Node14.inFromHost;
        Node14.outToHost --> opticalFiber {  distance = 200m; } --> Host14.inHost;
        Node14.outToController --> opticalFiberC {  distance = 3900000m; } --> controller.inController++;
        controller.outController++ --> opticalFiberC {  distance = 3900000m; } --> Node14.inFromController;
        Node14.outToNetwork++ --> opticalFiber {  distance = 100m; } --> Node14.inFromNetwork++;
        Node14.outToNetwork++ --> opticalFiber {  distance = 600000m; } --> Node12.inFromNetwork++;
        Node14.outToNetwork++ --> opticalFiber {  distance = 300000m; } --> Node13.inFromNetwork++;
        Node14.outToNetwork++ --> opticalFiber {  distance = 3600000m; } --> Node6.inFromNetwork++;
}
