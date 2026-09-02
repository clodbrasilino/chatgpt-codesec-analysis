#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const. However it seems that 'print_list' is a callback function, if 'list' is declared with const you might also need to cast function pointer(s). [constParameterCallback]
 *  Parameter 'list' can be declared as pointer to const
 */
void print_list(int *list, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

void map_print(int *list, int n, void (*print_func)(int*, int)) {
    if (list && print_func) {
        print_func(list, n);
    }
}

int main() {
    int n = 5;
    int *list = malloc(n * sizeof(int));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; ++i) {
        list[i] = i + 1;
    }

    for (int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         *  You might need to cast the function pointer here
         */
        map_print(list, n, print_list);
    }

    free(list);
    return EXIT_SUCCESS;
}