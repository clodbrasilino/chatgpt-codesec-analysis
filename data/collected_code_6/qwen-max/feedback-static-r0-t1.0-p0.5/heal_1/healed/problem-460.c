#include <stdio.h>
#include <stdlib.h>

int* get_first_elements(const int** list, int n, const int* sizes) {
    int* result = malloc(n * sizeof(int));
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
    const int* sizes = (const int[]){2, 3, 0};
    const int** list = malloc(n * sizeof(const int*));
    list[0] = (const int[]){1, 2};
    list[1] = (const int[]){3, 4, 5};
    list[2] = (const int[]){};

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