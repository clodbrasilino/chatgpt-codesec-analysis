#include <stdio.h>
#include <stdlib.h>

size_t count_integers(const int *list, size_t max_elements) {
    size_t count = 0;

    for (size_t i = 0; i < max_elements; i++) {
        /* Possible weaknesses found:
         *  Possible null pointer dereference: list [nullPointer]
         *  Null pointer dereference
         */
        if (list[i] != 0) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int numbers[] = {1, 2, 0, 4, 5, 0, 7, 8, 9, 10};
    size_t max_elements = sizeof(numbers) / sizeof(numbers[0]);

    size_t result = count_integers(numbers, max_elements);

    printf("%zu\n", result);

    /* Possible weaknesses found:
     *  Calling function 'count_integers', 1st argument 'NULL' value is 0
     */
    size_t null_result = count_integers(NULL, max_elements);
    
    if (null_result == 0) {
        printf("0\n");
    }

    return 0;
}