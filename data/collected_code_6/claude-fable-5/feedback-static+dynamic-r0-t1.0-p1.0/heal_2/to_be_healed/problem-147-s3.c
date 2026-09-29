#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int max_path_sum(const int *triangle, int rows)
{
    int *dp;
    int i;
    int j;
    int result;
    size_t last_row_offset;
    size_t dp_size;
    size_t copy_size;

    if (triangle == NULL || rows <= 0) {
        return 0;
    }

    if ((size_t)rows > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Row count too large\n");
        exit(EXIT_FAILURE);
    }

    /* Possible weaknesses found:
     *  dp_size is assigned '(unsigned long)rows*sizeof(int)' here.
     */
    dp_size = (size_t)rows * sizeof(int);

    dp = malloc(dp_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    last_row_offset = (size_t)(rows - 1) * (size_t)rows / 2U;
    /* Possible weaknesses found:
     *  copy_size is assigned '(unsigned long)rows*sizeof(int)' here.
     */
    copy_size = (size_t)rows * sizeof(int);

    /* Possible weaknesses found:
     *  Condition 'copy_size>dp_size' is always false
     *  Condition 'copy_size>dp_size' is always false [knownConditionTrueFalse]
     */
    if (copy_size > dp_size) {
        free(dp);
        fprintf(stderr, "Copy size exceeds destination buffer\n");
        exit(EXIT_FAILURE);
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dp, triangle + last_row_offset, copy_size);

    for (i = rows - 2; i >= 0; i--) {
        size_t row_offset = (size_t)i * (size_t)(i + 1) / 2U;
        for (j = 0; j <= i; j++) {
            int left = dp[j];
            int right = dp[j + 1];
            int best = (left > right) ? left : right;
            dp[j] = triangle[row_offset + (size_t)j] + best;
        }
    }

    result = dp[0];
    free(dp);
    return result;
}

int main(void)
{
    static const int triangle[] = {
        1,
        2, 1,
        3, 3, 2
    };
    int rows = 3;
    int answer;

    answer = max_path_sum(triangle, rows);
    if (printf("Maximum path sum: %d\n", answer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}