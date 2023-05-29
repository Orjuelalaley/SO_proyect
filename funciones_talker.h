#ifndef HEADER_FILE_H
#define HEADER_FILE_H

char **matriz_GIDs;

void funcioon_ImprimirRol(void);
void funcioon_ImprimirMenuu(void);
int askHasCharacter(char string[]);
void funcioon_InvocarEleccioon(void);
void funcioon_ImplementacioonDeTuberiias(char *mensaje);
int funcioon_CalcularUultimaFilaMatriz(char **matriz);
void funcioon_ListarUsuarios(void);
void funcioon_ListarIntegrantes(void);
void funcioon_CrearGrupo(void);
int funcioon_ElegirUsuarios(char *gid);
void funcioon_EnviarMensajeIndividual(void);
void funcioon_EnviarMensajeGrupal(void);

#endif
