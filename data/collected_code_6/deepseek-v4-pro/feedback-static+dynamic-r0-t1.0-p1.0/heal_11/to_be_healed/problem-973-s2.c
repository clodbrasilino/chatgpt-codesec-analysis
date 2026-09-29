#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, int n, size_t buffer_size) {
    if (str == NULL || n <= 0 || buffer_size == 0) {
        return;
    }

    size_t len = strnlen(str, buffer_size);
    if (len == 0 || len >= buffer_size) {
        return;
    }

    n = n % (int)len;
    if (n == 0) {
        return;
    }

    size_t rotate_count = (size_t)n;
    if (rotate_count > len) {
        return;
    }

    size_t remaining = len - rotate_count;

    /* Possible weaknesses found:
     *  Assuming condition 'rotate_count>buffer_size' is false
     */
    if (rotate_count > buffer_size) {
        return;
    }

    char *temp = malloc(rotate_count);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return;
    }

    /* Possible weaknesses found:
     *  Condition 'rotate_count<=buffer_size' is always true
     *  Same expression on both sides of '&&'. [duplicateExpression]
     *  Condition 'rotate_count<=buffer_size' is always true [knownConditionTrueFalse]
     */
    if (rotate_count <= buffer_size && rotate_count <= buffer_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str, rotate_count);
    } else {
        free(temp);
        return;
    }

    if (remaining + 1 < buffer_size) {
        memmove(str, str + rotate_count, remaining + 1);
    } else {
        free(temp);
        return;
    }

    if (remaining + rotate_count < buffer_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str + remaining, temp, rotate_count);
    } else {
        free(temp);
        return;
    }

    if (len < buffer_size) {
        str[len] = '\0';
    }

    free(temp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[100];

    snprintf(buffer, sizeof(buffer), "%s", "abcdef");
    left_rotate_string(buffer, 2, sizeof(buffer));
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%s", "hello");
    left_rotate_string(buffer, 7, sizeof(buffer));
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%s", "test");
    left_rotate_string(buffer, 0, sizeof(buffer));
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%s", "");
    left_rotate_string(buffer, 3, sizeof(buffer));
    printf("%s\n", buffer);

    return 0;
}