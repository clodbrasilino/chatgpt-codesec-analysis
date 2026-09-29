#include <stdio.h>
#include <stdlib.h>

void square_elements(int *list, int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9998999 * 9998999 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000009,time:4069,execs:2590,op:havoc,rep:2)
         * UBSan: signed integer overflow: 1410065408 * 1410065408 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:20847,execs:12563,op:havoc,rep:6)
         * UBSan: signed integer overflow: 92149077 * 92149077 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:6579,execs:4196,op:havoc,rep:2)
         */
        list[i] = list[i] * list[i];
    }
}

int main(void) {
    int size;
    int *list;

    printf("Enter number of elements: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    list = malloc((size_t)size * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &list[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(list);
            return EXIT_FAILURE;
        }
    }

    square_elements(list, size);

    printf("Squared elements:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return EXIT_SUCCESS;
}