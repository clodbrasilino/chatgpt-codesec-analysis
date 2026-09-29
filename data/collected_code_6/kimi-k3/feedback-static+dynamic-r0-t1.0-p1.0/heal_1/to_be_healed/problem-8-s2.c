#include <stdio.h>
#include <stdlib.h>

void square_elements(int *list, size_t size)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 8888888 * 8888888 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:10890,execs:3523,op:havoc,rep:7)
         * UBSan: signed integer overflow: 110799530 * 110799530 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:27030,execs:6964,op:havoc,rep:2)
         * UBSan: signed integer overflow: -2072745074 * -2072745074 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:31718,execs:8912,op:havoc,rep:1)
         */
        list[i] = list[i] * list[i];
    }
}

int main(void)
{
    size_t size;
    size_t i;
    int *list;

    if (printf("Enter the number of elements: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &size) != 1 || size == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    list = malloc(size * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu integers: ", size) < 0) {
        free(list);
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++) {
        if (scanf("%d", &list[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(list);
            return EXIT_FAILURE;
        }
    }

    square_elements(list, size);

    if (printf("Squares: ") < 0) {
        free(list);
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++) {
        if (printf("%d ", list[i]) < 0) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}