
// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "funciones_talker.h"
#pragma GCC poison gets

int main(int argc, char *argv[])
{

	funcioon_ImprimirRol();

	matriz_GIDs = (char **)calloc(100, sizeof(char *));

	funcioon_InvocarEleccioon();

	funcioon_ImprimirRol();

	return 0;
}

void funcioon_ImprimirRol(void)
{

	printf(
		"\n\n\n\n"
		"- - - - - - - - - - - - -\n"
		"	 TALKER           \n"
		"- - - - - - - - - - - - -\n"
		"\n\n\n\n");
}

void funcioon_ImprimirMenuu(void)
{

	puts(

		" 0. Salir\n"
		" 1. Listar usuarios actualmente conectados\n"
		" 2. Listar usuarios incluidos en un grupo\n"
		" 3. Crear grupo de usuarios\n"
		" 4. Enviar mensaje a otro usuario\n"
		" 5. Enviar mensaje a un grupo de usuarios\n"

	);
}

int askHasCharacter(char string[])
{

	size_t string_size = strlen(string);

	for (int counter_i = 0; counter_i < string_size; counter_i++)
	{
		if ((int)string[counter_i] < 48 || (int)string[counter_i] > 57)
		{
			return 1;
		}
	}

	return 0;
}

void funcioon_InvocarEleccioon(void)
{

	char *caracter_opcioonElegida = (char *)calloc(10, sizeof(char));
	int entero_opcioonElegida = -1;

	do
	{

		//// Invocar ...
		funcioon_ImprimirMenuu();

		//// Solicitar por consola la opción.
		printf("* Opción: ");
		scanf("%s", caracter_opcioonElegida);

		//// Verificar si la opción ingresada es un dígito.
		if (!askHasCharacter(caracter_opcioonElegida))
		{
			entero_opcioonElegida = atoi(caracter_opcioonElegida);
		}

		//// Accionar función dependiendo de la opción elegida.
		switch (entero_opcioonElegida)
		{

		case 0:

			funcioon_ImplementacioonDeTuberiias("¡Salir!");
			puts("Este usuario se acaba de desconectar.");
			break;

		case 1:

			funcioon_ImplementacioonDeTuberiias("Listar usuarios");
			funcioon_ListarUsuarios();
			entero_opcioonElegida = -1;
			break;

		case 2:

			funcioon_ImplementacioonDeTuberiias("Listar integrantes");
			funcioon_ListarIntegrantes();
			entero_opcioonElegida = -1;
			break;

		case 3:

			funcioon_ImplementacioonDeTuberiias("Crear grupo");
			funcioon_CrearGrupo();
			entero_opcioonElegida = -1;
			break;

		case 4:

			funcioon_ImplementacioonDeTuberiias("Enviar mensaje individual");
			funcioon_EnviarMensajeIndividual();
			entero_opcioonElegida = -1;
			break;

		case 5:

			funcioon_ImplementacioonDeTuberiias("Enviar mensaje grupal");
			funcioon_EnviarMensajeGrupal();
			entero_opcioonElegida = -1;
			break;

		default:

			puts("¡Opción incorrecta!");
			entero_opcioonElegida = -1;
			break;

		} //// te amo

		printf("\n\n\n\n");

	} while (entero_opcioonElegida != 0);
}

void funcioon_ImplementacioonDeTuberiias(char *mensaje)
{

	//// Declarar un entero como identificador de archivos.
	int identificador;

	//// Declarar un arreglo de caracteres, funciona como nombre de la tubería.
	char *nombreTuberiia = "/tmp/instrucciones";

	//// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
	//// Parámetros: nombre de la tubería, funcionalidad.
	identificador = open(nombreTuberiia, O_WRONLY);

	//// SECUENCIA PARA ENVIAR PID.
	//// Asignar memoria a una cadena de texto para leer PID.
	char *textoPID = (char *)calloc(5, sizeof(char));
	//// Obtener PID.
	pid_t pid = getpid();
	//// Guardar PID en la cadena de texto.
	sprintf(textoPID, "%d", pid);
	//// Imprimir PID.
	printf("* PID: %s\n", textoPID);
	//// Escribir PID en la tubería.
	write(identificador, textoPID, 5);

	//// SECUENCIA PARA ENVIAR INSTRUCCIÓN.
	//// Imprimir 'mensaje'.
	printf("* Instrucción: %s\n\n", mensaje);
	//// Escribir en la tubería.
	write(identificador, mensaje, 100);

	//// Cerrar la tubería.
	close(identificador);
}

int funcioon_CalcularUultimaFilaMatriz(char **matriz)
{

	int filas = 0;

	while (matriz[filas] != NULL)
	{
		filas++;
	}

	return filas;
}

void funcioon_ListarUsuarios(void)
{

	//// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
	char *nombreTuberiia = "/tmp/usuarios";

	//// Declarar un entero como identificador de archivos.
	int identificador = open(nombreTuberiia, O_RDONLY);

	//// Asignar memoria a una cadena de texto.
	char *texto_filas = (char *)calloc(2, sizeof(char));
	//// Leer el número de filas desde la tubería.
	read(identificador, texto_filas, 2);
	//// Asignar el texto de número de filas a un dígito.
	int filas = atoi(texto_filas);

	//// Leer e imprimir los PIDs.
	puts("* TALKERS");
	for (int contador_i = 0; contador_i < filas; contador_i++)
	{
		char *texto_PID = (char *)calloc(5, sizeof(char));
		read(identificador, texto_PID, 5);
		printf("PID: %s\n", texto_PID);
	}

	// Cerrar tubería.
	close(identificador);
}

void funcioon_ListarIntegrantes(void)
{

	puts("Listar integrantes");
}

void funcioon_CrearGrupo(void)
{

	//// Asignar memoria a una cadena de texto para leer Group ID.
	char *texto_GroupID = (char *)calloc(5, sizeof(char));

	//// Preguntar por el Group ID.
	printf("Group ID: ");
	scanf("%s", texto_GroupID);

	//// Inicializar un arreglo de caracteres, funciona como nombre de la tubería.
	char *nombreTuberiia = "/tmp/grupo";

	//// Declarar un entero como identificador de archivos.
	int identificador;

	//// SECUENCIA PARA ENVIAR GID.

	//// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
	//// Parámetros: nombre de la tubería, funcionalidad.
	identificador = open(nombreTuberiia, O_WRONLY);
	//// Escribir en la tubería.
	write(identificador, texto_GroupID, 5);
	//// Cerrar la tubería.
	close(identificador);

	//// SECUENCIA PARA CONFIRMAR GID.

	//// Abrir la tubería ya creada, solo para la funcionalidad de escritura.
	//// Parámetros: nombre de la tubería, funcionalidad.
	identificador = open(nombreTuberiia, O_RDONLY);
	//// Asignar memoria a una cadena de texto para leer bandera de confirmación.
	char *texto_banderaConfirmacioon = (char *)calloc(10, sizeof(char));
	//// Recibir bandera de confirmación desde la tubería.
	read(identificador, texto_banderaConfirmacioon, 10);

	//// Verificar bandera de confirmación.
	int confirmarGID = strcmp(texto_banderaConfirmacioon, "Afirmativo");
	//// Invocar ...
	int confirmarUsuarios = funcioon_ElegirUsuarios(texto_GroupID);

	//// Imprimir banderas de confirmación.
	if (confirmarGID == 0 && confirmarUsuarios == 1)
	{

		//// Imprimir notificación se éxito.
		puts("La creación del nuevo GID fue exitosa.");

		//// SECUENCIA PARA GUARDAR GID.

		//// Obtener la última posición de la matriz de GIDs.
		int filas_matriz = funcioon_CalcularUultimaFilaMatriz(matriz_GIDs);
		//// Asignar memoria a la última fila de la matriz de GIDs.
		matriz_GIDs[filas_matriz] = (char *)calloc(5, sizeof(char));
		//// Almacenar el GID en la última fila de la matriz.
		strcpy(matriz_GIDs[filas_matriz], texto_GroupID);
	}
	else
	{

		//// Imprimir notificación de fracaso.
		printf("La creación del GID ´%s´ fue denegada.", texto_GroupID);
	}

	//// Cerrar la tubería.
	close(identificador);
}

int funcioon_ElegirUsuarios(char *gid)
{

	//// Preguntar los usuarios.
	printf("\n- Elegir los usuarios del grupo ´%s´:\n", gid);
	puts("- (Salir con número cero)");

	//// Inicializar cadena de texto con el nombre de la tubería.
	char *nombreTuberiia = "/tmp/nuevos";

	//// Inicializar bandera para confirmación de PIDs.
	int bandera = 1;

	do
	{

		//// Asignar memoria a una cadena de texto.
		char *texto = (char *)calloc(6, sizeof(char));
		//// Solicitar por consola un PID.
		printf("PID: ");
		scanf("%s", texto);

		//// Inicializar un identificador para abrir tubería.
		int identificador = open(nombreTuberiia, O_RDWR);

		//// Verificar lectura continua.
		if (strcmp(texto, "0") == 0)
		{

			//// Escribir en tubería bandera para terminar con lectura.
			write(identificador, "0", 1);

			//// Asignar memoria a una cadena de texto.
			char *texto_confirmacioon = (char *)calloc(1, sizeof(char));
			//// Leer confirmación de tubería.
			read(identificador, texto_confirmacioon, 1);

			//// Verificar si la confirmación es afirmativa.
			if (strcmp(texto_confirmacioon, "0") == 0)
			{
				//// Actualizar bandera.
				bandera = 0;
			}

			//// Cerrar tubería.
			close(identificador);
			//// Imprimir notificación.
			puts("\nSaliendo de PIDs.\n");
			//// Terminar con la solicitud de PIDs.
			break;
		}
		else
		{

			//// Escribir en tubería posible PID.
			write(identificador, texto, 6);
			puts(texto);

			//// Asignar memoria a una cadena de texto.
			char *texto_confirmacioon = (char *)calloc(1, sizeof(char));
			//// Leer confirmación de tubería.
			read(identificador, texto_confirmacioon, 1);

			//// Verificar si la confirmación es afirmativa.
			if (strcmp(texto_confirmacioon, "1") == 0)
			{
				//// Imprimir notificación afirmativa.
				printf("El usuario ´%s´ puede agregarse.\n", texto);
			}
			else
			{
				//// Imprimir notificación negativa.
				printf("El usuario ´%s´ no puede agregarse.\n", texto);
				//// Actualizar bandera.
				bandera = 0;
			}
		}

		//// Cerrar la tubería.
		close(identificador);

	} while (bandera);

	return bandera;
}

void funcioon_EnviarMensajeIndividual(void)
{

	puts("Enviar mensaje individual");
}

void funcioon_EnviarMensajeGrupal(void)
{

	puts("Enviar mensaje grupal");
}

// To rest -->
