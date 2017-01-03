#include <stdbool.h>
#ifndef BUSCAMINAS_H
#define BUSCAMINAS_H
#define DIM 4
#define EXPLORADO ' '
#define NO_EXPLORADO 'O'
#define MINADO 1
#define VACIO 0
#define ARCHIVO_EXPLORADO "explorado.save"
#define ARCHIVO_MINADO "minado.save"

/* pre: Recibe dos matrices cuadradas de tamaño DIM.
 post: Devuelve dos matrices inicializadas*/
void InicializarCampos(char campoE[][DIM], int campoM[][DIM]);

/* pre: el campo de minas debe ser inicializado.
post: devuelve verdadero si hay una mina en esa posicion, falso en caso contrario
*/
bool ExisteMina(int campoM[][DIM], int fila, int columna);

/* pre: el campo de exploracion debe ser inicializado.
post: devuelve verdadero si la posicion fue inspeccionada, falso en caso contrario
*/
bool campoInspeccionado(char campoE[][DIM],int fila, int columna);

/*post: coloca una mina en la posicion indicada.
*/
void ColocarMina(int campoM[][DIM], int fila, int columna);

/*pre: el campo debe estar inicializado.
post: muestra por consola el campo minado.
*/
void DibujarCampoMinado(int campoM[][DIM]);

/*pre: el campo debe estar inicializado.
post: muestra por consola el campo explorado.
*/
void DibujarCampoExplorado(char campoE[][DIM]);

/*post: devuelve verdadero si recibe una posicion valida, falso en caso contrario.
*/
bool posicionInvalida(int fila, int columna);

/*pre: El campo debe estar inicializado.
post: explora el campo en la posicion indicada.
*/
void inspeccionar(char campoExplorado[][DIM],int fila, int columna);

/* post: llena el campo con minas
*/
void colocarMinas(int campoMinado[][DIM]);

/*pre:El campo minado y el campo explorado deben estar inicializados.
post: Devuelve verdadero si el jugador gano, false en caso contrario.
*/
bool verificarVictoria(int campoMinado[][DIM],char campoExplorado[][DIM]);

bool guardar_partida(int campoMinado[][DIM],char campoExplorado[][DIM]);

bool cargar_partida(int campoMinado[][DIM],char campoExploradado[][DIM]);

#endif
