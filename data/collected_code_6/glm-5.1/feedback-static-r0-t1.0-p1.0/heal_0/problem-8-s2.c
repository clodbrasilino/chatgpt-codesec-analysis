#include <stdio.h>
#include <stdlib.h>

int *find_squares(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return NULL;
    }

    int *squares = (int *)malloc(size * sizeof(int));
    if (squares == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        squares[i] = list[i] * list[i];
    }

    return squares;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);

    int *squares = find_squares(list, size);
    if (squares == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", squares[i]);
    }
    printf("\n");

    free(squares);
    squares = NULL;

    return EXIT_SUCCESS;
}