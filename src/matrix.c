#include "matrix.h"
static const int false = 1;
static const int true = 0;

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
        return false;
}
static int matrix_createheaders(Matrix **m, unsigned int n_rows, unsigned int n_columns)
{
    if ((*m))
        free((*m));
    (*m) = (Matrix *)malloc(sizeof(Matrix)); //cabeca da lista
    (*m)->right = (*m);
    (*m)->below = (*m);
    (*m)->line = -1;
    (*m)->column = -1;
    (*m)->info = -1.0;
    Matrix *it = (*m);
    for (unsigned int i = 1; i <= n_rows; i++)
    {
        //cria um novo no e atribui os valores a ele
        Matrix *r = (Matrix *)malloc(sizeof(Matrix));
        r->right = r;
        r->below = (*m);
        r->line = i;
        r->column = -1;
        r->info = -1.0;
        it->below = r;
        it = it->below;
    }
    it = (*m);
    for (unsigned int j = 1; j <= n_columns; j++)
    {
        //cria um novo no e atribui os valores a ele
        Matrix *r = (Matrix *)malloc(sizeof(Matrix));
        r->right = (*m);
        r->below = r;
        r->line = -1;
        r->column = j;
        r->info = -1.0;
        it->right = r;
        it = it->right;
    }
    return true;
}
static int matrix_insertelement(Matrix **m, unsigned int n_rows, unsigned int n_columns, int line, int column, float info, unsigned int addifequal)
{
    if (info == 0.0)
        return true; //pula qualquer 0
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
        return false; //n eh possivel inserir
    for (int i = 0; i <= line; i++)
    {
        it_r = it_r->below; //seleciona a linha do cabecalho
    }
    for (int j = 0; j <= column; j++)
    {
        it_c = it_c->right; //seleciona a coluna do cabecalho
    }
    Matrix *it_c2 = it_c;
    while (it_c2->below != it_c && it_c2->line < n->line)
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
        if (it_c2->line == n->line && it_c2->column == n->column)
        {
            if (addifequal == true)
            { //se ja existe um elemento na posicao ele eh somado
                it_c2->info += n->info;
                if (it_c2->info == 0.0)
                {
                    //precisa ser conferido
                    ant->below = it_c2->below;
                    free(it_c2);
                    it_c2 = ant;
                }
                free(n);
                return true;
            }
            else
                return true;
        }
        it_c2->below = n;
        n->below = it_c;
    }
    Matrix *it_r2 = it_r;
    ant = NULL;
    while (it_r2->right != it_r && it_r2->column < n->column)
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
    return true;
}

int matrix_create(Matrix **m)
{
    FILE *f = NULL;
    unsigned int n_rows = 5;
    unsigned int n_columns = 5;
    f = stdin;
    int retorno = 0;
    retorno = matrix_createheaders(m, n_rows, n_columns);
    retorno = matrix_insertelement(m, n_rows, n_columns, 2, 2, 3.0, false);
    retorno = matrix_insertelement(m, n_rows, n_columns, 2, 2, 1.0, false);
    retorno = matrix_insertelement(m, n_rows, n_columns, 2, 1, 2.0, false);
    retorno = matrix_insertelement(m, n_rows, n_columns, 1, 1, 1.0, false);
    return retorno;
}
int matrix_destroy(Matrix *m)
{
    if (!m)
        return false;
    Matrix *it_r = m->below;
    Matrix *it_c = m->right;
    Matrix *temp = NULL;
    while (it_r != m)
    {
        Matrix *t = it_r->right;
        while (t != it_r)
        {
            temp = t;
            t = temp->right;
            free(temp);
        }
        it_r = it_r->below;
        free(t);
    }
    while (it_c != m)
    {
        temp = it_c;
        it_c = it_c->right;
        free(temp);
    }
    free(m);
    printf("matriz desalocada!\n");
    return true;
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
        return true;
    }
    else
        return false;
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
            return false;
        Matrix *it1_r = m->below, *it1_c = NULL, *it2_r = n->below, *it2_c = NULL;
        retorno = matrix_createheaders(r, dim1_r, dim1_c);
        while (it1_r != m)
        {
            it1_c = it1_r->right;
            while (it1_c != it1_r)
            {
                matrix_insertelement(r, dim1_r, dim1_c, it1_c->line, it1_c->column, it1_c->info, true);
                it1_c = it1_c->right;
            }
            it1_r = it1_r->below;
        }
        while (it2_r != n)
        {
            it2_c = it2_r->right;
            while (it2_c != it2_r)
            {
                matrix_insertelement(r, dim1_r, dim1_c, it2_c->line, it2_c->column, it2_c->info, true);
                it2_c = it2_c->right;
            }
            it2_r = it2_r->below;
        }
        return true;
    }
    else
        return false;
}
int matrix_multiply(const Matrix *m, const Matrix *n, Matrix **r)
{
    unsigned int dm_r, dm_c, dn_r, dn_c;
    int retorno = false;
    if (m && n)
    {
        matrix_getdimension(m, &dm_r, &dm_c);
        matrix_getdimension(n, &dn_r, &dn_c);
        retorno = matrix_createheaders(r, dm_r, dm_c);
        if (retorno == false)
            return false;
        const Matrix *itm_r = NULL, *itm_c = NULL, *tmn_r = NULL, *itn_c = NULL;
        itm_r = m->below;
        while (itm_r != m)
        {
            itm_r = itm_r->below;
        }
        return true;
    }
    else
        return false;
}
int matrix_transpose(const Matrix *m, Matrix **r)
{
    int retorno = false;
    unsigned int dim_r, dim_c;

    if (m)
    {
        matrix_getdimension(m, &dim_r, &dim_c);
        retorno = matrix_createheaders(r, dim_c, dim_r);
        if (retorno == false)
            return false;
        Matrix *it1_r = m->below, *it1_c = NULL;
        while (it1_r != m)
        {
            it1_c = it1_r->right;
            while (it1_c != it1_r)
            {
                retorno = matrix_insertelement(r, dim_c, dim_r, it1_c->column, it1_c->line, it1_c->info, false);
                if (retorno == false)
                    return false;
                it1_c = it1_c->right;
            }
            it1_r = it1_r->below;
        }
        return true;
    }
    else
        return false;
}
int matrix_getelem(const Matrix *m, int x, int y, float *elem)
{
    if (m)
    {
        unsigned int dim_r, dim_c;
        matrix_getdimension(m, &dim_r, &dim_c);
        if (dim_r < x || dim_c < y || x <= 0 || y <= 0)
            return false;
        const Matrix *it_c = m;
        for (unsigned int i = 0; i <= y; i++)
        {
            it_c = it_c->right;
        }
        const Matrix *it_r = it_c->below;
        while (it_r->line != x)
        {
            if (it_r == it_c)
            {
                return false;
            }
            it_r = it_r->below;
        }
        (*elem) = it_r->info;
        return true;
    }
    return false;
}
int matrix_setelem(Matrix *m, int x, int y, float elem)
{

    if (m)
    {
        unsigned int dim_r, dim_c;
        matrix_getdimension(m, &dim_r, &dim_c);
        if (dim_r < x || dim_c < y || x <= 0 || y <= 0)
            return false;
        Matrix *it_c = m;
        for (unsigned int i = 0; i <= y; i++)
        {
            it_c = it_c->right;
        }
        Matrix *it_r = it_c->below;
        while (it_r->line != x)
        {
            if (it_r == it_c)
            {
                return false;
            }
            it_r = it_r->below;
        }
        it_r->info = elem;
        return true;
    }
    return false;
}