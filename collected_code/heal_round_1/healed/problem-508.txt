#include <stdbool.h>

bool checkOrder(const int list1[], const int list2[], int size1, int size2) {
  int i = 0, j = 0;
  
  while (i < size1 && j < size2) {
    if (list1[i] == list2[j]) {
      i++;
    }
    j++;
  }
  
  return i == size1;
}

int main() {
  const int list1[] = {1, 2, 3, 4, 5};
  const int list2[] = {1, 2, 3, 4, 5};
  int size1 = sizeof(list1) / sizeof(list1[0]);
  int size2 = sizeof(list2) / sizeof(list2[0]);

  bool result = checkOrder(list1, list2, size1, size2);

  return result;
}