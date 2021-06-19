#ifndef PERMUTACAO_H_INCLUDED
#define PERMUTACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "permu_stack.h"
#include "list.h"
#include "adjacency_listNDW.h"

bool search_array(int *array1, int n, int countVertex){
  for(int i=0;i<countVertex;i++)
  {
    if(array1[i]==n)
      return true;
  }
  return false;
}
int first_valid_value(int* array1, int* array2, int index, int countVertex){
  for(int i = index; i<countVertex;i++){
    if(search_array(array1, array2[i], countVertex) == false){
      return array2[i];
    }
  }
  return -1;
}
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void bubbleSort(int *arr, int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)     
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
 
Pilha_permu create_all_permutation(int countVertex){
  Pilha_permu total_permu, bckp, aux_permu;
  create_pilha_permu(&bckp);
  create_pilha_permu(&total_permu);
  create_pilha_permu(&aux_permu);
  int count_vertex = countVertex, contadorOp = countVertex;
  int *aux_array, *base_array;
  base_array = (int*)calloc(count_vertex, sizeof(int));
  for(int i=0;i<count_vertex;i++){
    aux_array = (int*)calloc(count_vertex, sizeof(int));
    aux_array[0] = i+1;
    base_array[i] = i+1;
    push_permu(&total_permu,aux_array,count_vertex);
    push_permu(&bckp,aux_array,count_vertex);
    free(aux_array);
  }
  int i, j;
  while(contadorOp > 0){
    contadorOp--;
    copia_pilha(&bckp, &aux_permu, contadorOp, count_vertex);
    while(!is_empty_pilha_permu(aux_permu)){
      i = 0, j = 0;
      while(i<contadorOp){
        aux_array = pop_permu(&aux_permu, count_vertex);
            aux_array[count_vertex - contadorOp] = first_valid_value(aux_array, base_array, j,  count_vertex);
        i++;
        j = aux_array[count_vertex - contadorOp];
        push_permu(&bckp, aux_array, count_vertex);
        push_permu(&total_permu, aux_array, count_vertex);
        free(aux_array);
      }
    }
  }
  free(base_array);
  destroy_pilha_permu(&bckp, count_vertex);
  destroy_pilha_permu(&aux_permu, count_vertex);
  //destroy_pilha_permu(&total_permu, count_vertex);
  return total_permu;
}
bool check_graph_path(int *aux_array, GraphADJListNDW graph){
  Cell *temp = NULL;
  if(graph.vertex_array[aux_array[0]-1].successor_list.list_size <= 1)  return false;
  for(int i=0,j = 1; j<graph.countVertex;i++, j++){
    temp = graph.vertex_array[aux_array[i]-1].successor_list.first_cell;
    if(aux_array[j] == 0){
      while(temp!=NULL && temp->successor_node != aux_array[0]){
        temp = temp->next_cell;
        if(temp == NULL){
          return false;
        }
      }
        return true;
    }
    if(graph.vertex_array[aux_array[j]-1].successor_list.list_size <= 1)  return false; 
    while(temp!=NULL && temp->successor_node != aux_array[j]){
      temp = temp->next_cell;
    }
    if(temp == NULL){
      return false;
    } 
  }
  return true;
}
bool check_path_size(int *aux_array, int countVertex){
  int count = 0;
  for(int i=0; i<countVertex;i++){
    if(aux_array[i] == 0) break;
    else{
      count++;
    }
  }
  if(count >= 3) return true;
  else return false;
}
bool compare_arrays(int *aux_array, int *temp_array, int n){
  bool check = true;
  for(int i=0; i<n;i++){
    if(aux_array[i] != temp_array[i])
      check = false;
  }
  return check;
}
bool search_path(Pilha_permu p, int *aux_array, int countVertex){
  if(p.tamanho != 0){
    Celula_permu *temp = p.topo;
    bool check = true;
    while(temp!=NULL){
        if(compare_arrays(aux_array, temp->permutacao, countVertex)){
          return true;
        }   
      temp = temp->proximo;
    }
    return false;    
  }
  else{
    return false;
  } 
  
}
void count_cycles_permutation(GraphADJListNDW graph){
  Pilha_permu total_permu = create_all_permutation(graph.countVertex);
  Pilha_permu aux;
  create_pilha_permu(&aux);
  int *aux_array;
  while(!is_empty_pilha_permu(total_permu)){
    aux_array = pop_permu(&total_permu, graph.countVertex);
    
    if(check_graph_path(aux_array, graph) && check_path_size(aux_array,graph.countVertex)){
      push_permu(&aux,aux_array,graph.countVertex);
    }
    free(aux_array);
  }
  while(!is_empty_pilha_permu(aux)){
    aux_array = pop_permu(&aux, graph.countVertex);
    bubbleSort(aux_array, graph.countVertex);
    if(!search_path(total_permu,aux_array,graph.countVertex)){
      push_permu(&total_permu,aux_array,graph.countVertex);
    }
    free(aux_array);
  }
  print_pilha_permu(total_permu ,  graph.countVertex);
  destroy_pilha_permu(&total_permu, graph.countVertex);
  destroy_pilha_permu(&aux, graph.countVertex);
  
  return ;
}

#endif // PERMUTACAO_H_INCLUDED