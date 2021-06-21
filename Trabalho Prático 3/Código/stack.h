#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_simplepath.h"

typedef struct VerticePilha{
  int vertice, index, count;
  long soma;
  List_sp list;
}VerticePilha;
typedef struct Celula{
    int dado, index, count;
    long soma;
    List_sp list;
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
void push(Pilha *p, int dado, long soma, int count, int index, List_sp list){
    Celula *temp = (Celula*)malloc(sizeof(Celula));
    create_list_sp(&temp->list);
    clone_list_sp(&temp->list, list);
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
    create_list_sp(&vertice.list);
    clone_list_sp(&vertice.list,temp->list);
    destroy_lista_sp(&temp->list);
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
    while(!is_empty_pilha(*p)){
      VerticePilha aux;
      aux = pop(p);
      destroy_lista_sp(&aux.list);
    }
        
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
        //printf("%d\t%ld\t%d\t%d\t",temp->dado, temp->soma, temp->index, temp->count);
        print_list_sp(temp->list);
        printf("\n\n");
        temp = temp->proximo;
    }
}
#endif // STACK_H_INCLUDED