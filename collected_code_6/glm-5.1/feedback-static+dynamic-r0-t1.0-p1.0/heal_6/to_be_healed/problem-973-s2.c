#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, size_t n) {
    if (str == NULL) {
        return;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return;
    }

    size_t rotations = n % len;
    if (rotations == 0) {
        return;
    }

    char *buffer = (char *)malloc(rotations);
    if (buffer == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, str, rotations);
    memmove(str, str + rotations, len - rotations);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + (len - rotations), buffer, rotations);

    free(buffer);
}

int main(void) {
    char str[] = "HelloWorld";
    int rotate_by = 3;

    printf("Original: %s\n", str);

    left_rotate_string(str, rotate_by);

    printf("Rotated: %s\n", str);

    return 0;
}