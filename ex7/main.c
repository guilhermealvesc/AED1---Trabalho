#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() {
    int i, qnt, escolha, sortedNum;
    Lista soldados;
    char* *nomes, name[50];
    soldados = cria_lista();
    do {
        printf("Informe a quantidade de soldados: ");
        scanf("%d", &qnt);
    } while (qnt < 1);
    for(i = 0; i < qnt; i++) {
        printf("Digite o nome do %do soldado: ", i + 1);
        setbuf(stdin, NULL);
        scanf("%[^\n]", name);
        if(!insere_soldado(&soldados, name)){
            printf("\nErro na alocacao!!");
            exit(1);
        }
    }
    printf("\n-Problema de Josephus-\n");
    printf("(1) Iniciar contagem a partir do inicio\n");
    printf("(2) Iniciar contagem a partir de uma posicao sorteada aleatoriamente\n");
    printf("(3) Iniciar contagem a partir do nome de um soldado \nDigite a sua escolha: ");
    scanf("%d", &escolha);
    switch(escolha) {
        case 1:
            if(sorteia_inicio(soldados, &nomes)) {
                printf("\nSoldados mortos...");
                for(i = 0; i < qnt - 1; i++) 
                    printf("\nSoldado %s morreu", nomes[i]);
                printf("\nSoldado %s foi o unico sobrevivente!", nomes[qnt - 1]);
            } else {
                printf("\nNao foi possivel sortear do inicio!");
            }
            break;
        case 2:
            if(sorteia_aleatorio(soldados, &nomes, name, &sortedNum)) {
                printf("\nO numero %d foi sorteado!", sortedNum);
                printf("\nPrimeiro soldado: %s", name);
                printf("\nSoldados mortos...");
                for(i = 0; i < qnt - 1; i++) 
                    printf("\nSoldado %s morreu", nomes[i]);
                printf("\nSoldado %s foi o unico sobrevivente!", nomes[qnt - 1]);
            } else {
                printf("\nNao foi possivel sortear de uma posicao aleatoria!");
            }
            break;
        case 3:
            printf("Digite o nome do soldado que deve iniciar: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", name);
            if(sorteia_nome(soldados, &nomes, name)) {
                printf("\nSoldados mortos...");
                for(i = 0; i < qnt - 1; i++) 
                    printf("\nSoldado %s morreu", nomes[i]);
                printf("\nSoldado %s foi o unico sobrevivente!", nomes[qnt - 1]);
            } else {
                printf("\nNao foi possivel sortear a partir do soldado %s!", name);
            }
            break;
        default:
            printf("Saindo do programa...");
    }
    return 0;
}