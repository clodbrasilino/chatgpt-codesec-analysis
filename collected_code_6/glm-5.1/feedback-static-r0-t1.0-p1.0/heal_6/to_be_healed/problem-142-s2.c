#include <stdio.h>
#include <stdlib.h>

int count_same_triples(const int *a, const int *b, const int *c, size_t size_a, size_t size_b, size_t size_c) {
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
    /* Possible weaknesses found:
     *  Assignment 'size_a=3', assigned value is 3
     *  'size_a' is assigned value '3' here.
     */
    size_t size_a = 3;
    /* Possible weaknesses found:
     *  'size_b' is assigned value '3' here.
     *  Assignment 'size_b=3', assigned value is 3
     */
    size_t size_b = 3;
    /* Possible weaknesses found:
     *  Assignment 'size_c=3', assigned value is 3
     *  'size_c' is assigned value '3' here.
     */
    size_t size_c = 3;

    /* Possible weaknesses found:
     *  Same expression on both sides of '||' because '!size_c' and '!size_b' represent the same value. [knownConditionTrueFalse]
     *  Condition '!size_b' is always false
     *  Same expression on both sides of '||' because '!size_a' and '!size_b' represent the same value. [knownConditionTrueFalse]
     *  Condition '!size_c' is always false [knownConditionTrueFalse]
     *  Same expression on both sides of '||' because '!size_c' and '!size_b' represent the same value.
     *  Same expression on both sides of '||' because '!size_a' and '!size_b' represent the same value.
     *  Condition '!size_c' is always false
     *  Condition '!size_a' is always false [knownConditionTrueFalse]
     *  Condition '!size_a' is always false
     *  Condition '!size_b' is always false [knownConditionTrueFalse]
     */
    if (!size_a || !size_b || !size_c) {
        return EXIT_FAILURE;
    }

    const int a[] = {1, 2, 3};
    const int b[] = {1, 2, 4};
    const int c[] = {1, 5, 2};

    int result = count_same_triples(a, b, c, size_a, size_b, size_c);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}