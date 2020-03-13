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
static int matrix_getdimension(const Matrix *m, unsigned int *lines, unsigned int *columns)
{
    if (m)
    {
        unsigned int n_rows = 0;
        unsigned int n_columns = 0;
        Matrix *it_r = m->below;
        while (it_r != m) //conta as linhas
        {
            it_r = it_r->below;
            n_rows++;
        }
        it_r = m->right;
        while (it_r != m) //conta as colunas
        {
            it_r = it_r->right;
            n_columns++;
        }
        (*lines) = n_rows;
        (*columns) = n_columns;
    }
    else
        return erro;
}
static int matrix_createheaders(Matrix **m, unsigned int n_rows, unsigned int n_columns)
{
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
    return sucesso;
}
static int matrix_addelem(Matrix **m, unsigned int n_rows, unsigned int n_columns, int line, int column, float info)
{
    if (info == 0.0)
        return sucesso;
    Matrix *it_r = (*m);
    Matrix *it_c = (*m);
    Matrix *n; //novo elemento
    n = (Matrix *)malloc(sizeof(Matrix));
    n->right = NULL;
    n->below = NULL;
    n->line = line;
    n->column = column;
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
            //coloca o elemento na ultima posicao
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
        while (it_r2->right != it_r || it_r2->column < n->column)
        {
            /*percorre a lista enquanto nao for o ultimo
            ou tiver em uma linha anterior ao novo elem */
            ant = it_r2;
            it_r2 = it_r2->right;
        }
        if (it_r2->column > n->column)
        {
            ant->right = n;
            n->right = it_r2;
        }
        else
        {
            it_r2->right = n;
            n->right = it_r;
        }
    }
    return sucesso;
}
//se ja existe um elemento na posicao ele eh somado
static int matrix_sumaddelem(Matrix **m, unsigned int n_rows, unsigned int n_columns, int line, int column, float info)
{
    unsigned int summed = erro;
    if (info == 0.0)
        return sucesso;
    Matrix *it_r = (*m);
    Matrix *it_c = (*m);
    Matrix *ant = NULL;
    Matrix *n; //novo elemento
    n = (Matrix *)malloc(sizeof(Matrix));
    n->right = NULL;
    n->below = NULL;
    n->line = line;
    n->column = column;
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
    Matrix *it_c2 = it_c;
    while (it_c2->below != it_c || it_c2->line < n->line)
    {
        /*percorre a lista enquanto nao for o ultimo
            ou tiver em uma linha anterior ao novo elem */
        ant = it_c2;
        it_c2 = it_c2->below;
        //printf("agarrado no loop\n");
    }
    if (it_c2->line > n->line)
    {
        ant->below = n;
        n->below = it_c2;
    }
    else
    {
        //coloca o elemento na ultima posicao
        if (it_c2->line == n->line && it_c2->column == n->column)
        {
            it_c2->info += n->info;
            free(n);
            return sucesso;
        }
        it_c2->below = n;
        n->below = it_c;
    }
    Matrix *it_r2 = it_r;
    ant = NULL;
    while (it_r2->right != it_r || it_r2->column < n->column)
    {
        /*percorre a lista enquanto nao for o ultimo
            ou tiver em uma linha anterior ao novo elem */
        ant = it_r2;
        it_r2 = it_r2->right;
    }
    if (it_r2->column > n->column)
    {
        ant->right = n;
        n->right = it_r2;
    }
    else
    {
        it_r2->right = n;
        n->right = it_r;
    }
    return sucesso;
}
int matrix_create(Matrix **m)
{
    FILE *f = NULL;
    unsigned int n_rows = 5;
    unsigned int n_columns = 5;
    f = stdin;
    int retorno = 0;
    retorno = matrix_createheaders(m, n_rows, n_columns);
    retorno = matrix_addelem(m, n_rows, n_columns, 2, 2, 1.0);
    retorno = matrix_addelem(m, n_rows, n_columns, 2, 1, 1.0);
    retorno = matrix_addelem(m, n_rows, n_columns, 2, 1, 1.0);
    retorno = matrix_addelem(m, n_rows, n_columns, 1, 1, 1.0);
    return retorno;
}
int matrix_destroy(Matrix *m)
{
    if (!m)
        return erro;
    Matrix *it_r = m->below;
    Matrix *it_c = m;
    Matrix *temp = NULL;
    while (it_r != m)
    {
        Matrix *t = it_r->right;
        while (it_r != t)
        {
            temp = it_r;
            it_r = temp->right;
            free(temp);
        }
        temp = t;
        it_r = it_r->below;
        free(temp);
    }
    while (it_c)
    {
        temp = it_c;
        it_c = it_c->right;
        free(temp);
    }
    return sucesso;
}
int matrix_print(const Matrix *m)
{
    if (m)
    {
        unsigned int n_rows = 0, n_columns = 0;
        matrix_getdimension(m, &n_rows, &n_columns);
        Matrix *it_r = m->below;
        fprintf(stdout, "%d\t%d\n", n_rows, n_columns);
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
    int retorno = 0;
    if (m && n) //verifica se as duas matrizes existe se possuem dimensoes iguais
    {
        unsigned int dim1_r = 0, dim1_c = 0, dim2_r = 0, dim2_c = 0;
        matrix_getdimension(m, &dim1_r, &dim1_c);
        matrix_getdimension(n, &dim2_r, &dim2_c);
        if (dim1_r != dim1_r || dim1_c != dim2_c)
            return erro;
        Matrix *it1_r = m->below, *it1_c = NULL, *it2_r = n->below, *it2_c = NULL;
        retorno = matrix_createheaders(r, dim1_r, dim1_c);
        while (it1_r != m)
        {
            it1_c = it1_r->right;
            while (it1_c != it1_r)
            {
                matrix_sumaddelem(r, dim1_r, dim1_c, it1_c->line, it1_c->column, it1_c->info);
                it1_c = it1_c->right;
            }
            it1_r = it1_r->below;
        }
        while (it2_r != m)
        {
            it2_c = it2_r->right;
            while (it2_c != it2_r)
            {
                matrix_sumaddelem(r, dim1_r, dim1_c, it2_c->line, it2_c->column, it2_c->info);
                it2_c = it2_c->right;
            }
            it2_r = it2_r->below;
        }
        return sucesso;
    }
    else
        return erro;
}
int matrix_multiply(const Matrix *m, const Matrix *n, Matrix **r)
{

    return erro;
}
int matrix_transpose(const Matrix *m, Matrix **r)
{

    return erro;
}
int matrix_getelem(const Matrix *m, int x, int y, float *elem)
{

    return erro;
}
int matrix_setelem(Matrix *m, int x, int y, float elem)
{

    return erro;
}