#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "adjacency_listDW.h"
#include "adjacency_arrayDNW.h"
#include "adjacency_matrixNDNW.h"
#include "adjacency_listNDW.h"
char* exemploDeGrafo(int op){
  if(op == 1)
    return "example1.txt";
  if(op == 2)
    return "example2.txt";
  else
    return "example3.txt";
}
void texto_menu_tipoDeGrafo(){
    printf("\n\t\tTRABALHO PRATICO 1 - ALGORITMOS EM GRAFOS");
    printf("\n\t\tAutores: Arthur Bernardo Coelho Moura e Lucas Baesse");
    printf("\n\n");
    printf("\n\t\tEscolha uma opcao de Grafo:");
    printf("\n\t\t[1]  - Direcionado ponderado");
    printf("\n\t\t[2]  - Direcionado nao ponderado");
    printf("\n\t\t[3]  - Nao direcionado ponderado");
    printf("\n\t\t[4]  - Nao direcionado nao ponderado");
    printf("\n\t\t[-1] - Exit\n");
}
void texto_menu_exemplos(){
    printf("\n\t\tTRABALHO PRATICO 1 - ALGORITMOS EM GRAFOS");
    printf("\n\t\tAutor: Arthur Bernardo Coelho Moura");
    printf("\n\n");
    printf("\n\t\tEscolha uma opcao de exemplo:");
    printf("\n\t\t[1]  - graph -> vertices: 6 arestas: 8");
    printf("\n\t\t[2]  - graph -> vertices: 8 arestas: 15");
    printf("\n\t\t[3]  - graph -> vertices: 10000 arestas: 10000");
    printf("\n\t\t[-1] - selecao de tipos de grafos\n");
}
void exec_direcionado_ponderado(){
  int op = 0;
  while(op != -1){
    system("clear");
    texto_menu_exemplos();
    scanf("%d", &op);
    if(op > 0 && op < 4){
      char * file_name = exemploDeGrafo(op);
      printf("\n%s", file_name);
      getchar();
      FILE* graph_file = fopen(exemploDeGrafo(op), "r");
      if(!graph_file){
        printf("\n\t\tErro na leitura do arquivo");
      }
      GraphADJListDW graph1;
      int countVertex = 0, countEdge = 0, weight = 0;
      fscanf(graph_file, "%d %d %d\n", &countVertex, &countEdge, &weight);
      init_GraphADJListDW(&graph1, countVertex,  countEdge,  weight == 1 ? true:false);;
      load_GraphADJListDW(&graph1, graph_file);
      print_GraphADJListDW(graph1, "graph1");
      destroy_GraphADJListDW(&graph1);
      fclose(graph_file);
      printf("\n\t\tAperte qualquer tecla para continuar...");
      fflush(stdin);
      fflush(stdin);
      fflush(stdin);
      getchar();
    }
    else if(op == -1){
      printf("\n\t\tVoltando para menu tipos de grafos...");
    }
    else{
      printf("\n\t\tOpcao invalida! Tente novamente...");
    }
  }
  return;
}
void exec_direcionado_Nponderado(){
  int op = 0;
  while(op != -1){
    system("clear");
    texto_menu_exemplos();
    scanf("%d", &op);
    if(op > 0 && op < 4){
      FILE* graph_file = fopen(exemploDeGrafo(op), "r");
      if(!graph_file){
        printf("\n\t\tErro na leitura do arquivo");
      }
      fflush(stdin);
      GraphADJArrayDNW graph2;
      int countVertex = 0, countEdge = 0, weight = 0;
      fscanf(graph_file, "%d %d %d\n", &countVertex, &countEdge, &weight);
      init_GraphADJArrayDNW(&graph2, countVertex, countEdge);
      load_GraphADJArrayDNW(&graph2, graph_file);
      print_GraphADJArrayDNW(graph2, "graph2");
      destroy_GraphADJArrayDNW(&graph2);
      fclose(graph_file);
      printf("\n\t\tAperte qualquer tecla para continuar...");
      getchar();
      getchar();

    }
    else if(op == -1){
      printf("\n\t\tVoltando para menu tipos de grafos...");
    }
    else{
      printf("\n\t\tOpcao invalida! Tente novamente...");
    }
  }
  return;
}
void exec_Ndirecionado_Nponderado(){
  int op = 0;
  while(op != -1){
    system("clear");
    texto_menu_exemplos();
    scanf("%d", &op);
    if(op > 0 && op < 4){
      FILE* graph_file = fopen(exemploDeGrafo(op), "r");
      if(!graph_file){
        printf("\n\t\tErro na leitura do arquivo");
      }
      fflush(stdin);
      GraphADJMatrixNDNW graph3;
      int countVertex = 0, countEdge = 0, weight = 0;
      fscanf(graph_file, "%d %d %d\n", &countVertex, &countEdge, &weight);
      init_GraphADJMatrixNDNW(&graph3, countVertex,  countEdge);
      load_GraphADJMatrixNDNW(&graph3, graph_file);
      print_GraphADJMatrixNDNW(graph3, "graph3");
      destroy_GraphADJMatrixNDNW(&graph3);
      fclose(graph_file);
      printf("\n\t\tAperte qualquer tecla para continuar...");
      fflush(stdin);
      getchar();
      getchar();
    }
    else if(op == -1){
      printf("\n\t\tVoltando para menu tipos de grafos...");
    }
    else{
      printf("\n\t\tOpcao invalida! Tente novamente...");
    }
  }
  return;
}
void exec_Ndirecionado_ponderado(){
  int op = 0;
  while(op != -1){
    system("clear");
    texto_menu_exemplos();
    scanf("%d", &op);
    if(op > 0 && op < 4){
      FILE* graph_file = fopen(exemploDeGrafo(op), "r");
      if(!graph_file){
        printf("\n\t\tErro na leitura do arquivo");
      }
      fflush(stdin);
      GraphADJListNDW graph4;
      int countVertex = 0, countEdge = 0, weight = 0;
      fscanf(graph_file, "%d %d %d\n", &countVertex, &countEdge, &weight);
      init_GraphADJListNDW(&graph4, countVertex,  countEdge,  weight == 1 ? true:false);;
      load_GraphADJListNDW(&graph4, graph_file);
      print_GraphADJListNDW(graph4, "graph4");
      destroy_GraphADJListNDW(&graph4);
      fclose(graph_file);
      printf("\n\t\tAperte qualquer tecla para continuar...");
      getchar();
      getchar();
    }
    else if(op == -1){
      printf("\n\t\tVoltando para menu tipos de grafos...");
    }
    else{
      printf("\n\t\tOpcao invalida! Tente novamente...");
    }
  }
  return;
}


int main(void) {
  int op = 0;
  while(op != -1){
    system("clear");
    texto_menu_tipoDeGrafo();
    scanf("%d", &op);
    switch (op){
      case 1:
        exec_direcionado_ponderado();
        break;
      case 2:
        exec_direcionado_Nponderado();
        break;
      case 3:
        exec_Ndirecionado_ponderado();
        break;
      case 4:
        exec_Ndirecionado_Nponderado();
        break;
      case -1:
        printf("\n\t\tEncerrando execucao...");
        break;
      default:
        printf("\n\t\tOpcao invalida! Tente novamente...");
        getchar();
        break;
    }
  }
  return 0;
}


