#include <stdio.h>
#include <stdlib.h>

int count_same_triples(const int *a, const int *b, const int *c, size_t size_a, size_t size_b, size_t size_c) {
    if (size_a == 0 || size_b == 0 || size_c == 0) {
        return 0;
    }
    
    int count = 0;
    size_t i, j, k;
    for (i = 0; i < size_a; i++) {
        for (j = 0; j < size_b; j++) {
            if (a[i] == b[j]) {
                for (k = 0; k < size_c; k++) {
                    if (a[i] == c[k]) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int main(void) {
    const int a[] = {1, 2, 3};
    const int b[] = {1, 2, 4};
    const int c[] = {1, 5, 2};

    /* Possible weaknesses found:
     *  Assignment 'size_a=sizeof(a)/sizeof(a[0])', assigned value is 3
     */
    size_t size_a = sizeof(a) / sizeof(a[0]);
    /* Possible weaknesses found:
     *  Assignment 'size_b=sizeof(b)/sizeof(b[0])', assigned value is 3
     */
    size_t size_b = sizeof(b) / sizeof(b[0]);
    /* Possible weaknesses found:
     *  Assignment 'size_c=sizeof(c)/sizeof(c[0])', assigned value is 3
     */
    size_t size_c = sizeof(c) / sizeof(c[0]);

    /* Possible weaknesses found:
     *  Condition '!size_b' is always false
     *  Condition '!size_c' is always false [knownConditionTrueFalse]
     *  Condition '!size_c' is always false
     *  Condition '!size_a' is always false [knownConditionTrueFalse]
     *  Condition '!size_a' is always false
     *  Condition '!size_b' is always false [knownConditionTrueFalse]
     */
    if (!size_a || !size_b || !size_c) {
        return EXIT_FAILURE;
    }

    int result = count_same_triples(a, b, c, size_a, size_b, size_c);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}