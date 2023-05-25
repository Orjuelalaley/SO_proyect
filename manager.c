
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
char** matriz_PIDs ;
char** matriz_GIDs ;


// Prototypes
void funcioon_ImprimirRol (void) ;
void funcioon_ImplementacioonDeTuberiias (void) ;
int funcioon_CalcularUultimaFilaMatriz (
    char** matriz_contar
) ;
int funcioon_VerificarExistencia (
    char** matriz_buscar ,
    char* texto_PID_verificarExistente
) ;
void funcioon_AccionarMenuu (
    char* instruccioon ,
    char* pid
) ;
void funcioon_ImprimirMatriz (
    char** matriz_imprimir ,
    char* mensaje_imprimir ,
    char* etiqueta_imprimir
) ;
void funcioon_EnviarListaUsuarios (void) ;
void funcioon_CrearGrupo (void) ;
void funcioon_EliminarPID (
    char* texto_PID_eliminar
) ;


int main ( ) {

    funcioon_ImprimirRol() ;


    //// Asignar memoria a matriz de PIDs con una sola fila.
    matriz_PIDs = (char**) calloc(100,sizeof(char*)) ;
    matriz_GIDs = (char**) calloc(100,sizeof(char*)) ;
    
    //// Leer datos desde la tubería.
    funcioon_ImplementacioonDeTuberiias() ;


    funcioon_ImprimirRol() ;

return 0;
}


void funcioon_ImprimirRol ( void ) {

    printf (

	"\n\n\n\n"
	"- - - - - - - - - - - - -\n"
	"	 MANAGER         \n"
	"- - - - - - - - - - - - -\n"
	"\n\n\n\n"

    ) ;

}


void funcioon_ImplementacioonDeTuberiias ( void ) {

    //// Declarar un entero como identificador de archivos.
    int identificador ;

    //// Declarar un arreglo de caracteres, funciona como nombre de la tubería.
    char* nombreTuberiia = "/tmp/instrucciones" ;
    
    //// Crear una tubería.
    //// Parámetros: nombre de la tubería, permisos de tubería.
    mkfifo (nombreTuberiia,0666) ;
    
    while ( __STDC__ ) {

    	//// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
    	//// Parámetros: nombre de la tubería, funcionalidad.
    	identificador = open (nombreTuberiia,O_RDONLY) ;

    	//// SECUENCIA PARA LEER PID.
	    //// Asignar memoria a una cadena de texto para guardar temporalmente un PID.
	    char* temp = (char*) calloc(10,sizeof(char)) ;
	    //// Almacenar el PID en la cadena de texto temporal.
	    read (identificador,temp,10) ;
    	    //// Obtener el número de filas de la matriz de PIDs.
    	    int nuumero_UultimaFila = funcioon_CalcularUultimaFilaMatriz(matriz_PIDs) ;
	    //// Verificar PIDs ya existentes.
	    if ( funcioon_VerificarExistencia(matriz_PIDs,temp) || nuumero_UultimaFila==0 ) {
    	    	//// Asignar memoria a la última fila de la matriz.
    	    	matriz_PIDs[nuumero_UultimaFila] = (char*) calloc(10,sizeof(char)) ;
    	    	//// Almacenar el PID en la última fila de la matriz.
    	    	strcpy(matriz_PIDs[nuumero_UultimaFila],temp) ;
		//// Imprimir notificación.
		puts ("¡Nuevo PID guardado!\n") ;
	    }

    	//// SECUENCIA PARA LEER INSTRUCCIÓN.
    	    //// Asignar memoria a una cadena de texto para leer mensaje.
    	    char* instruccioon = (char*) calloc(100,sizeof(char)) ;
    	    //// Leer instrucción desde la tubería.
    	    read (identificador,instruccioon,100) ;
    	    //// Imprimir instrucción.
    	    // printf ("* Instrucción: %s\n",instruccioon) ;

	//// Convertir una instrucción a una función.
	funcioon_AccionarMenuu (instruccioon,temp) ;

    	//// Cerrar la tubería.
    	close (identificador) ;

    }

}


int funcioon_CalcularUultimaFilaMatriz ( char** matriz ) {

    int filas=0 ;

    while ( matriz[filas] != NULL ) {
	filas++ ;
    }

return filas;
}


int funcioon_VerificarExistencia ( char** matriz , char* texto_pid ) {

    //// Obtener el número de filas que posee la matriz de PIDs.
    int filasMatriz = funcioon_CalcularUultimaFilaMatriz(matriz) ;

    //// Recorrer toda la matriz para encontrar PID repetido.
    for ( int contador_i=0 ; contador_i < filasMatriz ; contador_i++ ) {
	if ( strcmp(texto_pid,matriz[contador_i]) == 0 ) {
	    return 0 ;
	}
    }

return 1 ;
}


void funcioon_AccionarMenuu ( char* instruccioon , char* pid ) {

    //// Imprimir instrucción.
    printf ("* Instrucción: %s\n",instruccioon) ;
    //// Imprimir PID.
    printf ("* PID: %s\n\n",pid) ;

    //// Evaluar la elección de la 'instrucción'.
    if ( strcmp(instruccioon,"Listar usuarios") == 0 ) {
	funcioon_ImprimirMatriz(matriz_PIDs,"TALKERS","PID") ;
	funcioon_EnviarListaUsuarios() ;
    } else if ( strcmp(instruccioon,"Listar integrantes") == 0 ) {
        puts (instruccioon) ;
    } else if ( strcmp(instruccioon,"Crear grupo") == 0 ) {
        funcioon_CrearGrupo() ;
    } else if ( strcmp(instruccioon,"Enviar mensaje individual") == 0 ) {
        puts (instruccioon) ;
    } else if ( strcmp(instruccioon,"Enviar mensaje grupal") == 0 ) {
        puts (instruccioon) ;
    } else if ( strcmp(instruccioon,"¡Salir!") == 0 ) {
        funcioon_EliminarPID(pid) ;
    } else {
	puts ("\n!Error al leer instrucción!") ;
    }

    puts ("\n\n\n") ;

}


void funcioon_ImprimirMatriz ( char** matriz , char* msg , char* etiqueta ) {

    //// Obtener el número de filas que posee la matriz de PIDs.
    int filasMatriz = funcioon_CalcularUultimaFilaMatriz(matriz) ;

    //// Imprimir todos los PIDs de la matriz.
    printf ("* %s\n",msg) ;
    for ( int contador_i=0 ; contador_i < filasMatriz ; contador_i++ ) {
        printf ("%s: %s\n",etiqueta,matriz[contador_i]) ;
    }

}


void funcioon_EnviarListaUsuarios ( void ) {

    //// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
    char* nombreTuberiia = "/tmp/usuarios" ;
    
    //// Crear una tubería.
    //// Parámetros: nombre de la tubería, permisos de tubería.
    mkfifo (nombreTuberiia,0666) ;

    //// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
    //// Parámetros: nombre de la tubería, funcionalidad.
    int identificador = open (nombreTuberiia,O_WRONLY) ;

    //// Obtener el tamaño de filas de la matriz de PIDs.
    int filas = funcioon_CalcularUultimaFilaMatriz(matriz_PIDs) ;
    //// Asignar memoria a una cadena de texto.
    char* texto_filas = (char*) calloc(2,sizeof(char)) ;
    //// Asignar el valor de filas a la cadena de texto.
    sprintf (texto_filas,"%d",filas) ;
    //// Enviar el número de PIDs.
    write (identificador,texto_filas,2) ;

    //// Enviar todos los PIDs.
    for ( int contador_i=0 ; contador_i < filas ; contador_i++ ) {
	write (identificador,matriz_PIDs[contador_i],10) ;
    }

    //// Cerrar la tubería.
    close (identificador) ;

}


void funcioon_CrearGrupo ( void ) {

    //// Imprimir todos los GIDs registrados.
    funcioon_ImprimirMatriz (matriz_GIDs,"GIDs existentes","GID") ;

    //// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
    char* nombreTuberiia = "/tmp/grupo" ;
    
    //// Crear una tubería.
    //// Parámetros: nombre de la tubería, permisos de tubería.
    mkfifo (nombreTuberiia,0666) ;

    //// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
    //// Parámetros: nombre de la tubería, funcionalidad.
    int identificador = open (nombreTuberiia,O_RDWR) ;

    //// Asignar memoria a una cadena de texto para guardar temporalmente un GID.
    char* temp = (char*) calloc(5,sizeof(char)) ;
    //// Almacenar el GID en la cadena de texto temporal.
    read (identificador,temp,5) ;

    //// Imprimir GIP.
    printf ("\nNuevo GID: %s\n",temp) ;

    //// Verificar la existencia del GID ingresado.
    if ( funcioon_VerificarExistencia(matriz_GIDs,temp) ) {
	//// Obtener la última fila de la matriz de GIDs.
        int uultimaFila = funcioon_CalcularUultimaFilaMatriz(matriz_GIDs) ;
	//// Asignar memoria a la última fila de la matriz.
	matriz_GIDs[uultimaFila] = (char*) calloc(5,sizeof(char)) ;
	//// Almacenar el GID en la matriz.
	strcpy (matriz_GIDs[uultimaFila],temp) ;
	//// Imprimir notificación de éxito.
	puts ("¡Nuevo GID guardado!") ;
	//// Escribir una bandera de confirmación en la tubería.
	write (identificador,"Afirmativo",10) ;
    } else {
	//// Escribir una bandera de confirmación en la tubería.
	write (identificador,"Negativo",8) ;
	//// Imprimir notificación de fallo.
	printf ("El GID ´%s´ ya existe.\n",temp) ;
    }

    //// Cerrar la tubería.
    close(identificador) ;

}


void funcioon_EliminarPID ( char* texto_pid_eliminar ) {

    //// Obtener el número de filas que posee la matriz de PIDs.
    int filasMatriz = funcioon_CalcularUultimaFilaMatriz(matriz_PIDs) ;

    //// Recorrer toda la matriz para encontrar PID inactivo.
    for ( int contador_i=0 ; contador_i < filasMatriz ; contador_i++ ) {
	if ( strcmp(texto_pid_eliminar,matriz_PIDs[contador_i]) == 0 ) {
	    matriz_PIDs[contador_i] = 0 ;
	    printf ("El PID #%s se ha desconectado.\n",texto_pid_eliminar) ;
	}
    }

    //// Recorrer toda la matriz para reacomodarla.
    for ( int contador_i=0 ; contador_i < filasMatriz ; contador_i++ ) {
	if ( matriz_PIDs[contador_i] == 0  &&  (contador_i+1) < filasMatriz ) {
	    matriz_PIDs[contador_i] = matriz_PIDs[contador_i+1] ;
	}
    }

}




// To rest -->      
