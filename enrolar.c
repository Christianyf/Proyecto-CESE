   uint8_t in,index;
 //-----------------------------------------------------------
   debugPrintlnString( "Enrollar huella\r\n" );
   for(in=1;in<3;in++)
   {
	   if(in==1)
	   {
		   debugPrintlnString( "Ubique el dedo sobre el sensor\r\n" );

	   }else
		   {
			   debugPrintlnString( "Ubique el mismo dedo nuevamente\r\n" );
		   }
	   while(TRUE)
	   {
		   index=getImage();////******************************************
		   delay(1000);
		  // uartWriteByte( UART_PC,packet_in.data[0] );/////para probar luego borrar
		   //debugPrintlnString( "\r\n" );//para probar luego borrar
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
		   if(index==FINGERPRINT_OK)
		   {
			   debugPrintlnString( "Imagen capturada\r\n" );
			   break;
		   }else if(index==FINGERPRINT_NOFINGER)
		   {
			   //debugPrintlnString( "no hay dedo");
		   }else if(index==FINGERPRINT_IMAGEFAIL)
		   {
			   debugPrintlnString( "Error en Imagen\r\n" );
			   return FALSE;
		   }else
		   {
			   debugPrintlnString( "Otro error\r\n" );
			   return FALSE;
		   }

	   }
		   debugPrintlnString( "......Modelado.........\r\n" );
		   index=image2Tz(in);//******************************************
		   if(index==FINGERPRINT_OK)
		   {
			   debugPrintlnString( "Modelado correctamente\r\n" );
		   }else
		   {
			   if(index==FINGERPRINT_IMAGEMESS)
			   {
				   debugPrintlnString( "Imagen deteriorada\r\n" );
			   }else if(index==FINGERPRINT_FEATUREFAIL)
			   {
				   debugPrintlnString( "No se puede caracterizar las huellas\r\n" );
			   }else if(index==FINGERPRINT_INVALIDIMAGE)
			   {
				   debugPrintlnString( "Imagen invalida\r\n" );
			   }else
			   {
				   debugPrintlnString( "Otro error" );
				   return FALSE;
			   }
		   }

		  if(in==1)
		  {
			  debugPrintlnString( "Remueva el dedo\r\n" );
			  delay(1000);
			  while(!index==FINGERPRINT_NOFINGER)
			  {
				  index=getImage();
			  }
		  }


   }
