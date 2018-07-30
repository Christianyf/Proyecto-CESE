#include "complementario.h"
#include <gtk/gtk.h>

/*typedef struct {
	char	clave[30];
	int	indice_lectura;
	int	indice_escritura;
	
}buffer;*/

//static buffer buffer_clave;

void escribir_buffer()
{
	printf("%d\r\n",buffer_clave.indice_escritura);	
}
