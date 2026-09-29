#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'values' can be declared as pointer to const [constParameterPointer]
 */
int count_sequences(int *values, int values_count, int length) {
    if (values == NULL || values_count <= 0 || length <= 0) {
        return 0;
    }

    int *dp = (int *)calloc((size_t)length + 1, sizeof(int));
    int *prefix = (int *)calloc((size_t)length + 1, sizeof(int));
    if (dp == NULL || prefix == NULL) {
        free(dp);
        free(prefix);
        return 0;
    }

    dp[0] = 1;
    prefix[0] = 1;

    for (int pos = 1; pos <= length; pos++) {
        int total = 0;
        for (int i = 0; i < values_count; i++) {
            int step = values[i];
            if (step < 0) continue;
            if (pos - step >= 0) {
                total += dp[pos - step];
            }
        }
        dp[pos] = total;
        prefix[pos] = prefix[pos - 1] + total;
    }

    int result = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'i<=length' is not redundant
     */
    for (int i = 0; i <= length; i++) {
        /* Possible weaknesses found:
         *  Assignment 'remaining=length-i', assigned value is greater than -1
         */
        int remaining = length - i;
        /* Possible weaknesses found:
         *  Condition 'remaining>=0' is always true [knownConditionTrueFalse]
         *  Condition 'remaining>=0' is always true
         */
        if (remaining >= 0 && remaining <= length) {
            result += dp[i] * prefix[remaining];
        }
    }

    free(dp);
    free(prefix);
    return result;
}

int main(void) {
    int values[] = {1, 2, 3};
    int values_count = sizeof(values) / sizeof(values[0]);
    int length = 4;

    int result = count_sequences(values, values_count, length);
    printf("%d\n", result);

    return 0;
}