#include "matrix.h"
struct matrix
{
    struct matrix *right; //proximo elemento != 0 na mesma linha
    struct matrix *below; //proximo elemento != 0 na mesma coluna
    int line;
    int column;
    float info;
};  

int matrix_create(Matrix **m){

 return 0;   
}
int matrix_destroy(Matrix *m){

    return 0;
}
int matrix_print(const Matrix *m){
    
    return 0;
}
int matrix_add(const Matrix *m, const Matrix *n, Matrix **r){

    return 0;
}
int matrix_multiply(const Matrix *m, const Matrix *n, Matrix **r){
    
    return 0;
}
int matrix_transpose(const Matrix *m, Matrix **r){

    return 0;
}
int matrix_getelem(const Matrix *m, int x, int y, float *elem){
    
    return 0;
}
int matrix_setelem(Matrix *m, int x, int y, float elem){

    return 0;
}