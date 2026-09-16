#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

int *multiply_adjacent(const int *tuple, int size, int *result_size) {
    if (tuple == NULL || size < 2 || result_size == NULL) {
        if (result_size != NULL) *result_size = 0;
        return NULL;
    }

    int *result = (int *)malloc((size - 1) * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < size - 1; i++) {
        result[i] = tuple[i] * tuple[i + 1];
    }

    *result_size = size - 1;
    return result;
}

int main(void) {
    int tuple[] = {2, 3, 4, 5};
    int tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    int result_size = 0;

    int *result = multiply_adjacent(tuple, tuple_size, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
             *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
             */
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}