#include <stdio.h>

int countOccurrences(int *array, int element, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == element)
            count++;
    }
    return count;
}

int main() {
   int array[] = {1, 2, 3, 4, 2, 3, 2, 4, 5, 6, 2, 2};
   int size = sizeof(array) / sizeof(array[0]);
   int element = 2;

   int occurrence = countOccurrences(array, element, size);

   printf("Element %d occurred %d times\n", element, occurrence);

   return 0;
}