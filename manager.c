
#include "funciones_manager.h"

// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#pragma GCC poison gets



// Prototypes
void funcioon_EnviarSenial (
    char** matrizTemporalParaAgregarPIDsExitosos
) ;


int main ( ) {

    funcioon_ImprimirRol() ;


    //// Asignar memoria a matriz de PIDs con una sola fila.
    matriz_PIDs = (char**) calloc(100,sizeof(char*)) ;
    matriz_GIDs = (char**) calloc(100,sizeof(char*)) ;
    
    //// Leer datos desde la tubería.
    funcioon_ImplementacioonDeTuberiias() ;


    funcioon_ImprimirRol() ;

return 0 ;
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
	    char* temp = (char*) calloc(5,sizeof(char)) ;
	    //// Almacenar el PID en la cadena de texto temporal.
	    read (identificador,temp,5) ;
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
	write (identificador,matriz_PIDs[contador_i],5) ;
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

    //// Declarar un identificador para manejo de archivos.
    int identificador ;

    //// SECUENCIA PARA LEER NUEVO GID.
    	//// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
    	//// Parámetros: nombre de la tubería, funcionalidad.
    	identificador = open (nombreTuberiia,O_RDONLY) ;
    	//// Asignar memoria a una cadena de texto para guardar temporalmente un GID.
    	char* temp = (char*) calloc(5,sizeof(char)) ;
    	//// Almacenar el GID en la cadena de texto temporal.
    	read (identificador,temp,5) ;
	//// Cerrar tubería.
	close (identificador) ;
    	//// Imprimir GIP.
    	printf ("\nNuevo GID: %s\n\n",temp) ;
    	//// Invocar ...
    	int confirmarGID = funcioon_VerificarExistencia(matriz_GIDs,temp) ;

    //// SECUENCIA PARA CONFIRMAR GID.
    	//// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
    	//// Parámetros: nombre de la tubería, funcionalidad.
    	identificador = open (nombreTuberiia,O_WRONLY) ;
    	//// Verificar la existencia del GID ingresado.
    	if ( confirmarGID ) {
    	    //// Imprimir notificación de éxito.
    	    printf ("Es posible crear el GID ´%s´.\n\n",temp) ;
    	    //// Escribir una bandera de confirmación en la tubería.
    	    write (identificador,"Afirmativo",10) ;
    	} else {
    	    //// Imprimir notificación de fallo.
    	    printf ("El GID ´%s´ ya existe.\n",temp) ;
    	    //// Escribir una bandera de confirmación en la tubería.
    	    write (identificador,"Negativooo",10) ;
    	}
	//// Cerrar tubería.
	close (identificador) ;

    //// Crear un arreglo de PIDs.
    char** matriz_temp = (char**) calloc(100,sizeof(char*)) ;

    //// Invocar ...
    int confirmarUsuarios = funcioon_VerificarUsuarios(temp,matriz_temp) ;

    //// Verificar la existencia del GID ingresado.
    if ( confirmarGID && confirmarUsuarios ) {
	//// Obtener la última fila de la matriz de GIDs.
        int uultimaFila = funcioon_CalcularUultimaFilaMatriz(matriz_GIDs) ;
	//// Asignar memoria a la última fila de la matriz.
	matriz_GIDs[uultimaFila] = (char*) calloc(5,sizeof(char)) ;
	//// Almacenar el GID en la matriz.
	strcpy (matriz_GIDs[uultimaFila],temp) ;
	//// Imprimir notificación de éxito.
	puts ("\n¡Nuevo GID guardado!") ;
	//// Invocar ...
	funcioon_EnviarSenial(matriz_temp) ;
    } else {
	//// Imprimir notificación de fallo.
	printf ("\nNo es posible crear el GID ´%s´.\n",temp) ;
    }

    //// Cerrar la tubería.
    close(identificador) ;

}


int funcioon_VerificarUsuarios ( char* gid , char** matriz_temp ) {

    //// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
    char* nombreTuberiia = "/tmp/nuevos" ;

    //// Crear tubería.
    mkfifo (nombreTuberiia,0666) ;

    //// Declarar un identificador para abrir tubería.
    int identificador ;
    //// Inicializar bandera para confirmación de PIDs.
    int bandera = 1 ;
    //// Número de usuarios ingresados.
    int usuarios = 0 ;

    do {

	//// Inicializar un identificador para abrir tubería.
	identificador = open (nombreTuberiia,O_RDONLY) ;
	//// Asignar memoria a una cadena de texto.
	char* texto_lectura = (char*) calloc(6,sizeof(char)) ;
	//// Leer contenido desde la tubería.
	read (identificador,texto_lectura,6) ;
	//// Cerrar tubería.
	close (identificador) ;

	//// Verificar el contenido de la lectura.
	if ( strcmp(texto_lectura,"0") == 0 ) {

	    //// Inicializar un identificador para abrir tubería. 
            identificador = open (nombreTuberiia,O_WRONLY) ;

	    if ( usuarios == 0 ) {
		//// Imprimir notificación de fallo.
		puts ("No puede crearse un grupo sin usuarios.") ;
		//// Enviar confirmación negativa de creación.
		write (identificador,"0",1) ;
		//// Actualizar bandera.
		bandera = 0 ;
	    }

	    //// Cerrar la tubería.
	    close (identificador) ;
	    //// Imprimir notificación.
	    puts ("\nSaliendo de recibir PIDs.") ;
	    //// Terminar con la lectura de PIDs.
	    break ;

	} else if ( funcioon_VerificarExistencia(matriz_PIDs,texto_lectura) == 0 ) {

	    //// Inicializar un identificador para abrir tubería. 
            identificador = open (nombreTuberiia,O_WRONLY) ;
	    //// Imprimir notificación.
	    printf ("El usuario ´%s´ existe para la creación del grupo ´%s´.\n",texto_lectura,gid) ;
	    //// Enviar confirmación afirmativa de existencia.
	    write (identificador,"1",1) ;
	    //// Cerrar la tubería.
	    close (identificador) ;
	    //// Obtener la última fila de la matriz.
	    int fila = funcioon_CalcularUultimaFilaMatriz(matriz_temp) ;
	    //// Guardar en la última fila de la matriz el último PID exitoso.
	    matriz_temp[fila] = (char*) calloc(6,sizeof(char)) ;
	    strcpy (matriz_temp[fila],texto_lectura) ;
	    //// Actualizar número de usuarios.
	    usuarios++ ;

	} else {

	    //// Inicializar un identificador para abrir tubería. 
            identificador = open (nombreTuberiia,O_WRONLY) ;
	    //// Imprimir notificación.
	    printf ("El usuario ´%s´ no existe para la creación del grupo ´%s´.\n",texto_lectura,gid) ;
	    //// Enviar confirmación negativa de existencia.
	    write (identificador,"0",1) ;
	    //// Cerrar la tubería.
	    close (identificador) ;
	    //// Actualizar bandera.
	    bandera = 0 ;

	}

    } while ( bandera ) ;

return bandera ;
}


void funcioon_EnviarSenial ( char** matriz ) {

    puts ("\nEste es un mensaje desde señal.\n") ;

    //// Obtener el número de filas de la matriz de PIDs.
    int filas = funcioon_CalcularUultimaFilaMatriz(matriz) ;

    //// Recorrer todo el arreglo de PIDs temporales para mandar señal.
    for ( int contador_i=0 ; contador_i < filas ; contador_i++ ) {
	//// Convertir cada fila en un dígito entero.
	int pid_temp = atoi(matriz[contador_i]) ;
	//// Mandar señal.
	kill (pid_temp,SIGUSR1) ;
    }

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
