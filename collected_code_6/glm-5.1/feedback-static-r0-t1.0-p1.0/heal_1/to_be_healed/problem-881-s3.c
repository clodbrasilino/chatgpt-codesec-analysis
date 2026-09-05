#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
void find_sums(int *list, size_t size, int *sum_even, int *sum_odd) {
    int found_even = 0;
    int found_odd = 0;

    /* Possible weaknesses found:
     *  Either the condition 'sum_even==NULL' is redundant or there is possible null pointer dereference: sum_even. [nullPointerRedundantCheck]
     *  Null pointer dereference
     */
    *sum_even = 0;
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Either the condition 'sum_odd==NULL' is redundant or there is possible null pointer dereference: sum_odd. [nullPointerRedundantCheck]
     */
    *sum_odd = 0;

    /* Possible weaknesses found:
     *  Assuming that condition 'sum_even==NULL' is not redundant
     *  Assuming that condition 'sum_odd==NULL' is not redundant
     */
    if (list == NULL || sum_even == NULL || sum_odd == NULL) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            if (!found_even) {
                *sum_even = list[i];
                found_even = 1;
            }
        } else {
            if (!found_odd) {
                *sum_odd = list[i];
                found_odd = 1;
            }
        }
    }
}

int main(void) {
    int list[] = {1, 3, 5, 2, 4, 7, 6, 8, 9};
    size_t size = sizeof(list) / sizeof(list[0]);
    int sum_even = 0;
    int sum_odd = 0;

    find_sums(list, size, &sum_even, &sum_odd);

    printf("Sum of first even number: %d\n", sum_even);
    printf("Sum of first odd number: %d\n", sum_odd);

    return 0;
}