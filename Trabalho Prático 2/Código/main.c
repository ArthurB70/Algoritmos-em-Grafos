#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include "permutacao.h"
#include "adjacency_listNDW.h"
#include "stack.h"
#include "permu_stack.h"
#include "deepsearch.h"

void TP2(char* txt_name){
  system("clear");
  FILE* graph_file = fopen(txt_name, "r");
  if(!graph_file){
    printf("\n\t\tErro na leitura do arquivo");
  }
  GraphADJListNDW graph4;
  int countVertex = 0, countEdge = 0, weight = 0;
  fscanf(graph_file, "%d %d %d\n", &countVertex, &countEdge, &weight);
  init_GraphADJListNDW(&graph4, countVertex,  countEdge,  weight == 1 ?true:false);;
  load_GraphADJListNDW(&graph4, graph_file);
  print_GraphADJListNDW(graph4, "graph4");

  clock_t start_time, end_time;
  size_t peakSize;
  start_time = clock();
  printf("\nCICLOS VIA PERMUTACAO");
  count_cycles_permutation(graph4);
  end_time = clock();
  printf("\n\ttempo: %lf s\n", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);
  start_time = clock();
  DeepSearch deepSearch;
  init_deepSearch(&deepSearch, graph4.countVertex);
  deepSearch.deepSearchTree[0].startTime = 0;
  search(&deepSearch, graph4, 1);
  print_deepSearch(deepSearch, graph4.countVertex);
  printf("\nCICLOS VIA CAMINHAMENTO");
  count_cycles_DeepSearch(deepSearch, graph4);

  destroy_deepSearch(&deepSearch, graph4.countVertex);
  end_time = clock();
  printf("\n\ttempo: %lf s\n", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);

  destroy_GraphADJListNDW(&graph4);
  fclose(graph_file);
}

int main(void) {
  // INSIRA O NOME DO ARQUIVO ABAIXO
  TP2("example7.txt");
  return 0;
}