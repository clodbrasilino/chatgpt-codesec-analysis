#include <stdio.h>
#include <stdlib.h>

int count_sequences(int *values, int n, int k, int current_sum, int depth) {
    if (current_sum < 0) {
        return 0;
    }
    if (depth == k) {
        return 1;
    }
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += count_sequences(values, n, k, current_sum + values[i], depth + 1);
    }
    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    /* Possible weaknesses found:
     *  Assuming that condition 'argc<3' is not redundant
     */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <sequence_length> <value1> <value2> ...\n", argv[0]);
        return 1;
    }
    int k = atoi(argv[1]);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (k <= 0) {
        fprintf(stderr, "Sequence length must be a positive integer.\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  Assignment 'n=argc-2', assigned value is greater than 0
     */
    int n = argc - 2;
    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     *  Condition 'n<=0' is always false
     */
    if (n <= 0) {
        fprintf(stderr, "At least one value must be provided.\n");
        return 1;
    }
    int *values = (int *)malloc(n * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        values[i] = atoi(argv[i + 2]);
    }
    int result = count_sequences(values, n, k, 0, 0);
    printf("%d\n", result);
    free(values);
    return 0;
}