#ifndef DEEPSEARCH_H_INCLUDED
#define DEEPSEARCH_H_INCLUDED

typedef struct DeepSearchVertex{
  int startTime;
  int endTime;
  char* edgeType;
}DeepSearchVertex;
typedef struct DeepSearch{
  Pilha vertexStack;
  DeepSearchVertex* deepSearchTree;
}DeepSearch;
void init_deepSearch(DeepSearch* deepSearch, int countVertex){
  create_pilha(&deepSearch->vertexStack);
  deepSearch->deepSearchTree = (DeepSearchVertex*)malloc(countVertex * sizeof(DeepSearchVertex));
  for(int i=0; i<countVertex; i++){
    deepSearch->deepSearchTree[i].startTime = 0;
    deepSearch->deepSearchTree[i].endTime = 0;
    deepSearch->deepSearchTree[i].edgeType = (char*)calloc(countVertex, sizeof(char));
  }
}
long sum_vertex(int Vertex){
  return (Vertex * pow(10,Vertex - 1));
}
Pilha count_cycle_paths(GraphADJListNDW graph, int A){
  int contador_ciclos = 0;
  VerticePilha popVertex;
  int vertex = graph.vertex_array[A].vertex, vertex_index = 1, vertex_count = 1, i = 0;
  long vertex_sum = sum_vertex(graph.vertex_array[A].vertex);
  Cell *temp;
  Pilha aux_stack;
  Pilha return_stack;
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
      if(temp->successor_node == A+1 && aux_stack.topo->dado != A+1){
        contador_ciclos += 1;
        //printf("\nVERTICE: %d\t%d\t%d\t%d\t\n", vertex, vertex_sum, vertex_index, vertex_count);
        push(&return_stack, vertex, vertex_sum, vertex_count, vertex_index);
        popVertex = pop(&aux_stack);
        vertex = popVertex.vertice;
        vertex_sum = popVertex.soma;
        vertex_count = popVertex.count;
        vertex_index = popVertex.index + 1;
      } 
      else if(!procura_pilha(aux_stack, temp->successor_node)){
        push(&aux_stack, vertex, vertex_sum, vertex_count, vertex_index);
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
      popVertex = pop(&aux_stack);
      vertex = popVertex.vertice;
      vertex_sum = popVertex.soma;
      vertex_count = popVertex.count;
      vertex_index = popVertex.index + 1;
    }
    //getchar();
  }
  //printf("\n\t\tcontador_ciclos: %d \n", contador_ciclos);
  destroy_pilha(&aux_stack);
  return return_stack;
}

void count_cycles_DeepSearch(DeepSearch deepSearch,  GraphADJListNDW graph){
  int count = 0;
  Pilha total_cycle, aux_cycle;
  VerticePilha vertice_aux;
  create_pilha(&total_cycle);
  for(int i=0; i<graph.countVertex; i++){
    for(int j=0; j<graph.countVertex;j++){
      if(deepSearch.deepSearchTree[i].edgeType[j] == 'R' || deepSearch.deepSearchTree[i].edgeType[j] == 'C'){
        count++;
        aux_cycle = count_cycle_paths(graph,  j);
        while(aux_cycle.topo != 0){
          vertice_aux = pop(&aux_cycle);
          if(!procura_vertice_pilha(total_cycle, vertice_aux)){
            push(&total_cycle, vertice_aux.vertice, vertice_aux.soma, vertice_aux.count, vertice_aux.index);
          }
          
        }
        destroy_pilha(&aux_cycle);
      }
      
    }
    
  }
  print_pilha(total_cycle);
  destroy_pilha(&total_cycle);
}


void print_deepSearch(DeepSearch deepSearch, int countVertex){
 
  printf("\t\tTabela tempos \t tam: %d\n", countVertex);
  printf("\tStartTime: ");
  for(int i=0; i<countVertex; i++){
    printf("\t%d",deepSearch.deepSearchTree[i].startTime);
  }
  printf("\n\tEndTime: ");
  for(int i=0; i<countVertex; i++){
    printf("\t%d",deepSearch.deepSearchTree[i].endTime);
  }
  printf("\n\t\tTabela tipo de arestas\n");
  printf("\t\t\n\t");
  for(int i=0; i<countVertex; i++)
    printf("\t[%d]", i+1);

  printf("\n");
  for(int i=0; i<countVertex; i++){
    printf("\t[%d]",i+1);
    for(int j=0; j<countVertex;j++){
      printf("\t %c", deepSearch.deepSearchTree[i].edgeType[j]);
    }
    printf("\n");
  }
  printf("\n");
  
  return;
}

int return_vertex_on_list(DeepSearch* deepSearch, GraphADJListNDW graph, int vertex){
  
  Cell *temp = graph.vertex_array[vertex-1].successor_list.first_cell->next_cell;
  while(temp!=NULL){
    if(deepSearch->deepSearchTree[temp->successor_node -1].startTime == 0){
      deepSearch->deepSearchTree[vertex -1].edgeType[temp->successor_node - 1] = 'A';
      deepSearch->deepSearchTree[temp->successor_node - 1].edgeType[vertex - 1] = 'N';
      return temp->successor_node;
    }
    else if(deepSearch->vertexStack.tamanho != 0){
      if(deepSearch->deepSearchTree[vertex - 1].startTime > deepSearch->deepSearchTree[temp->successor_node -1].startTime && temp->successor_node != deepSearch->vertexStack.topo->dado){
        deepSearch->deepSearchTree[vertex - 1].edgeType[temp->successor_node - 1] = 'R';
        deepSearch->deepSearchTree[temp->successor_node - 1].edgeType[vertex - 1] = 'C';
      }
    }
    temp = temp->next_cell;
  }
  return -1;
}
void search(DeepSearch* deepSearch, GraphADJListNDW graph, int root){
  int time = 1, vertex = -1, nextVertex = -1;
  if(graph.countVertex >= root){
    vertex = graph.vertex_array[root-1].vertex;
    deepSearch->deepSearchTree[root-1].startTime = time;
    while(deepSearch->deepSearchTree[root-1].endTime == 0){
        int aux = return_vertex_on_list(deepSearch, graph, vertex);
        time++;
        if(aux == -1){
          deepSearch->deepSearchTree[vertex-1].endTime = time; 
          nextVertex = pop(&deepSearch->vertexStack).vertice;
        }
        else{
          nextVertex = aux;
          deepSearch->deepSearchTree[nextVertex-1].startTime = time;
          push(&deepSearch->vertexStack, vertex, 0, 0, 0);
        }
        vertex = nextVertex;
    }
  }
  return;
}
void destroy_deepSearch(DeepSearch* deepSearch, int countVertex){
  for(int i=0; i<countVertex; i++)
    free(deepSearch->deepSearchTree[i].edgeType);
  free(deepSearch->deepSearchTree);
}



#endif // DEEPSEARCH_H_INCLUDED