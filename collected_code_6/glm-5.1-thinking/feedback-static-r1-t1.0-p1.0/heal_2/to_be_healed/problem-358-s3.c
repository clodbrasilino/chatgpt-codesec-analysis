#include <stdio.h>
#include <stddef.h>

int list_modulo(const int *a, const int *b, int *result, size_t size) {
    if (a == NULL || b == NULL || result == NULL) {
        return -1;
    }
    if (size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (b[i] == 0) {
            return -1;
        }
        result[i] = a[i] % b[i];
    }
    return 0;
}

int main(void) {
    const int a[] = {10, 25, 33, 44, 50};
    const int b[] = {3, 4, 7, 6, 11};
    size_t size = sizeof(a) / sizeof(a[0]);
    int result[5];

    if (list_modulo(a, b, result, size) == 0) {
        for (size_t i = 0; i < size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    } else {
        printf("Error calculating modulo\n");
    }

    const int c[] = {10, 20, 30};
    const int d[] = {2, 0, 5};
    int res2[3];

    if (list_modulo(c, d, res2, 3)) {
        printf("Division by zero handled\n");
    }

    /* Possible weaknesses found:
     *  Calling function 'list_modulo' returns -1
     *  Condition 'list_modulo(NULL,b,result,size)' is always true [knownConditionTrueFalse]
     *  Condition 'list_modulo(NULL,b,result,size)' is always true
     */
    if (list_modulo(NULL, b, result, size)) {
        printf("Null pointer handled\n");
    }

    return 0;
}