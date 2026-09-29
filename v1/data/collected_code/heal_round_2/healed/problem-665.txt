#include <stdio.h>

void shiftElement(int* list, int size) {
  int temp = list[0];

  for (int i = 0; i < size - 1; i++) {
    list[i] = list[i + 1];
  }

  list[size - 1] = temp;
}

int main() {
  int list[5] = {1, 2, 3, 4, 5};

  shiftElement(list, 5);

  for (int i = 0; i < 5; i++) {
    printf("%d ", list[i]);
  }

  return 0;
}