// Universidad del Cauca
// "AGENTE INTELIGENTE PARA LA ASIGNACIÓN DE RUTAS EN UNA ARQUITECTURA SD-EON"
// Trabajo de grado
// Autores:	David Santiago Pismag Imbachi
//			Andrés Fernando Medina Pino

packet hostMessage {
    unsigned int destinationAdd;	//Direccion de destino
    unsigned int sourceAdd;			//Direccion de origen
    unsigned int typeOfService;		//Tipo (clase) de servicio
	unsigned int payloadLength;		//Longitud de payload del paquete en bytes
	unsigned int headerLength;		//Longitud de header del paquete en bytes
	double delay;					//Retardo total de transmision del paquete (E2E)
	//double additionalDelay;			//Retardos de procesamiento en los diferentes modulos
}

packet obsMessage{
	hostMessage *hostMessageGroup[];	//Vector de mensajes host
	unsigned int sourceAdd;				//Igual a la de Host
	unsigned int destinationAdd;		//Dirección de destino
	unsigned int typeOfService;		//Clase 1, 2 o 3
	unsigned int payloadLength;		//Longitud total del payload (payload+header IP) en bytes
	unsigned int headerLength;		//Longitud total de la cabecera OBS
	unsigned int signalWavelenght;	//Longitud de onda para la transmision de la ráfaga
	unsigned int burstID;			//ID para identificar la rafaga en el buffer
}

packet resourceRequest{
	unsigned int typeOfMsg;				//Tipo de mensaje enviado
			//Tipo 1: mensaje de solicitud de recursos
			//Tipo 2: ACK de solicitud de recursos, puede enviar la ráfaga
			//Tipo 3: Usados para liberar recursos cuando se envian del nodo al controlador
	double generationTime;			//Tiempo en que se genera la resource request (No aplica para la liberacion de recursos)
	double resourceDelay;			//Tiempo de retardo generado por la espera de recursos
	unsigned int sourceNode;		//El nodo 0 sera el controlador
	unsigned int destinationNode;	//Nodo destino de la ráfaga
	unsigned int signalWavelenght;	//Longitud de onda asignada por el controlador, solo aplica en el ACK
	unsigned int burstID;			//ID para identificar a que rafaga esta asociada la solicitud
	unsigned int typeOfService;		//Tipo (clase) de servicio
}

packet configurationMessage{
	unsigned int typeOfMsg;		//Tipo de mensaje enviado
			//Tipo 1: solicitud de configuracion
			//Tipo 2: ACK de configuracion
	unsigned int destinationNode;	//Nodo destino del mensaje de configuracion/ACK
	unsigned int inputTrafficPort;	//Puerto de entrada del tráfico, el 0 sera proveniente del host
	unsigned int outputTrafficPort;	//Puerto de salida del tráfico, el 0 sera dirigido hacia el host
	unsigned int numberOfNodes;		//Numero de nodos a configurar
	unsigned int signalWavelenght;	//Longitud de onda para la cual aplica la configuracion	
	unsigned int burstID;			//ID del proceso de configuracion (usado para diferenciar entre las diferentes ordenes de config)
										//Para este caso es la misma que el signalWavelenght, pero varia cuando se usan FSs
	double delayAI;					//Delay introducido por el procesamiento del AI
	double requestGenerationDelay;	//Delay introducido por la solicitud de recursos
	double configurationDelay;		//Retardo introducido por la configuración del camino óptico
}