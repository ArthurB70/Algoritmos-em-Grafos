#ifndef ADJACENCY_ARRAYDNW_H_INCLUDED
#define ADJACENCY_ARRAYDNW_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



/*
============================
REPRESENTAÇÃO DE
GRAFO DIRECIONADO 
E NÃO PONDERADO
============================
*/
typedef struct GraphADJArrayDNW{
  int countVertex;
  int countEdge;
  int* vertexArray;
  int* successorArray;
}GraphADJArrayDNW;

void init_GraphADJArrayDNW(GraphADJArrayDNW* graph, int countVertex, int countEdge){
  graph->countVertex = countVertex;
  graph->countEdge = countEdge;
  graph->vertexArray = (int*)calloc((graph->countVertex + 1), sizeof(int));
  graph->successorArray = (int*)calloc((graph->countEdge + 1), sizeof(int));
  for(int i=0;i<=countVertex; i++)
    graph->vertexArray[i] = countEdge + 1;
  return;
}
int size_temparray(int countVertex, int countEdge){
  if(countEdge > countVertex)
    return countEdge;
  else
    return countVertex;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void sort_array(int* a, int* b, int array_size){
    int i, j;
    for (i = 0; i < array_size-1; i++)
      for (j = 0; j < array_size-i-1; j++) {
          if (a[j] > a[j+1] && a[j+1]!= 0){
              swap(&a[j], &a[j+1]);
              swap(&b[j], &b[j+1]);
          }
          if(a[j] >= a[j+1] && b[j] > b[j+1] && a[j+1]!= 0){
              swap(&a[j], &a[j+1]);
              swap(&b[j], &b[j+1]);
          }
      }
}

void load_GraphADJArrayDNW(GraphADJArrayDNW* graph, FILE* graph_file){
  int temp_size = size_temparray(graph->countVertex, graph->countEdge);
  int* arraytempVertex = (int*)malloc((temp_size)*sizeof(int));
  int* arraytempEdge = (int*)malloc((temp_size)*sizeof(int));
  int i = 0, flag = 0;
  while(!feof(graph_file)){
    fscanf(graph_file, "%d %d %d\n", &arraytempVertex[i], &arraytempEdge[i], &flag);
    i++;
  }
  sort_array(arraytempVertex, arraytempEdge, temp_size);
  flag = -1;
  for(int j = 0; j<graph->countEdge; j++){
    if(flag != arraytempVertex[j]){
      flag = arraytempVertex[j];
      graph->vertexArray[arraytempVertex[j] - 1] = j + 1;
    }
    graph->successorArray[j] = arraytempEdge[j];
  }
  free(arraytempVertex);
  free(arraytempEdge);
}

void print_GraphADJArrayDNW(GraphADJArrayDNW graph, char* name){

  printf("\n%s\tCountVertex: %d  CountEdge: %d Weight: %s", name, graph.countVertex, graph.countEdge,"false");
  printf("\nindex_vertex_array[vertex_array]\tindex_successor_array[successor_array]");
  printf("\n");

  for(int i = 0, j = 0; i<=graph.countVertex || j<=graph.countEdge ; i++,j++){
    if(i<=graph.countVertex)
      printf("\n%d[%d] ", i+1, graph.vertexArray[i]);
    else
      printf("\n\t");
    if(j<=graph.countEdge)
        printf("\t\t%d[%d]", j+1, graph.successorArray[i]);
  }
}
void destroy_GraphADJArrayDNW(GraphADJArrayDNW* graph){
  free(graph->vertexArray);
  free(graph->successorArray);
  graph->countEdge = 0;
  graph->countVertex = 0;
}
#endif // ADJACENCY_ARRAYDNW_H_INCLUDED
