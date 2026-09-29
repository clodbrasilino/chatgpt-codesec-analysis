#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

bool is_even(int num) {
    return (num % 2 == 0);
}

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
void filter_even_numbers(int *array, int size, int **result, int *result_size) {
    int even_count = 0;
    for (int i = 0; i < size; i++) {
        if (is_even(array[i])) {
            even_count++;
        }
    }

    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    *result = (int *)malloc(even_count * sizeof(int));
    if (*result == NULL) {
        *result_size = 0;
        return;
    }

    *result_size = even_count;
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (is_even(array[i])) {
            (*result)[index++] = array[i];
        }
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = 10;
    int *even_numbers;
    int even_size;

    filter_even_numbers(numbers, size, &even_numbers, &even_size);

    for (int i = 0; i < even_size; i++) {
        printf("%d ", even_numbers[i]);
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(even_numbers);
    return 0;
}