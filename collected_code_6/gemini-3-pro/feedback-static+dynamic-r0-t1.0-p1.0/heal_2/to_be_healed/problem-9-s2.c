#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

int find_min_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    char *temp = (char *)malloc(2 * len + 1);
    if (temp == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, len);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp + len, str, len);
    temp[2 * len] = '\0';

    int min_rotations = (int)len;
    for (size_t i = 1; i <= len; i++) {
        if (strncmp(str, temp + i, len) == 0) {
            min_rotations = (int)i;
            break;
        }
    }

    free(temp);
    return min_rotations;
}

int main(void) {
    const char *test_str = "abcabc";
    int rotations = find_min_rotations(test_str);
    
    if (rotations != -1) {
        printf("%d\n", rotations);
    } else {
        printf("Error processing string.\n");
    }

    return 0;
}