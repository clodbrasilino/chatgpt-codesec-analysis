#include <stdio.h>

void shiftElement(const int* list, int size) {
  int temp = list[0];

  for (int i = 0; i < size - 1; i++) {
    /* Possible weaknesses found:
     *  assignment of read-only location '*(list + (sizetype)((long unsigned int)i * 4))'
     */
    *(list + i) = *(list + i + 1);
  }

  /* Possible weaknesses found:
   *  assignment of read-only location '*(list + ((sizetype)((long unsigned int)size * 4) + 18446744073709551612))'
   */
  *(list + size - 1) = temp;
}

int main() {
  int list[5] = {1, 2, 3, 4, 5};

  shiftElement(list, 5);

  for (int i = 0; i < 5; i++) {
    printf("%d ", list[i]);
  }

  return 0;
}