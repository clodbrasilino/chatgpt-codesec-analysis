#include <stdio.h>

int findLength(int* list);

int minListLength(int* lists[], int numLists) {
  int minLength = -1;
  int minIndex = -1;

  for(int i = 0; i < numLists; i++) {
    int length = findLength(lists[i]);
    if(minLength == -1 || length < minLength) {
      minLength = length;
      minIndex = i;
    }
  }
  
  return (minIndex != -1) ? minIndex : -1;
}

int findLength(int* list) {
  int length;
  
  for(length = 0; list[length] != '\0'; length++);
  
  return length;
}

int main() {
  int list1[4] = {1, 2, 3, 0};
  int list2[5] = {4, 5, 6, 7, 0};
  int list3[3] = {8, 9, 0};

  int* lists[3] = {list1, list2, list3};

  printf("The index of the shortest list is: %d\n", minListLength(lists, 3));

  return 0;
}