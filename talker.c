
// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#pragma GCC poison gets



// Global statements


// Prototypes
void funcioon_ImprimirRol (void) ;
void funcioon_ImprimirMenuu (void) ;
int askHasCharacter (
    char string[]
) ;
void funcioon_InvocarEleccioon (void) ;
void funcioon_ImplementacioonDeTuberiias (
    char* mensaje
) ;
void funcioon_ListarUsuarios (void) ;
void funcioon_ListarIntegrantes (void) ;
void funcioon_CrearGrupo (void) ;
void funcioon_EnviarMensajeIndividual (void) ;
void funcioon_EnviarMensajeGrupal (void) ;


int main ( int argc , char* argv[] ) {

    funcioon_ImprimirRol() ; 


    funcioon_InvocarEleccioon() ;


    funcioon_ImprimirRol() ; 

return 0;
}


void funcioon_ImprimirRol ( void ) {

    printf (

	"\n\n\n\n"
	"- - - - - - - - - - - - -\n"
	"	 TALKER           \n"
	"- - - - - - - - - - - - -\n"
	"\n\n\n\n"

    ) ;

}


void funcioon_ImprimirMenuu ( void ) {

    puts (

	" 0. Salir\n"
	" 1. Listar usuarios actualmente conectados\n"
	" 2. Listar usuarios incluidos en un grupo\n"
	" 3. Crear grupo de usuarios\n"
	" 4. Enviar mensaje a otro usuario\n"
	" 5. Enviar mensaje a un grupo de usuarios\n"

    ) ;

}


int askHasCharacter ( char string[] ) {

    size_t string_size = strlen (string) ;
    
    for ( int counter_i=0 ; counter_i < string_size ; counter_i++ ) {
	if ( (int)string[counter_i] < 48 || (int)string[counter_i] > 57 ) {
	    return 1 ;
	}
    }

return 0 ;
}


void funcioon_InvocarEleccioon ( void ) {

    char* caracter_opcioonElegida = (char*) calloc(10,sizeof(char)) ;
    int entero_opcioonElegida = -1 ;

    do {

	//// Invocar ...
	funcioon_ImprimirMenuu() ;

	//// Solicitar por consola la opción.
	printf ("* Opción: ") ;
	scanf ("%s",caracter_opcioonElegida) ;

	//// Verificar si la opción ingresada es un dígito.
	if ( !askHasCharacter(caracter_opcioonElegida) ) {
	    entero_opcioonElegida = atoi(caracter_opcioonElegida) ;
	}

	//// Accionar función dependiendo de la opción elegida.
	switch ( entero_opcioonElegida ) {

	    case 0 :

		funcioon_ImplementacioonDeTuberiias("¡Salir!") ;
		puts ("Este usuario se acaba de desconectar.") ;
		break ;

	    case 1 :

		funcioon_ImplementacioonDeTuberiias("Listar usuarios") ;
		funcioon_ListarUsuarios() ;
	        entero_opcioonElegida = -1 ;
	        break ;

	    case 2 :

		funcioon_ImplementacioonDeTuberiias("Listar integrantes") ;
		funcioon_ListarIntegrantes() ;
	        entero_opcioonElegida = -1 ;
		break ;

	    case 3 :

		funcioon_ImplementacioonDeTuberiias("Crear grupo") ;
		funcioon_CrearGrupo() ;
	        entero_opcioonElegida = -1 ;
		break ;

	    case 4 :

		funcioon_ImplementacioonDeTuberiias("Enviar mensaje individual") ;
		funcioon_EnviarMensajeIndividual() ;
	        entero_opcioonElegida = -1 ;
		break ;

	    case 5 :

		funcioon_ImplementacioonDeTuberiias("Enviar mensaje grupal") ;
		funcioon_EnviarMensajeGrupal() ;
	        entero_opcioonElegida = -1 ;
		break ;

	    default :

		puts ("¡Opción incorrecta!") ;
	        entero_opcioonElegida = -1 ;
		break ;

	}  //// te amo

	printf ("\n\n\n\n") ;

    } while ( entero_opcioonElegida != 0 ) ;

}


void funcioon_ImplementacioonDeTuberiias ( char* mensaje ) {

    //// Declarar un entero como identificador de archivos.
    int identificador ;

    //// Declarar un arreglo de caracteres, funciona como nombre de la tubería.
    char* nombreTuberiia = "/tmp/instrucciones" ;
    
    //// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
    //// Parámetros: nombre de la tubería, funcionalidad.
    identificador = open (nombreTuberiia,O_WRONLY) ;
    
    //// SECUENCIA PARA ENVIAR PID.
    	//// Asignar memoria a una cadena de texto para leer PID.
    	char* textoPID = (char*) calloc(10,sizeof(char)) ;
    	//// Obtener PID.
    	pid_t pid = getpid() ;
	//// Guardar PID en la cadena de texto.
    	sprintf (textoPID,"%d",pid) ;
    	//// Imprimir PID.
    	printf ("* PID: %s\n",textoPID) ;
    	//// Escribir PID en la tubería.
    	write (identificador,textoPID,10) ;

    //// SECUENCIA PARA ENVIAR INSTRUCCIÓN.
    	//// Imprimir 'mensaje'.
    	printf ("* Instrucción: %s\n\n",mensaje) ;
    	//// Escribir en la tubería.
    	write (identificador,mensaje,100) ;
    
    //// Cerrar la tubería.
    close (identificador) ;

}


void funcioon_ListarUsuarios ( void ) {

    //// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
    char* nombreTuberiia = "/tmp/usuarios" ;

    //// Declarar un entero como identificador de archivos.
    int identificador = open (nombreTuberiia,O_RDONLY) ;

    //// Asignar memoria a una cadena de texto.
    char* texto_filas = (char*) calloc(2,sizeof(char)) ;
    //// Leer el número de filas desde la tubería.
    read (identificador,texto_filas,2) ;
    //// Asignar el texto de número de filas a un dígito.
    int filas = atoi(texto_filas) ;

    //// Leer e imprimir los PIDs.
    puts ("* TALKERS") ;
    for ( int contador_i=0 ; contador_i < filas ; contador_i++ ) {
	char* texto_PID = (char*) calloc(10,sizeof(char)) ;
	read (identificador,texto_PID,10) ;
	printf ("PID: %s\n",texto_PID) ;
    }

    // Cerrar tubería.
    close (identificador) ;

}


void funcioon_ListarIntegrantes ( void ) {

    puts ("Listar integrantes") ;

}


void funcioon_CrearGrupo ( void ) {

    //// Asignar memoria a una cadena de texto para leer Group ID.
    char* texto_GroupID = (char*) calloc(5,sizeof(char)) ;

    //// Preguntar por el Group ID.
    printf ("Group ID: ") ;
    scanf ("%s",texto_GroupID) ;

    //// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
    char* nombreTuberiia = "/tmp/grupo" ;
    
    //// Declarar un entero como identificador de archivos.
    int identificador ;

    //// SECUENCIA PARA ENVIAR GID.
        //// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
   	//// Parámetros: nombre de la tubería, funcionalidad.
   	identificador = open (nombreTuberiia,O_WRONLY) ;
   	//// Escribir en la tubería.
   	write (identificador,texto_GroupID,5) ;
   	//// Cerrar la tubería.
   	close(identificador) ;

    //// SECUENCIA PARA CONFIRMAR GID.
        //// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
   	//// Parámetros: nombre de la tubería, funcionalidad.
   	identificador = open (nombreTuberiia,O_RDONLY) ;
        //// Asignar memoria a una cadena de texto para leer bandera de confirmación.
        char* texto_banderaConfirmacioon = (char*) calloc(10,sizeof(char)) ;
        //// Recibir bandera de confirmación desde la tubería.
        read (identificador,texto_banderaConfirmacioon,10) ;
        //// Imprimir bandera de confirmación.
	if ( strcmp(texto_banderaConfirmacioon,"Afirmativo") == 0 ) {
	    puts ("La creación del nuevo grupo fue exitosa.") ;
	} else {
	    puts ("La creación del grupo fue denegada.") ;
	}
   	//// Cerrar la tubería.
   	close(identificador) ;

}


void funcioon_EnviarMensajeIndividual ( void ) {

    puts ("Enviar mensaje individual") ;

}


void funcioon_EnviarMensajeGrupal ( void ) {

    puts ("Enviar mensaje grupal") ;

}




// To rest -->      
