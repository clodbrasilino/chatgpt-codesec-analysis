#include <stdio.h>
#include <stdlib.h>

int* extractElements(int* array, int start, int count) {
    int* result = malloc(count * sizeof(int));
    if(result == NULL) {
      return NULL;
    }

    for(int i = 0; i < count; i++) {
        result[i] = array[start + i];
    }

    return result;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int start = 2;
    int count = 5;
    int* extracted = extractElements(array, start, count);

    if(extracted != NULL){
        for(int i = 0; i < count; i++) {
            printf("%d ", extracted[i]);
        }
        free(extracted);
    }

    return 0;
}