#ifndef ADJACENCY_LISTNDW_H_INCLUDED
#define ADJACENCY_LISTNDW_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
/*
============================
REPRESENTAÇÃO DE
GRAFO NAO DIRECIONADO 
E PONDERADO
============================
*/
void print_listNDW(List l){
    Cell *temp = l.first_cell->next_cell;
    int i=0;
    while(temp!=NULL){
        printf(" %d(%d) - ", temp->successor_node, temp->edge_weight);
        temp = temp->next_cell;
        i++;
    }
}

// ADJACENCY LIST GRAPH

typedef struct Vertex_arrayADJListNDW{
  int vertex;
  List successor_list;
}Vertex_arrayADJListNDW;

typedef struct GraphADJListNDW{
  int countVertex;
  int countEdge;
  bool weight;
  Vertex_arrayADJListNDW* vertex_array;
}GraphADJListNDW;

void init_GraphADJListNDW(GraphADJListNDW* graph, int countVertex, int countEdge, bool weight){
  graph->countVertex = countVertex;
  graph->countEdge = countEdge;
  graph->weight = weight;
  graph->vertex_array = (Vertex_arrayADJListNDW*)malloc(graph->countVertex*sizeof(Vertex_arrayADJListNDW));
  for(int i=0; i<graph->countVertex; i++){
    create_list(&graph->vertex_array[i].successor_list);
    graph->vertex_array[i].vertex = i+1;
  }
  return;
}

void load_GraphADJListNDW(GraphADJListNDW* graph, FILE* graph_file){
  int vertex = 0, successor_vertex = 0, weight = 0;
  while(!feof(graph_file)){
    fscanf(graph_file, "%d %d %d\n", &vertex, &successor_vertex, &weight);
    if(vertex > graph->countVertex){
      printf("\nErro na leitura do grafo: vertice maior que o limite: vertice(%d) limite(%d)",vertex, graph->countVertex);
      break;
    }
    insert_in_order(&graph->vertex_array[vertex-1].successor_list, successor_vertex,weight);
    insert_in_order(&graph->vertex_array[successor_vertex-1].successor_list,vertex ,weight);
  }
}

void print_GraphADJListNDW(GraphADJListNDW graph, char* graph_name){
  printf("\n%s \tCountVertex: %d \tCountEdges: %d \tWeight: %s", graph_name, graph.countVertex, graph.countEdge, graph.weight == 1 ? "true":"false");
  printf("\n[vertex] - successor(weight)");
  for(int i=0; i<graph.countVertex;i++){
    printf("\n[%d] -", graph.vertex_array[i].vertex);
    print_listNDW(graph.vertex_array[i].successor_list);
    printf("\n");
  }
}
void destroy_GraphADJListNDW(GraphADJListNDW* graph){
  for(int i=0; i<graph->countVertex; i++){
    destroy_lista(&graph->vertex_array[i].successor_list);
  }
  graph->weight = false;
  graph->countVertex = 0;
  graph->countEdge = 0;
  free(graph->vertex_array);
}


#endif // ADJACENCY_LISTNDW_H_INCLUDED
