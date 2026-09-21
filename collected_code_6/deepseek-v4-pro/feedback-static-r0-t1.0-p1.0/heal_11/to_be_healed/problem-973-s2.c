#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, size_t size, int n) {
    if (str == NULL || size == 0 || n <= 0) {
        return;
    }

    size_t len = strnlen(str, size);
    if (len == 0 || len >= size) {
        return;
    }

    n = (int)((size_t)n % len);
    if (n == 0) {
        return;
    }

    /* Possible weaknesses found:
     *  If condition '(unsigned long)n>size-1' is true, the function will return/exit
     */
    if ((size_t)n > size - 1) {
        return;
    }

    char *temp = malloc((size_t)n + 1);
    if (temp == NULL) {
        return;
    }

    /* Possible weaknesses found:
     *  Testing identical condition '(unsigned long)n>size-1'
     *  Identical condition '(unsigned long)n>size-1', second condition is always false [identicalConditionAfterEarlyExit]
     */
    if ((size_t)n > len || (size_t)n > size - 1) {
        free(temp);
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, (size_t)n);
    temp[n] = '\0';

    size_t remaining = len - (size_t)n;
    if (remaining >= size) {
        free(temp);
        return;
    }

    size_t move_size = remaining + 1;
    if (move_size > size) {
        free(temp);
        return;
    }

    memmove(str, str + n, move_size);

    if ((size_t)n > size - remaining) {
        free(temp);
        return;
    }

    if (remaining + (size_t)n <= size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str + remaining, temp, (size_t)n);
    }
    free(temp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[100] = {0};

    if (sizeof(buffer) > 0) {
        snprintf(buffer, sizeof(buffer), "abcdef");
        left_rotate_string(buffer, sizeof(buffer), 2);
        printf("%s\n", buffer);

        snprintf(buffer, sizeof(buffer), "hello");
        left_rotate_string(buffer, sizeof(buffer), 7);
        printf("%s\n", buffer);

        snprintf(buffer, sizeof(buffer), "test");
        left_rotate_string(buffer, sizeof(buffer), 0);
        printf("%s\n", buffer);

        buffer[0] = '\0';
        left_rotate_string(buffer, sizeof(buffer), 3);
        printf("%s\n", buffer);
    }

    return 0;
}