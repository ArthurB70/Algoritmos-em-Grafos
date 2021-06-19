#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ADJACENCY LIST 
typedef struct Cell {
  int successor_node;
  int edge_weight;
  struct Cell *next_cell;
}Cell;

typedef struct List {
  Cell *first_cell, *last_cell;
  int list_size;
}List;

void create_list(List *l){
  Cell *aux = (Cell*)malloc(sizeof(Cell));
  aux->next_cell = NULL;
  l->first_cell  = l->last_cell = aux;
  l->list_size = 0;
  return;
}

void insert_in_order(List* l, int node, int edge_weight){
  Cell* position = l->first_cell;
  while(position->next_cell!=NULL && (node > position->next_cell->successor_node)){
    position = position->next_cell;
  }
  Cell* aux = (Cell*)malloc(sizeof(Cell));
  aux->next_cell = NULL;
  aux->successor_node = node;
  aux->edge_weight = edge_weight;
  aux->next_cell = position->next_cell;
  position->next_cell = aux;
  l->list_size++;
  if(aux->next_cell == NULL){
    l->last_cell = aux;
  }

}

void remove_at(List *l, int position){
    Cell *aux = (Cell*)malloc(sizeof(Cell));
    Cell *predecessor = l->first_cell;
    for(int i=0;i<=position;i++){
        predecessor = predecessor->next_cell;
    }
    predecessor->next_cell = predecessor->next_cell;
    if(predecessor->next_cell == NULL){
        l->last_cell = predecessor;
    }
    free(aux);
    l->list_size--;
}
bool is_empty_list(List l){
  return l.first_cell == l.last_cell;
}

void destroy_lista(List *l){
    while(l->list_size > 0){
        remove_at(l,0);
    }
}

#endif // LIST_H_INCLUDED
