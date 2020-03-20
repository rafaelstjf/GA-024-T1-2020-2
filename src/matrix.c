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
static char *replace_char(char *input, char find, char replace)
{
    /*funcao para trocar um caractere. 
Fonte: https://stackoverflow.com/questions/28637882/c-replace-one-character-in-an-char-array-by-another */

    char *output = (char *)malloc(strlen(input));

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == find)
            output[i] = replace;
        else
            output[i] = input[i];
    }

    output[strlen(input)] = '\0';

    return output;
}
static int matrix_getdimension(const Matrix *m, unsigned int *lines, unsigned int *columns)
{
    if (m)
    {
        unsigned int n_rows = 0;
        unsigned int n_columns = 0;
        Matrix *it_r = m->below;
        while (it_r->below != m) //percorre ateh o ultimo elemento
            it_r = it_r->below;
        n_rows = it_r->line; //atribui a linha do ultimo
        it_r = m->right;
        while (it_r->right != m)
            it_r = it_r->right;
        n_columns = it_r->column;
        (*lines) = n_rows;
        (*columns) = n_columns;
    }
    else
        return false;
}
static int matrix_createheaders(Matrix **m, unsigned int n_rows, unsigned int n_columns)
{
    if (!m)
        free(m);
    (*m) = (Matrix *)malloc(sizeof(Matrix)); //cabeca da lista
    if (!m)
        return false;
    (*m)->right = (*m);
    (*m)->below = (*m);
    (*m)->line = -1;
    (*m)->column = -1;
    (*m)->info = -1.0;
    Matrix *it = (*m);
    //cria as linhas do cabecalho
    for (unsigned int i = 1; i <= n_rows; i++)
    {
        Matrix *r;
        r = (Matrix *)malloc(sizeof(Matrix));
        if (!r)
            return false;
        r->right = r;
        r->below = (*m);
        r->line = i;
        r->column = -1;
        r->info = -1.0;
        it->below = r;
        it = it->below;
    }
    it = (*m);
    //cria as colunas do cabecalho
    for (unsigned int j = 1; j <= n_columns; j++)
    {
        //cria um novo no e atribui os valores a ele
        Matrix *r;
        r = (Matrix *)malloc(sizeof(Matrix));
        if (!r)
            return false;
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
    if (line > n_rows || column > n_columns || line <= 0 || column <= 0)
        return false; //n eh possivel inserir
    while (it_r->line != line)
    {
        it_r = it_r->below; //seleciona a linha do cabecalho
    }
    while (it_c->column != column)
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
                if (it_c2->info == 0)
                {
                    //precisa ser conferido
                    Matrix *temp1 = it_r;
                    while (temp1->right != it_c2)
                    {
                        temp1 = temp1->right;
                    }
                    temp1->right = it_c2->right;
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
    unsigned int buffer_size = 256;
    char *strstream = calloc(1, 1); //aloca e inicia tudo com 0
    char buffer[buffer_size];
    char *token;
    char *search = " ";
    unsigned int n_rows = 0;
    unsigned int n_columns = 0;
    int retorno = false;
    while (fgets(buffer, buffer_size, stdin)) // read from stdin
    {
        strstream = realloc(strstream, strlen(strstream) + 1 + strlen(buffer));
        if (!strstream)
            return false;
        if (strcmp(buffer, "0\n") == 0)
            break; //para quando for digitado 0
        strcat(strstream, buffer);
    }
    //printando tokens
    /*
    printf("PRINTANDO TOKENS\n");
    token = strtok(replace_char(strstream, '\n', ' '), search);
    while (token)
    {
        printf("%f\n", atof(token));
        token = strtok(NULL, search);
    }*/
    //get the number of lines and number of columns
    free(token);
    token = strtok(replace_char(strstream, '\n', ' '), search);
    if (!token)
        return false;
    n_rows = atoi(token);
    token = strtok(NULL, search);
    if (!token)
        return false;
    n_columns = atoi(token);
    if (matrix_createheaders(m, n_rows, n_columns) == false)
        return false;
    token = strtok(NULL, search);
    while (token)
    {
        int line, column;
        int first = false;
        float info;
        if (!token)
            break;
        line = atoi(token);
        token = strtok(NULL, search);
        if (!token)
            break;
        column = atoi(token);
        token = strtok(NULL, search);
        if (!token)
            break;
        info = atof(token);
        retorno = matrix_insertelement(m, n_rows, n_columns, line, column, info, false);
        token = strtok(NULL, search);
    }
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
    return true;
}
int matrix_print(const Matrix *m)
{
    if (m)
    {
        unsigned int n_rows = 0, n_columns = 0;
        matrix_getdimension(m, &n_rows, &n_columns);
        const Matrix *it_r = m->below;
        fprintf(stdout, "%d\t%d\n", n_rows, n_columns);
        while (it_r->line > -1)
        {
            const Matrix *it_c = it_r->right;
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
        retorno = matrix_createheaders(r, dm_r, dn_c);
        if (retorno == false)
            return false;
        const Matrix *itm_r = NULL, *itm_c = NULL, *itn_r = NULL, *itn_c = NULL;
        itm_r = m->below;
        while (itm_r != m)
        {
            itn_c = n->right;
            float sum = 0;
            while (itn_c != n) //vai para a proxima coluna da matriz N
            {
                itn_r = itn_c->below;
                //le as linhas da coluna da atual da matriz N
                while (itn_r != itn_c)
                {
                    itm_c = itm_r->right;
                    while (itm_c != itm_r)
                    {
                        if (itm_c->column == itn_r->line)
                        {
                            sum += itm_c->info * itn_r->info;
                            break;
                        }
                        itm_c = itm_c->right;
                    }
                    itn_r = itn_r->below;
                }
                if (sum > 0.0 || sum < 0.0)
                {
                    matrix_insertelement(r, dm_r, dn_c, itm_r->line, itn_c->column, sum, false);
                }
                sum = 0;
                itn_c = itn_c->right;
            }

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
        while (it_c->column != y)
        {
            it_c = it_c->right;
        }
        const Matrix *it_r = it_c->below;
        while (it_r->line != x)
        {
            if (it_r == it_c)
            {
                (*elem) = 0;
                return true;
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
        while (it_c->column != y)
        {
            it_c = it_c->right;
        }
        Matrix *it_r = it_c->below;
        while (it_r->line != x)
        {
            if (it_r == it_c)
            {
                //eh zero, entao cria novo elemento
                matrix_insertelement(&m, dim_r, dim_c, x, y, elem, false);
            }
            it_r = it_r->below;
        }
        it_r->info = elem;
        return true;
    }
    return false;
}