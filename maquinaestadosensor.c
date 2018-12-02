   typedef enum  estado {ESPERA,TOMA} Estado;
   Estado initial_state = ESPERA;

   uint8_t flag=1;
   uint8_t device_reply;


   while( TRUE ) {

	   if(initial_state==ESPERA)
	   {
		   if(flag==1)
		   {
			   debugPrintlnString( "En estado de Espera...\r\n" );
		   	   flag=0;
		   }
		   device_reply=getImage();
		   uartWriteByte( UART_PC,packet_in.type );
		   uartWriteByte( UART_PC,packet_in.data[0] );
		   uartWriteByte( UART_PC,device_reply);
		   //delay(1000);
		   if(device_reply==FINGERPRINT_OK )//&& packet_in.type==FINGERPRINT_ACKPACKET
		   {
			   debugPrintlnString( "capturo imagen y modeliozo.\r\n" );
			   debugPrintlnString( "espera por segunda imagen.\r\n" );
			   debugPrintlnString( "cambió de estado.\r\n" );
			   initial_state=TOMA;
			   flag=1;
		   }

	   }
	   if(initial_state==TOMA)
	   {
		   if(flag==1)
		   {
			   debugPrintlnString( "En estado de TOMA...\r\n" );
		   	   flag=0;
		   }
	   }

   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
