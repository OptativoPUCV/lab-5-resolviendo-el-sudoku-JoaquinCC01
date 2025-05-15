#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){ 
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i,j,k;
  int arr[10];
  for (i=0;i<9;i++){
    memset(arr,0,sizeof(arr));
    for (j=0;j<9;j++){
      k = n->sudo[i][j];
      if(k){
        if(arr[k]) return 0;
        arr[k] = 1;
      }
        
      }
    }
  for (j=0;j<9;j++){
    memset(arr,0,sizeof(arr));
    for (i=0;i<9;i++){
      k = n->sudo[i][j];
      if(k){
        if(arr[k]) return 0;
        arr[k] = 1;
      }  
      }
    }
  for (int bi = 0; bi < 9; bi += 3) { // bi y bj nos dicen los subbloques de 3x3
    for (int bj = 0; bj < 9; bj += 3) {
        memset(arr, 0, sizeof(arr));
        for (int di = 0; di < 3; di++) { // di filas y dj columnas
            for (int dj = 0; dj < 3; dj++) {
                int k = n->sudo[bi + di][bj + dj];
                if (k) {
                    if (arr[k]) return 0;
                    arr[k] = 1;
                }
            }
        }
    }
}
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    for(int i = 0; i<9;i++){
      for(int j = 0; j<9;j++){
        if(n->sudo[i][j] == 0){
          for (int k = 1; k <= 9; k++){
            n->sudo[i][j] = k;
            if(is_valid(n)){
              Node* new = copy(n);
              pushBack(list, new);
            }
          }
        }
      }
    }
    return list;
}


int is_final(Node* n){
  if (!is_valid(n)) return 0;
  else{
  for (int i=0;i<9;i++){
    for (int j=0;j<9;j++){
      if(n->sudo[i][j] == 0)
        return 0;
      }
    }
  return 1;
}
}

Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
  push(stack, initial);
  while(!is_empty(stack)){
    Node* n = top(stack);
    pop(stack);
    (*cont)++;
    if(is_final(n)){
      return n;
    }
    List* adj = get_adj_nodes(n);
    for (int i=0;i<get_size(adj);i++){
      Node* new = (Node*)front(adj);
      push(stack, new);
      popFront(adj);
    }
    clean(adj);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/