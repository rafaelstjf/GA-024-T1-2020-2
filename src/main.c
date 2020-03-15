#include <stdio.h>
#include "matrix.h"
int main(void)
{
    /* Inicializacao da aplicacao ... */
    Matrix *A = NULL;
    Matrix *B = NULL;
    Matrix *C = NULL;
    printf("Criando a matriz A\n");
    if (!matrix_create(&A))
        matrix_print(A);
    else
    {
        fprintf(stderr, "Erro na alocacao de A como listas encadeadas.\n");
        return 1;
    }
    printf("Criando a matriz B\n");
    if (!matrix_create(&B))
        matrix_print(B);
    else
    {
        fprintf(stderr, "Erro na alocacao de B como listas encadeadas.\n");
        return 1;
    }
    printf("Somando as matrizes A + B em C\n");
    if (!matrix_add(A, B, &C))
    {
        matrix_print(C);
    }
    else
        fprintf(stderr, "Erro na soma C=A+B.\n");
    matrix_destroy(C);
    printf("Multiplicando as matrizes A e B em C\n");
    if (!matrix_multiply(A, B, &C))
        matrix_print(C);
    else
        fprintf(stderr, "Erro na multiplicacao C=A*B.\n");
    matrix_destroy(C);
    printf("Transpondo a matriz A em C\n");
    if (!matrix_transpose(A, &C))
        matrix_print(C);
    else
        fprintf(stderr, "Erro na transposicao C=A^T.\n");
    float elem;
    printf("Selecionando o elemento (1, 1) da matriz A\n");
    if (matrix_getelem(A, 1, 1, &elem) == 0)
        printf("elemento: %f\n", elem);
    printf("Atribuindo ao elemento (1, 1) da matriz A o valor 32.553\n");
    if (matrix_setelem(A, 1, 1, 32.553) == 0)
        matrix_print(A);
    matrix_destroy(C);
    matrix_destroy(A);
    matrix_destroy(B);
    printf("Todas as matrizes foram desalocadas\n");
    return 0;
}