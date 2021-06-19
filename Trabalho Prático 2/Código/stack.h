#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct VerticePilha{
  int vertice, index, count;
  long soma;
}VerticePilha;
typedef struct Celula{
    int dado, index, count;
    long soma;
    struct Celula *proximo;
}Celula;
typedef struct Pilha{
    int tamanho;
    Celula *topo;
}Pilha;
void create_pilha(Pilha *p){
    p->tamanho = 0;
    p->topo = NULL;
}
void push(Pilha *p, int dado, long soma, int count, int index){
    Celula *temp = (Celula*)malloc(sizeof(Celula));
    temp->index = index;
    temp->soma = soma;
    temp->count = count;
    temp->dado = dado;
    temp->proximo = p->topo;
    p->topo = temp;
    p->tamanho++;
}
bool is_empty_pilha(Pilha p){
    return p.topo==NULL;
}
VerticePilha pop(Pilha *p){
    VerticePilha vertice;
    if(is_empty_pilha(*p)){
      vertice.vertice = -1;
      return vertice;
    }  
    Celula *temp = p->topo;
    vertice.vertice = temp->dado;
    vertice.index = temp->index;
    vertice.soma = temp->soma;
    vertice.count = temp->count;
    p->topo = p->topo->proximo;
    free(temp);
    p->tamanho--;
    return vertice;
}
void destroy_pilha(Pilha *p){
    while(!is_empty_pilha(*p))
        pop(p);
}
bool procura_pilha(Pilha p, int n){
  Celula *temp = p.topo;
  while(temp!=NULL){
    if(temp->dado == n)
      return true;
    temp = temp->proximo;
  }
  return false;
}
bool procura_vertice_pilha(Pilha p, VerticePilha n){
  Celula *temp = p.topo;
  while(temp!=NULL){
    if(temp->soma == n.soma){
      return true; 
    }
    temp = temp->proximo;
  }
  return false;
}
void print_pilha(Pilha p){
    Celula *temp = p.topo;
    printf("\nTamanho: %d \n",p.tamanho);
    while(temp!=NULL){
        printf("%ld\n", temp->soma);
        temp = temp->proximo;
    }
}
#endif // STACK_H_INCLUDED