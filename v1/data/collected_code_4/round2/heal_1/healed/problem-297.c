#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 256

typedef struct {
  int size;
  int *data;
} List;

List* createList(int size) {
  List* list = (List*)malloc(sizeof(List));
  if (list == NULL) {
    return NULL;
  }
  list->size = size;
  list->data = (int*)malloc(size * sizeof(int));
  if (list->data == NULL) {
    free(list);
    return NULL;
  }
  return list;
}

void flattenList(List **nestedList, int size, List *resultList) {
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < nestedList[i]->size; j++) {
      if (resultList->size >= MAX_SIZE * MAX_SIZE) 
        return;
      resultList->data[resultList->size++] = nestedList[i]->data[j];
    }
  }
}

void freeList(List* list) {
  if (list) {
    free(list->data);
    free(list);
  }
}

int main() {
  int i;
  List *nestedList[MAX_SIZE];
  
  for(i = 0; i < MAX_SIZE; i++) {
    nestedList[i] = createList(MAX_SIZE);
    if (nestedList[i] == NULL) {
      for (int j = 0; j < i; j++) {
        freeList(nestedList[j]);
      }
      return 1;
    }
  }
  
  List *resultList = createList(MAX_SIZE*MAX_SIZE);
  if (resultList == NULL) {
    for (int j = 0; j < MAX_SIZE; j++) {
      freeList(nestedList[j]);
    }
    return 1;
  }
  resultList->size = 0;

  flattenList(nestedList, MAX_SIZE, resultList);

  printf("[");
  for(i = 0; i < resultList->size - 1; i++) {
    printf("%d, ", resultList->data[i]);
  }

  printf("%d]\n", resultList->data[i]);

  for(i = 0; i < MAX_SIZE; i++) {
    freeList(nestedList[i]);
  }
  
  freeList(resultList);

  return 0;
}