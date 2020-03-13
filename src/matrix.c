#include "matrix.h"
static const int erro = 1;
static const int sucesso = 0;

struct matrix
{
    struct matrix *right; //proximo elemento != 0 na mesma linha
    struct matrix *below; //proximo elemento != 0 na mesma coluna
    int line;
    int column;
    float info;
};
static int matrix_addelm(Matrix **m, unsigned int n_rows, unsigned int n_columns, int line, int column, float info)
{
    Matrix *it_r = (*m);
    Matrix *it_c = (*m);
    Matrix *n; //novo elemento
    n = (Matrix*)malloc(sizeof(Matrix));
    n->right = NULL;
    n->below = NULL;
    n->line = line;
    n->column = line;
    n->info = info;
    if (line > n_rows || column > n_columns)
        return erro; //n eh possivel inserir
    for (int i = 0; i <= line; i++)
    {
        it_r = it_r->below; //seleciona a linha do cabecalho
    }
    for (int j = 0; j <= column; j++)
    {
        it_c = it_c->right; //seleciona a coluna do cabecalho
    }
    if (it_c->below == it_c)
    { //nao existe elemento na coluna
        n->below = it_c;
        it_c->below = n;
    }
    else
    { //ja existe elemento
        Matrix *it_c2 = it_c;
        Matrix *ant = NULL;
        while (it_c2->below != it_c || it_c2->line < n->line)
        {
            /*percorre a lista enquanto nao for o ultimo
            ou tiver em uma linha anterior ao novo elem */
            ant = it_c2;
            it_c2 = it_c2->below;
        }
        if (it_c2->line > n->line)
        {
            ant->below = n;
            n->below = it_c2;
        }
        else
        {
            it_c2->below = n;
            n->below = it_c;
        }
    }
    if (it_r->right == it_r)
    {
        //nao existe elemento na linha
        n->right = it_r;
        it_r->right = n;
    }
    else
    { //ja existe elemento
        Matrix *it_r2 = it_r;
        Matrix *ant = NULL;
        while (it_r2->right != it_r || it_r2->line < n->line)
        {
            /*percorre a lista enquanto nao for o ultimo
            ou tiver em uma linha anterior ao novo elem */
            ant = it_r2;
            it_r2 = it_r2->right;
        }
        if (it_r2->line > n->line)
        {
            ant->below = n;
            n->below = it_r2;
        }
        else
        {
            it_r2->below = n;
            n->below = it_c;
        }
    }
    return sucesso;
}
int matrix_create(Matrix **m)
{
    FILE *f = NULL;
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
    Matrix *it = (*m);
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
    it->below = (*m);
    it = (*m);
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
    it->right = (*m);
    matrix_addelm(m, n_rows, n_columns, 2, 2, 1.0);
    return sucesso;
}
int matrix_destroy(Matrix *m)
{
    if(!m)
        return erro;
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
    return sucesso;
}
int matrix_print(const Matrix *m)
{
    if (m)
    {
        Matrix *it_r = m->below;
        while (it_r != m)
        {
            Matrix *it_c = it_r->right;
            while (it_c != it_r)
            {
                fprintf(stdout, "%d\t%d\t%f\n", it_c->line, it_c->column, it_c->info);
                it_c = it_c->right;
            }
            it_r = it_r->below;
        }
        return sucesso;
    }
    else
        return erro;
}
int matrix_add(const Matrix *m, const Matrix *n, Matrix **r)
{

    return sucesso;
}
int matrix_multiply(const Matrix *m, const Matrix *n, Matrix **r)
{

    return sucesso;
}
int matrix_transpose(const Matrix *m, Matrix **r)
{

    return sucesso;
}
int matrix_getelem(const Matrix *m, int x, int y, float *elem)
{

    return sucesso;
}
int matrix_setelem(Matrix *m, int x, int y, float elem)
{

    return sucesso;
}