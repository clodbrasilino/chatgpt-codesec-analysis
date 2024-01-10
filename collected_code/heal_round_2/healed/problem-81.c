#include <stdio.h>
#include <stdlib.h>

void zipTuples(const int* tuple1, const int* tuple2, int size) {
    int* zipTuple = (int*)malloc(size * 2 * sizeof(int));
    
    if (zipTuple != NULL) {
        for (int i = 0; i < size * 2; i += 2) {
            zipTuple[i] = tuple1[i / 2];
            zipTuple[i + 1] = tuple2[i / 2];
        }
        
        printf("Zip Tuple: ");
        for (int i = 0; i < size * 2; i++) {
            printf("%d ", zipTuple[i]);
        }

        free(zipTuple);
    } else {
        printf("Memory not allocated.\n");
    }
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);

    zipTuples(tuple1, tuple2, size);
    
    return 0;
}