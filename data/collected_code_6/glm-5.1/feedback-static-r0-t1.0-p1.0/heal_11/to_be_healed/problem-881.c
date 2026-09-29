#include <stdio.h>
#include <stdlib.h>

int* find_sum_first_even_odd(const int* list, size_t size) {
    int* result = (int*)malloc(2 * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    result[0] = -1;
    result[1] = -1;

    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 == 0 && result[0] == -1) {
            result[0] = list[i];
        } else if (list[i] % 2 != 0 && result[1] == -1) {
            result[1] = list[i];
        }
        
        if (result[0] != -1 && result[1] != -1) {
            break;
        }
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* const argv[const]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    size_t size = argc - 1;
    int* list = (int*)malloc(size * sizeof(int));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        list[i] = atoi(argv[i + 1]);
    }

    int* result = find_sum_first_even_odd(list, size);
    if (result == NULL) {
        free(list);
        return EXIT_FAILURE;
    }

    if (result[0] != -1) {
        printf("%d\n", result[0]);
    }
    if (result[1] != -1) {
        printf("%d\n", result[1]);
    }

    free(result);
    free(list);

    return EXIT_SUCCESS;
}