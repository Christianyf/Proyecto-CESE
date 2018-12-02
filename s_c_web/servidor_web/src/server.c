#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "ClientData.h"
#include <pthread.h>



struct {

	int fd;
	pthread_t thread;
	int flagFree;
}S_ClientData;

typedef struct {
	int dat1;
	char dat2;
	int dat3[3]; 
}ejemplo;

ejemplo datos;

typedef struct S_ClientData ClientData;

void maquina(void);

static ClientData conexiones[100];////base de datos de los clientes
///////////////////////////////////////////

void* atenderCliente(void* arg){

	//int newfd;
	//char buffer[128];
	
	ClientData* pData = (ClientData*)arg;//para poder acceder a los datos de determinada conexion "logear"
	
	//newfd=pData->fd;//guardo en newfd el fd de la nueva comunicacion alojada///////////////////////////7

	while(1){
		int n=read(pData->fd,&datos,sizeof(datos));
			if(n==0){//probar con || n==-1

				break;//implica error en la comunicacion se cayo la conexion.
			}
			
		printf("Recibi %d bytes\n",n);
		maquina();
		//write(pData->fd,"hola",5);
		//probar cerrar aqui
		
	}

	close(pData->fd);//se cierra el proceso del thread, siempre cuidar de cerrar
	pData->flagFree=1;
	
	//close(fd);//****************************************
	
	//exit(1);//cuidado sin esto da warning, verifica funcionamiento
	
}
////////////////////////////////////////////////////////////////////

void lanzarThreadParaCliente(int newfd){

	//verificar un lugar libre en la base de datos
	int index = cd_getFreeIndex(conexiones,100);

	if(index==-1){
		close(newfd);
		return;
	}
	
	//creo el thread
	conexiones[index].flagFree=0;
	conexiones[index].fd=newfd;
	
	int ret=pthread_create(&conexiones[index].thread,NULL,atenderCliente,&conexiones[index]);

	if(ret==-1){//si no se puede crear el thread se debe cancelar la conexion y dejar el espacio como vacio en la base de datos

		conexiones[index].flagFree=1;
		close(newfd);
		return;
	}

	return;

}
///////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////

int main(void)
{	
	//estructuras para almacenar la direccion del servidor y cliente
	socklen_t addr_len;
	struct sockaddr_in clientaddr;
	struct sockaddr_in serveraddr;
	
	char buffer[128];
	int newfd;
	int n;

	cd_init(conexiones,100);//inicializa el vector 1/100, levanta las flags (1)

	// Creamos socket
	int s = socket(AF_INET,SOCK_STREAM, 0);

	// Cargamos datos de IP:PORT del server
    	bzero((char*) &serveraddr, sizeof(serveraddr));
    	serveraddr.sin_family = AF_INET;
    	serveraddr.sin_port = htons(4096);
    	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    	if(serveraddr.sin_addr.s_addr==INADDR_NONE)
    	{
        	fprintf(stderr,"ERROR invalid server IP\r\n");
        	return 1;
    	}

	// Abrimos puerto con bind()
	if (bind(s, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == -1) {
		close(s);
		perror("listener: bind");
		return 1;
	}

	// Seteamos socket en modo Listening
	if (listen (s, 10) == -1) // backlog=10
  	{
    	    	perror("error en listen");
    		exit(1);
  	}

	while(1)
	{
		// Ejecutamos accept() para recibir conexiones entrantes
		addr_len = sizeof(struct sockaddr_in);
    		
		if ( (newfd = accept(s, (struct sockaddr *)&clientaddr, &addr_len)) == -1)
      		{
		      perror("error en accept");
		      exit(1);
	    	}
	 	printf  ("server:  conexion desde:  %s\n", inet_ntoa(clientaddr.sin_addr));


		//lanzarThreadParaCliente(newfd);/////////////////////////////////
		if( (n = read(newfd,buffer,128)) == -1 )
		{
			perror("Error leyendo mensaje en socket");
			exit(1);
		}
		buffer[n]=0;
		printf("Recibi %d bytes.:%s\n",n,buffer);
		
		if (strcmp(buffer, "Pagina") ==0){
			printf("Bien carajo\n");
			if (send(newfd,"holis",6,0) == -1)
    			{
      				perror("Error escribiendo mensaje en socket");
      				exit (1);
    			}
    			
			
		}

		
	}
	
	close(s);//modificado cuidado

	return 0;
}
//////////////////////////////////////////////////////////////////////////
void maquina(void)
{
	if(datos.dat1==1){
	printf("llega evento\n");
	}

}


/////////////////////////funcion del thread (proceso paralelo)/////////////////////////////////////////////////



//si read devuelve un cero es porque se cerro la conexion
//habilitar el lock y el detached, extra para mejorar la performance
//exit cierra la conexion usar mejor break o return (probar)
//chmod para dar permisos










