#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

bool are_rotations(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t temp_size;
    char *temp;
    bool result;

    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    len1 = strnlen(s1, MAX_INPUT_LEN);
    len2 = strnlen(s2, MAX_INPUT_LEN);

    if (len1 >= MAX_INPUT_LEN || len2 >= MAX_INPUT_LEN) {
        return false;
    }

    if (len1 != len2) {
        return false;
    }

    if (len1 == 0) {
        return true;
    }

    if (len1 > (SIZE_MAX - 1) / 2) {
        return false;
    }

    temp_size = (2 * len1) + 1;

    temp = malloc(temp_size);
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    if (len1 > temp_size - 1 || len1 > temp_size - 1 - len1) {
        free(temp);
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, s1, len1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp + len1, s1, len1);
    temp[temp_size - 1] = '\0';

    result = (strstr(temp, s2) != NULL);

    free(temp);
    return result;
}

static void strip_newline(char *s)
{
    size_t len;

    if (s == NULL) {
        return;
    }

    len = strnlen(s, MAX_INPUT_LEN);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf1[MAX_INPUT_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf2[MAX_INPUT_LEN];

    while (fgets(buf1, sizeof(buf1), stdin) != NULL &&
           fgets(buf2, sizeof(buf2), stdin) != NULL) {
        strip_newline(buf1);
        strip_newline(buf2);

        if (are_rotations(buf1, buf2)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
        fflush(stdout);
    }

    return EXIT_SUCCESS;
}