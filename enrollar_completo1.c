/*==================[inlcusiones]============================================*/

#include "sapi.h"        // <= Biblioteca sAPI
#include <string.h>
#include <math.h>


/*==================[definiciones y macros]==================================*/

#define UART_PC        UART_USB
#define UART_BLUETOOTH UART_232

#define BAUD_RATE 115200

#define FINGERPRINT_OK 0X00
#define FINGERPRINT_ACKPACKET 0x7
#define FINGERPRINT_NOFINGER 0x02
#define FINGERPRINT_IMAGEFAIL 0x03
#define FINGERPRINT_IMAGEMESS 0x06
#define FINGERPRINT_FEATUREFAIL 0x07
#define FINGERPRINT_INVALIDIMAGE 0x15
#define FINGERPRINT_ENROLLMISMATCH 0x0A
#define FINGERPRINT_BADLOCATION 0x0B
#define FINGERPRINT_FLASHERR 0x18
#define FINGERPRINT_VERIFYPASSWORD 0x13
#define FINGERPRINT_PACKETRECIEVEERR 0x01
#define FINGERPRINT_STARTCODE 0xEF01
#define FINGERPRINT_COMMANDPACKET 0x1
#define FINGERPRINT_GETIMAGE 0x01
#define FINGERPRINT_IMAGE2TZ 0x02
#define FINGERPRINT_REGMODEL 0x05
#define FINGERPRINT_STORE 0x06
#define FINGERPRINT_LOAD 0x07
#define FINGERPRINT_UPLOAD 0x08
#define FINGERPRINT_DELETE 0x0C
#define FINGERPRINT_EMPTY 0x0D
#define FINGERPRINT_HISPEEDSEARCH 0x1B
#define FINGERPRINT_TIMEOUT 0xFF
#define FINGERPRINT_BADPACKET 0xFE
#define FINGERPRINT_TEMPLATECOUNT 0x1D

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/*==================[definiciones de datos internos]=========================*/

DEBUG_PRINT_ENABLE
CONSOLE_PRINT_ENABLE

uint32_t thePassword=0;
//----------------------------------------------------------------------------
typedef struct  {

  uint16_t start_code;      ///< "Wakeup" code for packet detection
  uint8_t address[4];       ///< 32-bit Fingerprint sensor address
  uint8_t type;             ///< Type of packet
  uint16_t length;          ///< Length of packet
  uint8_t data[64];         ///< The raw buffer for packet payload

}Adafruit_Fingerprint_Packet;

 static Adafruit_Fingerprint_Packet packet;
 static Adafruit_Fingerprint_Packet packet_in;

/*==================[definiciones de datos externos]=========================*/

 void Adafruit_Fingerprint_packet (uint8_t type, uint16_t length, uint8_t * data);
 uint8_t getStructuredPacket(Adafruit_Fingerprint_Packet * packet, uint16_t timeout);
//----------------------------------------------------------------------------
 void writeStructuredPacket(const Adafruit_Fingerprint_Packet *packet) {


   //uartWriteByte( UART_PC,packet->start_code >>8 );
   uartWriteByte( UART_BLUETOOTH,packet->start_code >>8 );

   //uartWriteByte( UART_PC,packet->start_code & 0XFF );
   uartWriteByte( UART_BLUETOOTH,packet->start_code & 0XFF );

   //uartWriteByte( UART_PC,packet->address[0] );
   uartWriteByte( UART_BLUETOOTH,packet->address[0] );

   //uartWriteByte( UART_PC,packet->address[1] );
   uartWriteByte( UART_BLUETOOTH,packet->address[1] );

   //uartWriteByte( UART_PC,packet->address[2] );
   uartWriteByte( UART_BLUETOOTH,packet->address[2] );

   //uartWriteByte( UART_PC,packet->address[3] );
   uartWriteByte( UART_BLUETOOTH,packet->address[3] );

   //uartWriteByte( UART_PC,packet->type );
   uartWriteByte( UART_BLUETOOTH,packet->type );

   uint16_t wire_length = packet->length+2;//se suma 2 por la presencia de los bytes del checksum


   //uartWriteByte( UART_PC,wire_length >> 8 );
   uartWriteByte( UART_BLUETOOTH,wire_length >> 8 );

   //uartWriteByte( UART_PC,wire_length & 0XFF );
   uartWriteByte( UART_BLUETOOTH,wire_length & 0XFF );

   uint16_t sum = ((wire_length)>>8) + ((wire_length)&0xFF) + packet->type;


   for (uint8_t i=0; i< packet->length; i++) {

     //uartWriteByte( UART_PC,packet->data[i] );
     uartWriteByte( UART_BLUETOOTH,packet->data[i] );

     sum += packet->data[i];
   }


   //uartWriteByte( UART_PC,sum >> 8 );
   uartWriteByte( UART_BLUETOOTH,sum >> 8 );

   //uartWriteByte( UART_PC,sum & 0XFF );
   uartWriteByte( UART_BLUETOOTH,sum & 0XFF );

   //debugPrintlnString( "\n" );
   return;
 }
//----------------------------------------------------------------------------
 void GET_CMD_PACKET(uint8_t commandpacket,uint8_t dat1,uint8_t dat2,uint8_t dat3,uint8_t dat4){
 	uint8_t data[5];//5
 	data[0]=commandpacket;
 	data[1]=dat1;
 	data[2]=dat2;
 	data[3]=dat3;
 	data[4]=dat4;



    Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
    writeStructuredPacket(&packet);
 }

/*==================[declaraciones de funciones internas]====================*/
void Adafruit_Fingerprint_packet (uint8_t type, uint16_t length, uint8_t * data) {

  packet.start_code = FINGERPRINT_STARTCODE;
  packet.type = type;
  packet.length = length;
  packet.address[0] = 0xFF; packet.address[1] = 0xFF;
  packet.address[2] = 0xFF; packet.address[3] = 0xFF;

  if(length<64)
    memcpy(packet.data, data, length);
  else
    memcpy(packet.data, data, 64);
}
//-----------------------------------------------------------------------------

uint8_t checkPassword(void) {

  GET_CMD_PACKET(FINGERPRINT_VERIFYPASSWORD,
                  (uint8_t)(thePassword >> 24), (uint8_t)(thePassword >> 16),
                  (uint8_t)(thePassword >> 8), (uint8_t)(thePassword & 0xFF));

  if (packet.data[0] == FINGERPRINT_OK)//debe cambiarse por los datos de respuesta, no los de envio
    return FINGERPRINT_OK;
  else
    return FINGERPRINT_PACKETRECIEVEERR;
}
//----------------------------------------------------------------------------
bool_t verifyPassword(void) {
  return checkPassword() == FINGERPRINT_OK;
}
//----------------------------------------------------------------------------

//---------------------------------------------------------------------------
uint8_t image2Tz(uint8_t slot) {
  uint8_t data[2] = {FINGERPRINT_IMAGE2TZ,slot};
  Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
  writeStructuredPacket(&packet);
  if(getStructuredPacket(&packet_in,100)==FINGERPRINT_OK)
  {
	  return packet_in.data[0];
  }else
  {
	  return FINGERPRINT_BADPACKET;
  }
}
//---------------------------------------------------------------------------
uint8_t createModel(void) {
  uint8_t data[1] = {FINGERPRINT_REGMODEL};
  Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
  writeStructuredPacket(&packet);
  getStructuredPacket(&packet_in,100);

  return packet_in.data[0];
}
//--------------------------------------------------------------------------
uint8_t storeModel(uint16_t location) {

  uint8_t data[4] = {FINGERPRINT_STORE,0X01,(uint8_t)(location >> 8),(uint8_t)(location & 0xFF)};
  Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
  writeStructuredPacket(&packet);
  if(getStructuredPacket(&packet_in,100)==FINGERPRINT_OK)
    {
  	  return packet_in.data[0];
    }else
    {
    	return packet_in.data[0];
    }
}
//-------------------------------------------------------------------------
uint8_t loadModel(uint16_t location) {

  uint8_t data[4] = {FINGERPRINT_LOAD,0X01,(uint8_t)(location >> 8),(uint8_t)(location & 0xFF)};
  Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
  writeStructuredPacket(&packet);
  return 0;
}
//------------------------------------------------------------------------
uint8_t getModel(void) {

  uint8_t data[2] = {FINGERPRINT_UPLOAD,0X01};
  Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
  writeStructuredPacket(&packet);
  return 0;
}
//-----------------------------------------------------------------------
uint8_t deleteModel(uint16_t location) {

  uint8_t data[5] = {FINGERPRINT_DELETE, (uint8_t)(location >> 8), (uint8_t)(location & 0xFF), 0x00, 0x01};
  Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
  writeStructuredPacket(&packet);
  return 0;
}
//-----------------------------------------------------------------------
uint8_t emptyDatabase(void) {

  uint8_t data[1]={FINGERPRINT_EMPTY};
  Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
  writeStructuredPacket(&packet);
  return 0;
}
//------------------------------------------------------------------------
uint8_t getStructuredPacket(Adafruit_Fingerprint_Packet * packet, uint16_t timeout) {//usar con cuidado
  uint8_t byte;
  uint16_t idx=0, timer=0;

  while(TRUE) {
    while(!uartRxReady(UART_BLUETOOTH))
    {
      delay(1);
      //timer++;
      //if( timer >= timeout)
      //{
    	  //debugPrintlnString( "Timed out" );
    	  //return FINGERPRINT_TIMEOUT;
      //}
    }
    uartReadByte( UART_BLUETOOTH, &byte );
    //uartWriteByte( UART_PC, byte );

    switch (idx) {
      case 0:
        if (byte != (FINGERPRINT_STARTCODE >> 8))
	  continue;
        packet->start_code = (uint16_t)byte << 8;
        break;
      case 1:
        packet->start_code |= byte;
        if (packet->start_code != FINGERPRINT_STARTCODE)
	  return FINGERPRINT_BADPACKET;
        break;
      case 2:
      case 3:
      case 4:
      case 5:
        packet->address[idx-2] = byte;
        break;
      case 6:
	packet->type = byte;
	break;
      case 7:
	packet->length = (uint16_t)byte << 8;
	break;
      case 8:
	packet->length |= byte;
	break;
      default:
        packet->data[idx-9] = byte;
        if((idx-8) == packet->length)
          return FINGERPRINT_OK;
        break;
    }
    idx++;
  }
  return FINGERPRINT_BADPACKET;
}
//-----------------------------------------------------------------------
uint8_t getImage(void) {
  uint8_t data[1] = {FINGERPRINT_GETIMAGE};
  Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
  writeStructuredPacket(&packet);
  //getStructuredPacket(&packet_in,100);
  if(getStructuredPacket(&packet_in,100)==FINGERPRINT_OK)
  {
	  return packet_in.data[0];
  }else
  {
	  return FINGERPRINT_BADPACKET;
  }

}


//-----------------------------------------------------------------------
uint8_t fingerFastSearch(void) {
  // high speed search of slot #1 starting at page 0x0000 and page #0x00A3

  uint8_t data[6]={FINGERPRINT_HISPEEDSEARCH, 0x01, 0x00, 0x00, 0x00, 0xA3};
  Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
  writeStructuredPacket(&packet);
  getStructuredPacket(&packet_in,100);

  uint16_t fingerID = 0xFFFF;
  uint16_t confidence = 0xFFFF;

  fingerID = packet_in.data[1];
  fingerID <<= 8;
  fingerID |= packet_in.data[2];

  confidence = packet_in.data[3];
  confidence <<= 8;
  confidence |= packet_in.data[4];

  return 0;
}
//----------------------------------------------------------------------------
uint8_t getTemplateCount(void) {//no usar actua raro

  uint16_t templateCount;
  uint8_t data[1]={FINGERPRINT_TEMPLATECOUNT};
  Adafruit_Fingerprint_packet (FINGERPRINT_COMMANDPACKET, sizeof(data), data);
  writeStructuredPacket(&packet);
  getStructuredPacket(&packet_in,100);

  templateCount = packet_in.data[1];
  templateCount <<= 8;
  templateCount |= packet_in.data[2];

  return packet_in.data[0];
}
//----------------------------------------------------------------------------

/*==================[declaraciones de funciones externas]====================*/
typedef enum  estado {ESPERA,TOMA,LIMBO,SALIDA} Estado;
Estado initial_state = ESPERA;

uint8_t flag=1;
uint8_t device_reply;

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
	// Inicializar y configurar la plataforma
   boardConfig();

   // Inicializar UART_USB para conectar a la PC
   debugPrintConfigUart( UART_PC, 57600 );//(usually 57600, 9600 or 115200)
   debugPrintlnString( "UART_PC configurada." );

   // Inicializar UART_232 para conectar al modulo bluetooth
   consolePrintConfigUart( UART_BLUETOOTH, 57600 );
   debugPrintlnString( "UART_BLUETOOTH para modulo Bluetooth configurada." );

   //verifyPassword();//***********************************
   //getImage();//*****************************************
   //image2Tz(2);//**************************************** el 2 es para confirmar, el 1 para la primera toma
   //createModel();
   //storeModel(3);//3 ES LA UBICACION que quiero darle en la flash
   //loadModel(3);////3 ES LA UBICACION que tiene en la memoria flash
   //getModel();//baja a la pc ???????????????????
   //deleteModel(3);//numero del mmodelo a borrar
   //emptyDatabase();
   //fingerFastSearch();
   //getTemplateCount();
   //getStructuredPacket(&packet_in,100);
   /*debugPrintlnString( "\n" );
   uartWriteByte( UART_PC,packet_in.start_code>>8 );
   uartWriteByte( UART_PC,packet_in.start_code & 0XFF );
   uartWriteByte( UART_PC,packet_in.address[0] );
   uartWriteByte( UART_PC,packet_in.address[1] );
   uartWriteByte( UART_PC,packet_in.address[2] );
   uartWriteByte( UART_PC,packet_in.address[3] );
   uartWriteByte( UART_PC,packet_in.type );
   uartWriteByte( UART_PC,packet_in.length>>8 );
   uartWriteByte( UART_PC,packet_in.length & 0XFF );
   uartWriteByte( UART_PC,packet_in.data[0] );
   uartWriteByte( UART_PC,packet_in.data[1] );
   uartWriteByte( UART_PC,packet_in.data[2] );*/

   //uint8_t data = 0;
//-------------------------------------------------------------

   uint8_t bite = 0,j,aux=0xff,aux2;


   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
	   if(initial_state==ESPERA)
	   {
		   if(flag==1)
		   {
			   debugPrintlnString( "Ubique el dedo sobre el sensor...\r\n" );
		   	   flag=0;
		   }
		   device_reply=getImage();

		   if(device_reply==FINGERPRINT_OK )
		   {
			   initial_state=LIMBO;
			   flag=1;
			   debugPrintlnString( "Imagen Capturada.\r\n" );
			   debugPrintlnString( "Remueva el dedo....\r\n" );
			   aux = image2Tz(1);

		   }else if(device_reply==FINGERPRINT_IMAGEFAIL)
		   {
			   debugPrintlnString( "Error en captura\r\n" );
			   initial_state=SALIDA;
			   flag=1;
		   }

	   }
	   if(initial_state==LIMBO)
	   {
		   if(flag==1)
		   {
			   flag=0;
		   }
		   device_reply=getImage();
		   if(device_reply==FINGERPRINT_NOFINGER)
		   {
			   initial_state=TOMA;
			   flag=1;
		   }
	   }
	   if(initial_state==TOMA)
	   {
		   if(flag==1)
		   {
			   debugPrintlnString( "Ubique el mismo dedo nuevamente\r\n" );
		   	   flag=0;
		   }
		   device_reply=getImage();

		   if(device_reply==FINGERPRINT_OK)
		   {
			   image2Tz(2);
			   aux=createModel();
			   if(aux==FINGERPRINT_OK)
			   {
				   debugPrintlnString( "Modelo creado correctamente.\r\n" );
				   aux2=storeModel(1);
				   if(aux2==FINGERPRINT_OK)
				   {
					   debugPrintlnString( "Modelo guardado correctamente.\r\n" );
				   }else if(aux2==FINGERPRINT_BADLOCATION)
				   {
					   debugPrintlnString( "Localidad de memoria incorrecta.\r\n" );
				   }else if(aux2==FINGERPRINT_FLASHERR)
				   {
					   debugPrintlnString( "Almacenamiento en flash incorrecto.\r\n" );
				   }else
				   {
					   debugPrintlnString( "Error de almacenamiento\r\n" );
				   }
			   }else if(aux==FINGERPRINT_ENROLLMISMATCH)
			   {
				   debugPrintlnString( "Las huellas no coinciden.\r\n" );
			   }
			   initial_state=SALIDA;
			   flag=1;

		   }else if(device_reply==FINGERPRINT_IMAGEFAIL)
		   {
			   debugPrintlnString( "Error en captura\r\n" );
			   initial_state=SALIDA;
			   flag=1;
		   }
	   }
	   if(initial_state==SALIDA)
	   {
		   if(flag==1)
		   {
			   flag=0;
		   }
		   device_reply=getImage();
		   if(device_reply==FINGERPRINT_NOFINGER)
		   {
			   initial_state=ESPERA;
			   flag=1;
		   }
	   }


   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

