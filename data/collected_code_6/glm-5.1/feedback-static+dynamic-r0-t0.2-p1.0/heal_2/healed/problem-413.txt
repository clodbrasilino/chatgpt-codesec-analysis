#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int c;
} Tuple;

int extract_nth_element(Tuple *list, size_t list_size, size_t n, size_t index, int *result) {
    if (list == NULL || result == NULL) {
        return -1;
    }

    if (index >= list_size) {
        return -1;
    }

    switch (n) {
        case 0:
            *result = list[index].a;
            break;
        case 1:
            *result = list[index].b;
            break;
        case 2:
            *result = list[index].c;
            break;
        default:
            return -1;
    }

    return 0;
}

int main(void) {
    Tuple list[] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    int result;

    if (extract_nth_element(list, list_size, 1, 2, &result) == 0) {
        printf("%d\n", result);
    } else {
        printf("Error\n");
    }

    if (extract_nth_element(list, list_size, 3, 0, &result) == 0) {
        printf("%d\n", result);
    } else {
        printf("Error\n");
    }

    if (extract_nth_element(NULL, list_size, 0, 0, &result) != 0) {
        printf("Error\n");
    }

    return 0;
}