#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, int n) {
    if (str == NULL || str[0] == '\0' || n <= 0) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    n = (int)((size_t)n % len);
    if (n == 0) {
        return;
    }

    char *temp = malloc((size_t)n + 1);
    if (temp == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, (size_t)n);
    temp[n] = '\0';

    memmove(str, str + n, len - (size_t)n + 1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + len - (size_t)n, temp, (size_t)n);

    free(temp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[100] = {0};

    snprintf(buffer, sizeof(buffer), "%s", "abcdef");
    left_rotate_string(buffer, 2);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%s", "hello");
    left_rotate_string(buffer, 7);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%s", "test");
    left_rotate_string(buffer, 0);
    printf("%s\n", buffer);

    buffer[0] = '\0';
    left_rotate_string(buffer, 3);
    printf("%s\n", buffer);

    return 0;
}