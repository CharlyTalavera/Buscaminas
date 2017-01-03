#include <stdio.h>
#include <stdbool.h>
#include "buscaminas.h"
#include <time.h>
#include <stdlib.h>

void InicializarCampos(char campoE[][DIM], int campoM[][DIM]){
    srand(time(NULL));
    for (int i=0;i<DIM;i++){
        for (int j=0;j<DIM;j++){
            campoE[i][j] = NO_EXPLORADO;
            campoM[i][j] = rand()%2;
        }
    }
}

bool ExisteMina(int campoM[][DIM], int fila, int columna){
    return campoM[fila][columna] == MINADO;
}

bool campoInspeccionado(char campoE[][DIM],int fila, int columna){
  return campoE[fila][columna]==EXPLORADO;
}

void ColocarMina(int campoM[][DIM], int fila, int columna){
    campoM[fila][columna] = MINADO;
}

void DibujarCampoMinado(int campoM[][DIM]){
    printf(" ");
    for (int i=0;i<DIM;i++)
        printf(" %d",i);
    printf("\n");
    for (int i=0;i<DIM;i++){
        printf("%d ",i);
        for (int j=0;j<DIM;j++){
            printf("%i ",campoM[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void DibujarCampoExplorado(char campoE[][DIM]){
    printf(" ");
    for (int i=0;i<DIM;i++)
	printf(" %i",i);
    printf("\n");
    for (int i=0;i<DIM;i++){
        printf("%c ",i);
    	for (int j=0;j<DIM;j++){
            printf("%c ",campoE[i][j]);
        }
	printf("\n");
    }
    printf("\n");
}

bool posicionInvalida(int fila, int columna){
	return  fila<0 || columna<0 || fila>=DIM || columna>=DIM;
}
void inspeccionar(char campoExplorado[][DIM],int fila, int columna){
    campoExplorado[fila][columna]=EXPLORADO;
}

void colocarMinas(int campoMinado[][DIM]){
    int fil,col;
    for(int i=1; i<=DIM/2; i++){
	printf("Coloque mina numero: %d\n",i);
	printf("Ingrese fila:\n");
        scanf("%i",&fil);
        printf("Ingrese columna:\n");
        scanf("%i",&col);
        while(posicionInvalida(fil,col) || ExisteMina(campoMinado, fil, col)){
            printf("¡Posicion invalida!");
            printf("Ingrese fila:\n");
            scanf("%i",&fil);
            printf("Ingrese columna:\n");
            scanf("%i",&col);
        }
        ColocarMina(campoMinado, fil, col);
    }
}

bool verificarVictoria(int campoMinado[][DIM],char campoExplorado[][DIM]){
    for(int i=0;i<DIM;i++)
        for(int j=0;j<DIM;j++)
            if(campoMinado[i][j]==VACIO && campoExplorado[i][j]==NO_EXPLORADO)
                return false;
    return true;
}


bool guardar_partida(int campoMinado[][DIM],char campoExplorado[][DIM]){
  FILE* archivo_explorado=fopen(ARCHIVO_EXPLORADO,"w");
  FILE* archivo_minado=fopen(ARCHIVO_MINADO,"w");
  if(!archivo_explorado || !archivo_minado)
    return false;
  for(int i=0;i<DIM;i++)
    for(int j=0;j<DIM;j++){
      fwrite(&campoMinado[i][j],sizeof(int),1,archivo_minado);
      fwrite(&campoExplorado[i][j],sizeof(char),1,archivo_explorado);
    }
  fclose(archivo_explorado);
  fclose(archivo_minado);
  return true;
}

bool cargar_partida(int campoMinado[][DIM],char campoExplorado[][DIM]){
  FILE* archivo_explorado=fopen(ARCHIVO_EXPLORADO,"r");
  FILE* archivo_minado=fopen(ARCHIVO_MINADO,"r");
  if(!archivo_explorado || !archivo_minado)
    return false;
  for(int i=0;i<DIM;i++)
    for(int j=0;j<DIM;j++){
      fread(&campoMinado[i][j],sizeof(int),1,archivo_minado);
      fread(&campoExplorado[i][j],sizeof(char),1,archivo_explorado);
  }
  fclose(archivo_explorado);
  fclose(archivo_minado);
  return true;
}
