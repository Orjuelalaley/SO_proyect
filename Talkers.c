/* 
Autor: M. Curiel
funcion: Ilustra la creaci'on de pipe nominales. 
Nota: todas las llamadas al sistema no estan validadas.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include "nom.h"

#define TAMMENSAJE 10

int fd1;
 char mensaje[TAMMENSAJE];


int main (int argc, char **argv)
{
  int  fd, pid, creado = 0, res;
  datap datos;
 
 
  
  mode_t fifo_mode = S_IRUSR | S_IWUSR;
 
  
  // Se abre el pipe cuyo nombre se recibe como argumento del main. 
  do { 
     fd = open(argv[1], O_WRONLY);
     if (fd == -1) {
         perror("pipe");
         printf(" Se volvera a intentar despues\n");
	 sleep(10);        
     } else creado = 1;
  } while (creado == 0);


  pid = getpid();
  datos.pid = pid;
  
  // Nombre de un segundo pipe
  strcpy(datos.segundopipe, "mypipe");
  // Se crea un segundo pipe para la comunicacion con el server.
  unlink("mypipe"); 
  if (mkfifo (datos.segundopipe, fifo_mode) == -1) {
     perror("Client  mkfifo");
     exit(1);
  }
  // se envia el nombre del pipe al otro proceso. 
   write(fd, &datos , sizeof(datos));

   // Se abre el segundo pipe
  creado = 0;
  do { 
     if ((fd1 = open(datos.segundopipe, O_RDONLY)) == -1) {
        perror(" Cliente  Abriendo el segundo pipe. Se volvera a intentar ");
        sleep(5);
     } else creado = 1; 
   } while (creado == 0);
 
   // Se lee un mensaje por el segundo pipe. 

    
   read(fd1, mensaje, 10);
   printf("El proceso cliente termina y lee %s \n", mensaje);
 
  exit(0);

  
}
