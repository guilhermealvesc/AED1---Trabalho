#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
 
int main()
{
  int x = 0;
  int val[11] = {4, 8, -1, 19, 2, 7, 8, 7, -9, 22, 45};

  Lista list = cria();
  Lista list2 = cria();
  Lista invertida = cria();
  Lista concatenada = cria();

  imprime(list);

  for (size_t i = 0; i < 11; i++)
  {
    inserir(list, val[i]);
  }

  for (size_t i = 0; i < 11; i++)
  {
    inserir(list2, val[i]);
  }
  
  imprime(list);
  remove_impares(list);
  imprime(list);
  x = menor(list);
  printf("menor = %d\n", x);
  x = tamanho(list);
  printf("tamanho = %d\n", x);
  printf("Invertida:\n");
  invertida = inverter(list);
  imprime(invertida);
  imprime(list);
  imprime(list2);
  concatenada = concatenar(list, list2);
  concatenada = concatenar(concatenada, concatenada);
  printf("Concatenada:\n");
  imprime(concatenada);

  libera(list);

  system("pause");
  return 0;
}