#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int left_rotate(char *str, size_t d)
{
    size_t len;
    char *temp;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0) {
        return 0;
    }

    d = d % len;
    if (d == 0) {
        return 0;
    }

    temp = malloc(len + 1);
    if (temp == NULL) {
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

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, temp, len + 1);
    free(temp);

    return 0;
}

int main(void)
{
    char str[] = "GeeksforGeeks";
    size_t d = 2;

    if (left_rotate(str, d) != 0) {
        fprintf(stderr, "Rotation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", str) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}