#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 4

int** extract_elements(int** arr, int size, int index) {
    int** extracted_elements = (int**) malloc(size * sizeof(int*));

    for(int i=0; i<size; i++) {
        if (arr[i] != NULL) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'extracted_elements' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            extracted_elements[i] = (int*) malloc(sizeof(int));
            if (index >= 0 && index < COLS) {
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL '*extracted_elements_40 + _19' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                *extracted_elements[i] = arr[i][index];
            } else {
                free(extracted_elements[i]);
                extracted_elements[i] = NULL;
            }
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'extracted_elements' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            extracted_elements[i] = NULL;
        }
    }
    return extracted_elements;
}

int main() {
    int** array = (int**) malloc(ROWS * sizeof(int*));
    for(int i=0; i<ROWS; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'array' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        array[i] = (int*) malloc(COLS * sizeof(int));
        for(int j=0; j<COLS; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*array_46 + _6 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            array[i][j] = i*j;
        }
    }

    int** extracted_elements = extract_elements(array, ROWS, 2);
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