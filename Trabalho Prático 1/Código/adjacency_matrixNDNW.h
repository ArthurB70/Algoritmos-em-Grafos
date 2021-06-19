#ifndef ADJACENCY_MATRIXNDNW_H_INCLUDED
#define ADJACENCY_MATRIXNDNW_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
============================
REPRESENTAÇÃO DE
GRAFO NÃO DIRECIONADO 
E NÃO PONDERADO
============================
*/
typedef struct GraphADJMatrixNDNW{
  int countVertex;
  int countEdge;
  bool weight;
  int** graph_matrix;
}GraphADJMatrixNDNW;

void init_GraphADJMatrixNDNW(GraphADJMatrixNDNW* graph, int countVertex, int countEdge){
  graph->countEdge = countEdge;
  graph->countVertex = countVertex;
  graph->weight = false;
  graph->graph_matrix = (int**)calloc(graph->countVertex, sizeof(int*));
  for(int i=0; i<graph->countVertex;i++)
    graph->graph_matrix[i] = (int*)calloc(graph->countVertex, sizeof(int));
  return;
}

void load_GraphADJMatrixNDNW(GraphADJMatrixNDNW* graph, FILE* graph_file){
  int vertex = 0, successor_vertex = 0, weight = 0;
  while(!feof(graph_file)){
    fscanf(graph_file,"%d %d %d\n", &vertex, &successor_vertex, &weight);
    if(graph->graph_matrix[vertex - 1][successor_vertex - 1] == 0){
      graph->graph_matrix[vertex - 1][successor_vertex - 1] = 1;
      graph->graph_matrix[successor_vertex - 1][vertex - 1] = 1;    
    }
    else{
      printf("\nErro: Arco nao foi adicionado ao Grafo. Arco Paralelo(%d,%d)",vertex, successor_vertex);
      graph->countEdge--;
    }

  }
  return;
}

void destroy_GraphADJMatrixNDNW(GraphADJMatrixNDNW* graph){
  for(int i = 0; i<graph->countVertex;i++)
    free(graph->graph_matrix[i]);
    
  free(graph->graph_matrix);
  graph->countEdge = 0;
  graph->countVertex = 0;
  return;
}

void print_GraphADJMatrixNDNW(GraphADJMatrixNDNW graph, char* graph_name){
  printf("\n%s \tCountVertex: %d \tCountEdges: %d \tWeight: %s\n", graph_name, graph.countVertex, graph.countEdge, graph.weight == 1 ? "true":"false");
  printf(" i\\j  ");
  for(int i=0;i<graph.countVertex; i++)
    printf(" [%d]\t ", i+1);
  printf("\n");
  for(int i = 0; i<graph.countVertex; i++){
    printf("\n[%d] ", i+1);
    for(int j = 0; j<graph.countVertex; j++){
        printf("   %d\t", graph.graph_matrix[i][j]);
    }
    printf("\n");
  }
}
#endif // ADJACENCY_MATRIXNDNW_H_INCLUDED