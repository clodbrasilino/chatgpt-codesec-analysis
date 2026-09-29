#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

int left_rotate(char *str, size_t buf_size, size_t d)
{
    size_t len;
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

    /* Possible weaknesses found:
     *  Assuming condition 'len-d>len' is false
     */
    if (len + 1 > buf_size || d > len || len - d > len) {
        return -1;
    }

    temp = malloc(len + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Condition '(len-d)>len' is always false
     *  Condition '(len-d)>len' is always false [knownConditionTrueFalse]
     */
    if ((len - d) > len || d > (len - (len - d))) {
        free(temp);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str + d, len - d);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp + (len - d), str, d);
    temp[len] = '\0';

    if (len + 1 > buf_size) {
        free(temp);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, temp, len + 1);
    free(temp);

    return 0;
}

int main(void)
{
    char str[] = "HelloWorld";
    size_t d = 3;

    printf("Original string: %s\n", str);

    if (left_rotate(str, sizeof(str), d) != 0) {
        fprintf(stderr, "Rotation failed\n");
        return EXIT_FAILURE;
    }

    printf("Rotated string:  %s\n", str);

    return EXIT_SUCCESS;
}