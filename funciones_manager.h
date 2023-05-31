#ifndef FUNCIONES_H
#define FUNCIONES_H


char** matriz_PIDs ;
char** matriz_GIDs ;

void funcioon_ImprimirRol (void) ;
void funcioon_ImplementacioonDeTuberiias (void) ;
int funcioon_CalcularUultimaFilaMatriz (char** matriz_contar) ;
int funcioon_VerificarExistencia (char** matriz_buscar,char* texto_PID_verificarExistente) ;
void funcioon_AccionarMenuu (char* instruccioon,char* pid) ;
void funcioon_ImprimirMatriz (char** matriz_imprimir,char* mensaje_imprimir,char* etiqueta_imprimir) ;
void funcioon_EnviarListaUsuarios (void) ;
void funcioon_CrearGrupo (void) ;
int funcioon_VerificarUsuarios (char* gid,char** matrizTemporal) ;
void funcioon_EliminarPID (char* texto_PID_eliminar) ;


#endif
