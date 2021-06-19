#ifndef PERMU_STACK_H_INCLUDED
#define PERMU_STACK_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Celula_permu{
    int *permutacao;
    struct Celula_permu *proximo;
}Celula_permu;
typedef struct Pilha_permu{
    int tamanho;
    Celula_permu *topo;
}Pilha_permu;
void create_pilha_permu(Pilha_permu *p){
    p->tamanho = 0;
    p->topo = NULL;
}
void push_permu(Pilha_permu *p, int* permu_array, int countVertex){
    Celula_permu *temp = (Celula_permu*)malloc(sizeof(Celula_permu));
    temp->permutacao = (int*)calloc(countVertex, sizeof(int));
    for(int i=0;i<countVertex;i++)
      temp->permutacao[i] = permu_array[i];
    temp->proximo = p->topo;
    p->topo = temp;
    p->tamanho++;
}
bool is_empty_pilha_permu(Pilha_permu p){
    return p.topo==NULL;
}
int* pop_permu(Pilha_permu *p, int countVertex){
    int *array_retorno;
    array_retorno = (int*)calloc(countVertex,sizeof(int));
    if(is_empty_pilha_permu(*p)){
      return NULL;
    }  
    Celula_permu *temp = p->topo;
    for(int i=0;i<countVertex;i++)
      array_retorno[i] = temp->permutacao[i]; 
    p->topo = p->topo->proximo;
    free(temp->permutacao);
    free(temp);
    p->tamanho--;
    return array_retorno;
}
void copia_pilha(Pilha_permu *p, Pilha_permu *copia, int n, int countVertex){
  int *aux_array;
  while(!is_empty_pilha_permu(*p)){
      aux_array = pop_permu(p,countVertex);  
    for(int i=0;i<n;i++)
      push_permu(copia,aux_array,countVertex);
  }
  free(aux_array);
}
void destroy_pilha_permu(Pilha_permu *p, int countVertex){
    while(!is_empty_pilha_permu(*p))
        pop_permu(p, countVertex);
}
void print_pilha_permu(Pilha_permu p, int countVertex){
    Celula_permu *temp = p.topo;
    printf("\nTamanho: %d \n",p.tamanho);
    while(temp!=NULL){
        for(int i=countVertex -1;i>0; i--)
          printf("%d ", temp->permutacao[i]);
        printf("\n");
        temp = temp->proximo;
    }
}
#endif // PERMU_STACK_H_INCLUDED