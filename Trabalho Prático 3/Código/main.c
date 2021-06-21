#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include "adjacency_listDW.h"
#include "stack.h"
#include "simplepath.h"
#include "list_simplepath.h"

void TP3(char* txt_name, int A, int B){
  FILE* graph_file = fopen(txt_name, "r");
  if(!graph_file){
    printf("\n\t\tErro na leitura do arquivo");
  }
  GraphADJListDW graph4;
  int countVertex = 0, countEdge = 0, weight = 0;
  fscanf(graph_file, "%d %d %d\n", &countVertex, &countEdge, &weight);
  init_GraphADJListDW(&graph4, countVertex,  countEdge,  weight == 1 ?true:false);
  load_GraphADJListDW(&graph4, graph_file);
  //print_GraphADJListDW(graph4, "graph4");
  Pilha pRetorno;
  create_pilha(&pRetorno);
  printf("\nCAMINHOS SIMPLES DE %d a %d", A, B);

  pRetorno = count_simple_paths(graph4, A, B);
  
  print_pilha(pRetorno);
  destroy_pilha(&pRetorno);
  destroy_GraphADJListDW(&graph4);
  fclose(graph_file);
}

int main(void) {
  // INSIRA O NOME DO ARQUIVO ABAIXO, O VERTICE DE ORIGEM E O DE DESTINO
  // example2.txt VERTICES = 8 ARESTAS = 13
  // example3.txt VERTICES = 6 ARESTAS = 11
  // example4.txt VERTICES = 6 ARESTAS = 9
  TP3("example3.txt", 1, 6);
  return 0;
}