#include "matrix.h"
struct matrix
{
    struct matrix *right; //proximo elemento != 0 na mesma linha
    struct matrix *below; //proximo elemento != 0 na mesma coluna
    int line;
    int column;
    float info;
};

int matrix_create(Matrix **m)
{
    FILE* f = NULL;
    unsigned int n_rows = 0;
    unsigned int n_columns = 0;
    f = stdin;
    if ((*m))
        free((*m));
    (*m) = (Matrix *)malloc(sizeof(Matrix)); //cabeca da lista
    (*m)->right = NULL;
    (*m)->below = NULL;
    (*m)->line = -1;
    (*m)->column = -1;
    (*m)->info = -1.0;
    Matrix *it = m;
    for (unsigned int i = 1; i <= n_rows; i++)
    {
        //cria um novo no e atribui os valores a ele
        Matrix *r = (Matrix *)malloc(sizeof(Matrix));
        r->right = r;
        r->below = NULL;
        r->line = i;
        r->column = -1;
        r->info = -1.0;
        it->below = r;
        it = it->below;
    }
    it->below = m;
    it = m;
    for (unsigned int j = 1; j <= n_columns; j++)
    {
        //cria um novo no e atribui os valores a ele
        Matrix *r = (Matrix *)malloc(sizeof(Matrix));
        r->right = NULL;
        r->below = r;
        r->line = -1;
        r->column = j;
        r->info = -1.0;
        it->right = r;
        it = it->right;
    }
    it->right = m;

}
int matrix_destroy(Matrix *m)
{
    Matrix *it_r = m->right;
    Matrix *it_b = m;
    Matrix *temp = NULL;
    while (it_b)
    {
        while (it_r)
        {
            temp = it_r;
            it_r = temp->right;
            free(temp);
        }
        temp = it_b;
        it_b = it_b->below;
        free(temp);
    }
    return 0;
}
int matrix_print(const Matrix *m)
{
    //fprintf(stdout,)
    return 0;
}
int matrix_add(const Matrix *m, const Matrix *n, Matrix **r)
{

    return 0;
}
int matrix_multiply(const Matrix *m, const Matrix *n, Matrix **r)
{

    return 0;
}
int matrix_transpose(const Matrix *m, Matrix **r)
{

    return 0;
}
int matrix_getelem(const Matrix *m, int x, int y, float *elem)
{

    return 0;
}
int matrix_setelem(Matrix *m, int x, int y, float elem)
{

    return 0;
}