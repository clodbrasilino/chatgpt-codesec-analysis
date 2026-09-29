#include <stdio.h>
#include <stdbool.h>

bool check_tuples(int tuple1[], int tuple2[], int size1, int size2) {
  if (size1 != size2) {
    return false;
  }

  for (int i = 0; i < size1; i++) {
    if (tuple2[i] >= tuple1[i]) {
      return false;
    }
  }

  return true;
}

int main() {
  int tuple1[] = {1, 2, 3, 4, 5};
  int tuple2[] = {0, 1, 2, 3, 4};
  int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
  int size2 = sizeof(tuple2) / sizeof(tuple2[0]);

  if (check_tuples(tuple1, tuple2, size1, size2)) {
    printf("Yes, each element of second tuple is smaller than its corresponding index in first tuple.\n");
  } else {
    printf("No, each element of second tuple is not smaller than its corresponding index in first tuple.\n");
  }

  return 0;
}