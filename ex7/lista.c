/* 
--Justificativa do aluno sobre a escolha do TAD--
    Para o problema de Josephus, como se trata de uma roda com remoções de pessoas
através de sorteios, utilizei uma lista encadeada(devido a quantidade grande quantidade 
de remoções ao decorrer do programa), com o comportamento circular(para que a ideia de roda
ocorra com maior facilidade, e seja possível percorrer a lista na forma de um círculo, já que
é necessário passar do fim para o início da lista várias vezes). Cogitei em usar a técnica de nó cabeçalho 
para o problema, mas conclui que não seria necessário, já que ia tornar a implementação mais difícil 
pelo fato de ser circular, e também, percorrer a lista uma vez para saber seu tamanho já é 
suficiente para descartar o uso do nó cabeçalho para esse problema.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista.h"
//Estrutura para posicao de cada elemento
struct no {
    char nomeSoldado[50];
    struct no *prox;
};
//Cria a lista
Lista cria_lista() {
    return NULL;
};
//Verifica se a lista esta vazia
int lista_vazia(Lista list) {
    return list == NULL;
}

//Retorna o tamanho da lista
int lista_tam(Lista list) {
    if(lista_vazia(list))
        return 0;
    //se nao esta vazia, tem pelo menos 1
    int cont = 1;
    Lista aux = list->prox;
    while(aux->prox != list->prox) {
        aux = aux->prox;
        cont++;
    }
    return cont;
}
//Insere um elemento no final da lista
int insere_soldado(Lista *list, char* nome) {
    Lista N = (Lista) malloc(sizeof(struct no));
    if(N == NULL)
        return 0;
    
    strcpy(N->nomeSoldado, nome);
    if(lista_vazia(*list)) {
        N->prox = N;
        *list = N;
    } else {
        N->prox = (*list)->prox;
        (*list)->prox = N;
        *list = N;
    }
    return 1;
}

char** alocaNomes(int tamanho) {
    char* *nomes = malloc(tamanho * sizeof(char*));
    if(nomes == NULL) 
        return NULL;
    int i;
    for(i = 0; i < tamanho; i++) {
        nomes[i] = (char*) malloc(50*sizeof(char));
        if(nomes[i] == NULL)
            return NULL;
    }
    return nomes;
}

/* 
Sorteia aleatoriamente até achar o soldado sobrevivente, partindo do início / Retorna 
uma lista com tamanho da quantidade de soldados na ordem de eliminação, e no final, o sobrevivente.
 */
int sorteia_inicio(Lista list, char** *nomes) {
    if(lista_vazia(list)) 
        return 0;
    //Pega tamanho da lista
    int contMortos = 0, pos, tam = lista_tam(list);
    *nomes = alocaNomes(tam);
    if(*nomes == NULL) 
        return 0;
    srand(time(NULL));
    //Primeiro Soldado
    Lista aux = list;
    //Enquanto tiver mais de um soldado
    while(tam > 1) {
        pos = rand() % tam;
        //Ando pos posições
        while(pos > 0) {
            aux = aux->prox;
            pos--;
        }
        //Coloco so soldado morto na lista
        strcpy((*nomes)[contMortos], aux->prox->nomeSoldado);
        contMortos++;
        //E removo o soldado da lista
        Lista aux2 = aux->prox;
        aux->prox = aux2->prox;
        free(aux2);
        list = aux;
        tam--;
    }
    //Coloca o nome do sobrevivente no final da lista
    strcpy((*nomes)[contMortos], list->nomeSoldado);
    return 1;
}

/* 
Sorteia aleatoriamente até achar o soldado sobrevivente, partindo de um soldado aleatório / Retorna 
uma lista com tamanho da quantidade de soldados na ordem de eliminação, e no final, o sobrevivente /
Também devolve o nome do soldado sorteado e o numero sorteado.
 */
int sorteia_aleatorio(Lista list, char** *nomes, char *nomesoldado, int *num) {
    if(lista_vazia(list)) 
        return 0;
    //Pega tamanho da lista
    int contMortos = 0, pos, tam = lista_tam(list);
    *nomes = alocaNomes(tam);
    if(*nomes == NULL) 
        return 0;
    srand(time(NULL));
    //Sorteia um soldado para começar
    pos = rand() % tam;
    *num = pos;
    //Anda até o soldado o primeiro soldado
    while(pos > 0) {
        list = list->prox;
        pos--;
    }
    //Retornando soldado de inicio
    strcpy(nomesoldado, list->prox->nomeSoldado);
    //Último Soldado
    Lista aux = list;
    //Enquanto tiver mais de um soldado
    while(tam > 1) {
        pos = rand() % tam;
        //Ando pos posições
        while(pos > 0) {
            aux = aux->prox;
            pos--;
        }
        //Coloco so soldado morto na lista
        strcpy((*nomes)[contMortos], aux->prox->nomeSoldado);
        contMortos++;
        //E removo o soldado da lista
        Lista aux2 = aux->prox;
        aux->prox = aux2->prox;
        free(aux2);
        list = aux;
        tam--;
    }
    //Coloca o nome do sobrevivente no final da lista
    strcpy((*nomes)[contMortos], list->nomeSoldado);
    return 1;
}
/* 
Sorteia aleatoriamente até achar o soldado sobrevivente, partindo de um soldado informado / Retorna 
uma lista com tamanho da quantidade de soldados na ordem de eliminação, e no final, o sobrevivente /
Se o nome informado do soldado nao estiver na lista, retorna 0.
 */
int sorteia_nome(Lista list, char** *nomes, char *nomesoldado) {
    if(lista_vazia(list)) 
        return 0;
    //Pega tamanho da lista
    int contMortos = 0, pos, tam = lista_tam(list);
    *nomes = alocaNomes(tam);
    if(*nomes == NULL) 
        return 0;
    //Último Soldado
    Lista aux = list;
    //Percorre os soldados procurando o nome por onde iniciar
    //Se nao for no inicio, o soldado com o nome deve estar para frente
    if(strcmp(list->prox->nomeSoldado, nomesoldado)) {
        aux = list->prox;
        while (aux->prox != list->prox && strcmp(aux->prox->nomeSoldado, nomesoldado)) 
            aux = aux->prox;
        //Soldado nao foi encontrado
        if(aux->prox == list->prox) {
            return 0;
        }
    }
    srand(time(NULL));
    //Enquanto tiver mais de um soldado
    while(tam > 1) {
        pos = rand() % tam;
        //Ando pos posições
        while(pos > 0) {
            aux = aux->prox;
            pos--;
        }
        //Coloco so soldado morto na lista
        strcpy((*nomes)[contMortos], aux->prox->nomeSoldado);
        contMortos++;
        //E removo o soldado da lista
        Lista aux2 = aux->prox;
        aux->prox = aux2->prox;
        free(aux2);
        list = aux;
        tam--;
    }
    //Coloca o nome do sobrevivente no final da lista
    strcpy((*nomes)[contMortos], list->nomeSoldado);
    return 1;
}