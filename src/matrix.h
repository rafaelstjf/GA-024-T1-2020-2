#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct matrix Matrix;

/**
 * le de stdin os elementos diferentes de zero de uma matriz e monta a estrutura especificada acima para listas encadeadas, 
 * retornando a matriz criada em m.
*/
int matrix_create(Matrix **m);
/**
 * Desaloca a matriz
*/
int matrix_destroy(Matrix *m);
/**
 * Imprime a matriz
*/
int matrix_print(const Matrix *m);
/**
 * Soma duas matrizes m e n, e retorna o resultado em r
*/
int matrix_add(const Matrix *m, const Matrix *n, Matrix **r);
/**
 * Multiplica duas matrizes m e n, e retorna o resultado em r
*/
int matrix_multiply(const Matrix *m, const Matrix *n, Matrix **r);
/**
 * Calcula a transposta da matriz m e retorna o resultado em r
*/
int matrix_transpose(const Matrix *m, Matrix **r);
/**
 * retorna o elemento (x, y) da matriz m 
*/
int matrix_getelem(const Matrix *m, int x, int y, float *elem);
/**
 * atribui ao elemento (x, y) da matriz m o valor de elem
*/
int matrix_setelem(Matrix *m, int x, int y, float elem);
#endif
