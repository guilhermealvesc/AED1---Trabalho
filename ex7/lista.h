typedef struct no* Lista;

Lista cria_lista();
int lista_tam(Lista);
int insere_soldado(Lista*, char* nome);
int sorteia_inicio(Lista, char** *nomes);
int sorteia_aleatorio(Lista, char** *nomes, char *nomesoldado, int *num);
int sorteia_nome(Lista, char** *nomes, char *nomesoldado);