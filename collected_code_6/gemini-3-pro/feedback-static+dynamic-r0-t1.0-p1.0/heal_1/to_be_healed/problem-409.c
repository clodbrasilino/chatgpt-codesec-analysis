#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int findRowMinProduct(Tuple* row, size_t cols) {
    if (row == NULL || cols == 0) {
        return 0;
    }

    int minProduct = INT_MAX;

    for (size_t i = 0; i < cols; i++) {
        int product = row[i].first * row[i].second;
        if (product < minProduct) {
            minProduct = product;
        }
    }

    return minProduct;
}

/* Possible weaknesses found:
 *  Parameter 'colsPerRow' can be declared as pointer to const [constParameterPointer]
 */
int* findMinProducts(Tuple** list, size_t rows, size_t* colsPerRow) {
    if (list == NULL || rows == 0 || colsPerRow == NULL) {
        return NULL;
    }

    int* minProducts = (int*)malloc(rows * sizeof(int));
    if (minProducts == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        if (list[i] != NULL && colsPerRow[i] > 0) {
            minProducts[i] = findRowMinProduct(list[i], colsPerRow[i]);
        } else {
            minProducts[i] = 0; 
        }
    }

    return minProducts;
}

int main(void) {
    size_t rows = 3;
    size_t colsPerRow[] = {2, 3, 1};

    Tuple** list = (Tuple**)malloc(rows * sizeof(Tuple*));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        list[i] = (Tuple*)malloc(colsPerRow[i] * sizeof(Tuple));
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
    }

    list[0][0] = (Tuple){1, 2};
    list[0][1] = (Tuple){3, -4};

    list[1][0] = (Tuple){0, 5};
    list[1][1] = (Tuple){6, 2};
    list[1][2] = (Tuple){-1, -1};

    list[2][0] = (Tuple){7, 8};

    int* results = findMinProducts(list, rows, colsPerRow);
    if (results != NULL) {
        for (size_t i = 0; i < rows; i++) {
            printf("%d\n", results[i]);
        }
        free(results);
    }

    for (size_t i = 0; i < rows; i++) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}