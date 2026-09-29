#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

int left_rotate(char *str, size_t str_size, size_t d)
{
    size_t len;
    char *temp;

    if (str == NULL || str_size == 0 || str_size > MAX_STR_LEN) {
        return -1;
    }

    len = strnlen(str, str_size);
    if (len >= str_size) {
        return -1;
    }

    if (len == 0) {
        return 0;
    }

    d = d % len;
    if (d == 0) {
        return 0;
    }

    if (d > len || (len - d) > len) {
        return -1;
    }

    if (len + 1 > str_size) {
        return -1;
    }

    temp = malloc(len + 1);
    if (temp == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Assuming condition 'd>len' is false
     *  Assuming condition '(len-d)>len' is false
     */
    if ((len - d) > len || d > len || ((len - d) + d) != len) {
        free(temp);
        return -1;
    }

    /* Possible weaknesses found:
     *  Condition '(len-d)<=len' is always true [knownConditionTrueFalse]
     *  Condition '(len-d)<=len' is always true
     *  Condition 'd<=len' is always true
     *  Condition 'd<=len' is always true [knownConditionTrueFalse]
     */
    if ((len - d) <= len && d <= len && (len + 1) <= str_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str + d, len - d);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp + (len - d), str, d);
        temp[len] = '\0';
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