#include <stdbool.h>

bool checkOrder(int list1[], int list2[], int size1, int size2) {
  int i = 0, j = 0;
  
  while (i < size1 && j < size2) {
    if (list1[i] == list2[j]) {
      i++;
    }
    j++;
  }
  
  if (i == size1) {
    return true;
  } else {
    return false;
  }
}