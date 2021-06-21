#ifndef LIST_SIMPLEPATH_H_INCLUDED
#define LIST_SIMPLEPATH_H_INCLUDED


// ADJACENCY List_sp 
typedef struct Cell_sp {
  int A;
  int B;
  struct Cell_sp *next_cell;
}Cell_sp;

typedef struct List_sp {
  Cell_sp *first_cell, *last_cell;
  int list_size;
}List_sp;

void create_list_sp(List_sp *l){
  Cell_sp *aux = (Cell_sp*)malloc(sizeof(Cell_sp));
  aux->next_cell = NULL;
  l->first_cell  = l->last_cell = aux;
  l->list_size = 0;
  return;
}

void insert_sp(List_sp* l, int A, int B){
  Cell_sp* position = l->first_cell;
  Cell_sp* aux = (Cell_sp*)malloc(sizeof(Cell_sp));
  aux->next_cell = NULL;
  aux->A = A;
  aux->B = B;
  aux->next_cell = position->next_cell;
  position->next_cell = aux;
  l->list_size++;
  if(aux->next_cell == NULL){
    l->last_cell = aux;
  }

}
bool is_empty_list_sp(List_sp l){
  return l.first_cell == l.last_cell;
}
void clone_list_sp(List_sp *clone, List_sp base){
    Cell_sp *temp = base.first_cell->next_cell;
    while(temp!=NULL){
      insert_sp(clone,temp->A, temp->B);
      temp = temp->next_cell;
    }

}
void remove_at_sp(List_sp *l){
    Cell_sp *aux = l->first_cell->next_cell;
    l->first_cell->next_cell = aux->next_cell;
    aux->next_cell = NULL;
    if(aux->next_cell == NULL){
        l->last_cell = aux;
    }
    free(aux);
    l->list_size--;
}
void print_list_sp(List_sp l){
    Cell_sp *temp = l.first_cell->next_cell;
    while(temp!=NULL){
        printf(" (%d,%d),  ", temp->A, temp->B);
        temp = temp->next_cell;
    }
}
void destroy_lista_sp(List_sp *l){
    while(l->list_size > 0){
        remove_at_sp(l);
    }
}

#endif // LIST_SIMPLEPATH_H_INCLUDED