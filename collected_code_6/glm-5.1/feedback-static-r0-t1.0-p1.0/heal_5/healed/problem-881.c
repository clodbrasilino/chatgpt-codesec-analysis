#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

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

int main(int argc, char* const argv[]) {
    (void)argc;
    (void)argv;
    return EXIT_SUCCESS;
}