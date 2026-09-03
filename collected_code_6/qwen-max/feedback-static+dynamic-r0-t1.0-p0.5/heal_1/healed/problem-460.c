#include <stdio.h>
#include <stdlib.h>

int* get_first_elements(int** list, int n, const int* sizes) {
    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; ++i) {
        if (sizes[i] > 0) {
            result[i] = list[i][0];
        } else {
            result[i] = 0;
        }
    }
    return result;
}

int main() {
    int n = 3;
    const int sizes[] = {2, 3, 0};
    int** list = (int**)malloc(n * sizeof(int*));
    list[0] = (int[]){1, 2};
    list[1] = (int[]){3, 4, 5};
    list[2] = (int[]){};

    int* first_elements = get_first_elements(list, n, sizes);
    if (first_elements != NULL) {
        for (int i = 0; i < n; ++i) {
            printf("%d ", first_elements[i]);
        }
        free(first_elements);
    }

    free(list);

    return 0;
}