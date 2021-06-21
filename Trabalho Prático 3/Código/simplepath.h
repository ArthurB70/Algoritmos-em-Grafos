#ifndef SIMPLEPATH_H_INCLUDED
#define SIMPLEPATH_H_INCLUDED

#include "list_simplepath.h"

long sum_vertex(int Vertex){
  return (Vertex * pow(10,Vertex - 1));
}

Pilha count_simple_paths(GraphADJListDW graph, int A, int B){
  int vertex = graph.vertex_array[A-1].vertex, vertex_index = 1, vertex_count = 1, i = 0;
  long vertex_sum = sum_vertex(graph.vertex_array[A-1].vertex);
  Cell *temp;
  Pilha aux_stack;
  Pilha return_stack;
  List_sp list;
  create_list_sp(&list);
  create_pilha(&return_stack);
  create_pilha(&aux_stack);
  while(vertex !=-1){
    i = 0;
    temp = graph.vertex_array[vertex - 1].successor_list.first_cell;
    while(temp!=NULL){
      if(i < vertex_index)
      temp = temp->next_cell;
      else{
        break;
      } 
      i++;
    }
    if(temp != NULL){
       if(temp->successor_node == B && is_empty_pilha(aux_stack)){
          vertex_sum += sum_vertex(temp->successor_node);
          insert_sp(&list, vertex, temp->successor_node);
          push(&return_stack, vertex, vertex_sum, vertex_count, vertex_index, list);
          remove_at_sp(&list);
          vertex_sum -= sum_vertex(temp->successor_node);
          vertex_index +=  1;
       }
       else if(temp->successor_node == B && aux_stack.topo->dado != B){
        vertex_sum += sum_vertex(temp->successor_node);
        insert_sp(&list, vertex, temp->successor_node);
        push(&return_stack, vertex, vertex_sum, vertex_count, vertex_index, list);
        remove_at_sp(&list);
        vertex_sum -= sum_vertex(temp->successor_node);
        vertex_index +=  1;

      } 
      else if(!procura_pilha(aux_stack, temp->successor_node)){
        push(&aux_stack, vertex, vertex_sum, vertex_count, vertex_index,list);
        insert_sp(&list, vertex, temp->successor_node);
        vertex = temp->successor_node;
        vertex_sum += sum_vertex(vertex);
        vertex_index = 1;
        vertex_count += 1;
      }
      else{
        vertex_index += 1;
      }
    }
    else{
        if(list.list_size > 0){
          destroy_lista_sp(&list);
        }
        VerticePilha popVertex;
        popVertex = pop(&aux_stack);
        if(popVertex.list.list_size > 0)
          clone_list_sp(&list, popVertex.list);

        if(popVertex.list.list_size > 0)
          destroy_lista_sp(&popVertex.list);
        
        vertex = popVertex.vertice;
        vertex_sum = popVertex.soma;
        vertex_count = popVertex.count;
        vertex_index = popVertex.index + 1; 
    }
  }
  destroy_lista_sp(&list);
  destroy_pilha(&aux_stack);
  return return_stack;
}


#endif // SIMPLEPATH_H_INCLUDED