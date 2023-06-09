
// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "funciones_manager.h"

#pragma GCC poison gets



// Global statements
char*** matriz_GID_X_PIDs ;


// Prototypes
void funcioon_EnviarListaMiembros (void) ;
int funcioon_BuscarGID (
    char* gid
) ;
void funcioon_ListarMiembros (
    int filaEnDondeSeEncuentraElGID
) ;
void funcioon_NoListarMiembros (void) ;
void funcioon_EnviarSenial (
    char** matrizTemporalParaAgregarPIDsExitosos ,
    char* gidParaEnviarAlUsuario
) ;
int funcioon_ContarFilas3D (void) ;
void funcioon_Imprimir3D (void) ;


int main ( ) {

    funcioon_ImprimirRol() ;


    //// Asignar memoria a matrices.
    matriz_GID_X_PIDs = (char***) calloc(100,sizeof(char**)) ;
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
        funcioon_EnviarListaMiembros() ;
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
    for ( int contador_i=0 ; contador_i <= filasMatriz ; contador_i++ ) {
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


void funcioon_EnviarListaMiembros ( void ) {

    //// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
    char* nombreTuberiia = "/tmp/usuarios" ;
    
    //// Crear una tubería.
    //// Parámetros: nombre de la tubería, permisos de tubería.
    mkfifo (nombreTuberiia,0666) ;

    //// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
    //// Parámetros: nombre de la tubería, funcionalidad.
    int identificador = open (nombreTuberiia,O_RDONLY) ;

    //// Asignar memoria a una cadena de texto para almacenar GID.
    char* temp_gid = (char*) calloc(5,sizeof(char)) ;
    //// Leer desde la tubería el GID.
    read (identificador,temp_gid,5) ;

    //// Imprimir mensaje.
    printf ("Buscando %s...\n",temp_gid) ;

    //// Cerrar la tubería.
    close (identificador) ;

    int bandera = funcioon_BuscarGID (temp_gid) ;

    if ( bandera >= 0 ) {

	printf ("El GID #%s existe.\n",temp_gid) ;
	funcioon_ListarMiembros(bandera) ;

    } else {

	printf ("El GID #%s no existe.\n",temp_gid) ;
	funcioon_NoListarMiembros() ;

    }

}


int funcioon_BuscarGID ( char* gid ) {

    for ( int contador_i=0 ; matriz_GID_X_PIDs[contador_i] != NULL ; contador_i++ ) {
	printf ("... %s\n",matriz_GID_X_PIDs[contador_i][0]) ;
	if ( strcmp(matriz_GID_X_PIDs[contador_i][0],gid) == 0 ) {
	    return contador_i ;
	}
    }

return -1 ;
}


void funcioon_ListarMiembros ( int fila ) {

    //// SECUENCIA PARA MANDAR BANDERA.
        //// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
        char* nombreTuberiia = "/tmp/bandera" ;
        //// Crear una tubería.
        //// Parámetros: nombre de la tubería, permisos de tubería.
        mkfifo (nombreTuberiia,0666) ;
        //// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
        //// Parámetros: nombre de la tubería, funcionalidad.
        int identificador = open (nombreTuberiia,O_WRONLY) ;
        //// Enviar por la tubería la bandera de confirmación.
        write (identificador,"1",1) ;
        //// Cerrar tubería de bandera.
        close (identificador) ;

    //// SECUENCIA PARA MANDAR DATOS.
        //// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
        nombreTuberiia = "/tmp/miembros" ;
        //// Crear una tubería.
        //// Parámetros: nombre de la tubería, permisos de tubería.
        mkfifo (nombreTuberiia,0666) ;
        //// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
        //// Parámetros: nombre de la tubería, funcionalidad.
        identificador = open (nombreTuberiia,O_WRONLY) ;

        //// Obtener la última celda de la fila.
        int fila_matriz = funcioon_CalcularUultimaFilaMatriz (matriz_GID_X_PIDs[fila]) - 1 ;
        //// Convertir la última celda a cadena de texto.
        char* texto_fila_matriz = (char*) calloc(1,sizeof(char)) ;
        sprintf (texto_fila_matriz,"%d",fila_matriz) ;
        //// Enviar el número de elementos por la tubería.
        write (identificador,texto_fila_matriz,1) ;

        puts ("\nListando miembros... ") ;
        for ( int contador_i=1 ; matriz_GID_X_PIDs[fila][contador_i] != NULL ; contador_i++  ) {
            printf ("PID: %s\n",matriz_GID_X_PIDs[fila][contador_i]) ;
            write (identificador,matriz_GID_X_PIDs[fila][contador_i],4) ;
        }

        //// Cerrar la tubería.
        close (identificador) ;

}


void funcioon_NoListarMiembros ( void ) {

    //// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
    char* nombreTuberiia = "/tmp/bandera" ;
    //// Crear una tubería.
    //// Parámetros: nombre de la tubería, permisos de tubería.
    mkfifo (nombreTuberiia,0666) ;
    //// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
    //// Parámetros: nombre de la tubería, funcionalidad.
    int identificador = open (nombreTuberiia,O_WRONLY) ;
    //// Enviar por la tubería la bandera de confirmación.
    write (identificador,"0",1) ;
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
	funcioon_EnviarSenial(matriz_temp,temp) ;
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

	//// Cerrar la tubería.
	close (identificador) ;

    } while ( bandera ) ;

return bandera ;
}


void funcioon_EnviarSenial ( char** matriz , char* gid ) {

    puts ("\nEnviando notificaciones...") ;

    //// Obtener el número de filas de la matriz de PIDs.
    int filas = funcioon_CalcularUultimaFilaMatriz(matriz) ;

    //// Obtener la última fila de la matriz 3D.
    int filas_3D = funcioon_ContarFilas3D() ;
    //// Asignar memoria a la última fila de la matriz.
    matriz_GID_X_PIDs[filas_3D] = (char**) calloc(filas+2,sizeof(char*)) ;
    //// Asignar memoria a la primera celda de la matriz para guardar el GID.
    matriz_GID_X_PIDs[filas_3D][0] = (char*) calloc(5,sizeof(char)) ;
    //// Copiar en la primera celda el nuevo GID.
    strcpy (matriz_GID_X_PIDs[filas_3D][0],gid) ;

    //// Recorrer todo el arreglo de PIDs temporales para mandar señal.
    for ( int contador_i=0 ; contador_i < filas ; contador_i++ ) {

	//// Convertir cada fila en un dígito entero.
	int pid_temp = atoi(matriz[contador_i]) ;
	//// Mandar señal.
	kill (pid_temp,SIGUSR1) ;
	//// Asignar a una cadena de texto el nombre de la tubería.
	char* nombreTuberiia = (char*) calloc(12,sizeof(char)) ;
	strcat (nombreTuberiia,"/tmp/") ;
	strcat (nombreTuberiia,matriz[contador_i]) ;
	//// Crear una tubería para pasar el GID.
	mkfifo (nombreTuberiia,0666) ;
	//// Inicializar un identificador para el manejo de tuberías.
	int identificador = open (nombreTuberiia,O_WRONLY) ;
	//// Escribir en la tubería el GID.
	write (identificador,gid,5) ;
	//// Cerrar la tubería.
	close (identificador) ;
	//// Imprimir notificación.
	printf ("El PID #%s ahora pertenece al GID #%s.\n",matriz[contador_i],gid) ;

	//// SECUENCIA PARA RELACIONAR GID CON PIDs.
	    //// Asignar memoria a cada celda de la matriz 3D.
	    matriz_GID_X_PIDs[filas_3D][contador_i+1] = (char*) calloc(5,sizeof(char)) ;
	    //// Copiar cada nuevo PID en la celda.
	    strcat (matriz_GID_X_PIDs[filas_3D][contador_i+1],matriz[contador_i]) ;

    }

    puts ("\n¡Actualización en la matriz de GID_X_PIDs!") ;
    funcioon_Imprimir3D() ;

}


int funcioon_ContarFilas3D ( void ) {

    int filas = 0 ;

    while ( matriz_GID_X_PIDs[filas] != NULL ) {
	filas++ ;
    }

return filas ;
}


void funcioon_Imprimir3D ( void ) {

    for ( int contador_i=0 ; matriz_GID_X_PIDs[contador_i] != NULL ; contador_i++ ) {
	for ( int contador_j=0 ; matriz_GID_X_PIDs[contador_i][contador_j] != NULL ; contador_j++ ) {
	    printf (" %s |",matriz_GID_X_PIDs[contador_i][contador_j]) ;
	}
	puts ("") ;
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
