#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

int left_rotate(char *str, size_t buf_size, size_t d)
{
    size_t len;
    size_t first_part;
    size_t second_part;
    char *temp;

    if (str == NULL || buf_size == 0 || buf_size > MAX_STR_LEN) {
        return -1;
    }

    len = strnlen(str, buf_size);
    if (len == buf_size) {
        return -1;
    }

    if (len == 0) {
        return 0;
    }

    d = d % len;
    if (d == 0) {
        return 0;
    }

    first_part = len - d;
    second_part = d;

    /* Possible weaknesses found:
     *  Assuming that condition 'first_part+second_part!=len' is not redundant
     */
    if (first_part > len || second_part > len || first_part + second_part != len) {
        return -1;
    }

    temp = malloc(len + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return -1;
    }

    if (first_part > 0 && d < len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str + d, first_part);
    }

    /* Possible weaknesses found:
     *  Condition 'first_part+second_part<=len' is always true [knownConditionTrueFalse]
     *  Condition 'first_part+second_part<=len' is always true
     */
    if (second_part > 0 && first_part + second_part <= len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp + first_part, str, second_part);
    }

    temp[len] = '\0';

    if (len + 1 <= buf_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str, temp, len + 1);
    } else {
        free(temp);
        return -1;
    }

    free(temp);

    return 0;
}

int main(void)
{
    char str[] = "GeeksforGeeks";
    size_t d = 2;

    if (left_rotate(str, sizeof(str), d) != 0) {
        fprintf(stderr, "Rotation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", str) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}