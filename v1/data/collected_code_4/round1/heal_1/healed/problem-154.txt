#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 4

int** extract_elements(int** arr, int size, int index) {
    int** extracted_elements = (int**) malloc(size * sizeof(int*));
    if (!extracted_elements) {
        return NULL;
    }

    for(int i=0; i<size; i++) {
        if (arr[i] != NULL) {
            extracted_elements[i] = (int*) malloc(sizeof(int));
            if (extracted_elements[i] == NULL) {
                return NULL;
            }
            if (index >= 0 && index < COLS) {
                *extracted_elements[i] = arr[i][index];
            } else {
                free(extracted_elements[i]);
                extracted_elements[i] = NULL;
            }
        } else {
            extracted_elements[i] = NULL;
        }
    }
    return extracted_elements;
}

int main() {
    int** array = (int**) malloc(ROWS * sizeof(int*));
    if (!array) {
        return -1;
    }

    for(int i=0; i<ROWS; i++) {
        array[i] = (int*) malloc(COLS * sizeof(int));
        if (!array[i]) {
            return -1;
        }

        for(int j=0; j<COLS; j++) {
            array[i][j] = i*j;
        }
    }

    int** extracted_elements = extract_elements(array, ROWS, 2);
    if (!extracted_elements) {
        return -1;
    }
    
    for(int i=0; i<ROWS; i++) {
        if (extracted_elements[i] != NULL) {
            printf("%d\n", *extracted_elements[i]);
            free(extracted_elements[i]);
        }
    }

    for(int i=0; i<ROWS; i++) {
        if (array[i] != NULL) 
            free(array[i]);
    }

    free(extracted_elements);
    free(array);

    return 0;
}