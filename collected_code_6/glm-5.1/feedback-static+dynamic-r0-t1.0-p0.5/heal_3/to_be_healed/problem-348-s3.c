#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long count_sequences(const int *values, int n, int k, long long current_sum, int depth) {
    if (current_sum < 0) {
        return 0;
    }
    if (depth == k) {
        return 1;
    }
    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += count_sequences(values, n, k, current_sum + values[i], depth + 1);
    }
    return total;
}

int safe_str_to_int(const char *str, int *out_val) {
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') {
        return 0;
    }
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return 0;
    }
    *out_val = (int)val;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    /* Possible weaknesses found:
     *  Assuming that condition 'argc<3' is not redundant
     */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <length> <value1> <value2> ...\n", argv[0]);
        return 1;
    }
    int k;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!safe_str_to_int(argv[1], &k) || k <= 0) {
        fprintf(stderr, "Length must be a positive integer.\n");
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
    int *values = malloc(n * sizeof(int));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (!safe_str_to_int(argv[i + 2], &values[i])) {
            fprintf(stderr, "Invalid integer value provided.\n");
            free(values);
            return 1;
        }
    }
    long long result = count_sequences(values, n, k, 0, 0);
    printf("%lld\n", result);
    free(values);
    return 0;
}