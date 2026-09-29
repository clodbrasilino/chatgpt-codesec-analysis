#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'adooph', got <no output>
  *  test case 0 failed: expected 'thonpy', got <no output>
  *  test case 1 failed: expected 'databig', got <no output>
  */

char *left_rotate(const char *str, size_t d)
{
    size_t len;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN && str[len] != '\0') {
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (len == 0) {
        result[0] = '\0';
        return result;
    }

    d = d % len;

    if (d > len || (len - d) > len) {
        free(result);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, str + d, len - d);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + (len - d), str, d);
    result[len] = '\0';

    return result;
}

int main(void)
{
    const char *original = "HelloWorld";
    size_t shift = 3;
    char *rotated;

    rotated = left_rotate(original, shift);
    if (rotated == NULL) {
        fprintf(stderr, "Error: rotation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", original) < 0) {
        free(rotated);
        return EXIT_FAILURE;
    }

    if (printf("Rotated:  %s\n", rotated) < 0) {
        free(rotated);
        return EXIT_FAILURE;
    }

    free(rotated);
    return EXIT_SUCCESS;
}