#include <stdio.h>
#include <stdlib.h>

void extract_elements(int* arr, int size, int position, int number, int** result) {
    int i;

    if(position < 0 || position >= size || number <= 0 || (position + number) > size) {
      printf("Invalid parameters\n");
      *result = NULL;
      return;
    }

    *result = (int*)malloc(sizeof(int) * number);
    if(*result == NULL) {
        printf("Memory not allocated\n");
        exit(0);
    }

    for(i = 0; i < number; i++) {
        (*result)[i] = arr[position + i];
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int *result;
    int position = 2;
    int number = 3;

    extract_elements(arr, size, position, number, &result);

    if(result != NULL) {
        for(int i = 0; i < number; i++)
            printf("%d ", result[i]);
        printf("\n");
        free(result);
    }

    return 0;
}