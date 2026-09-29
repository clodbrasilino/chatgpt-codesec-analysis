#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    if (len == 0) {
        return;
    }

    n = n % len;
    if (n == 0) {
        return;
    }

    char *temp = malloc(n + 1);
    if (temp == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, n);
    temp[n] = '\0';
    memmove(str, str + n, len - n + 1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + len - n, temp, n);
    str[len] = '\0';

    free(temp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[100];

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(buffer, "abcdef", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    left_rotate_string(buffer, 2);
    printf("%s\n", buffer);

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(buffer, "hello", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    left_rotate_string(buffer, 7);
    printf("%s\n", buffer);

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(buffer, "test", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    left_rotate_string(buffer, 0);
    printf("%s\n", buffer);

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strncpy(buffer, "", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    left_rotate_string(buffer, 3);
    printf("%s\n", buffer);

    return 0;
}