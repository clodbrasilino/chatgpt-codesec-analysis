#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }

    size_t len = strnlen(str, 100);
    if (len == 0 || len >= 100) {
        return;
    }

    n = n % (int)len;
    if (n == 0) {
        return;
    }

    char *temp = malloc(n + 1);
    if (temp == NULL) {
        return;
    }

    if (n <= (int)len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str, n);
    }
    temp[n] = '\0';
    
    memmove(str, str + n, len - n + 1);
    
    if (n <= (int)len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str + len - n, temp, n);
    }
    str[len] = '\0';

    free(temp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[100];

    snprintf(buffer, sizeof(buffer), "%s", "abcdef");
    left_rotate_string(buffer, 2);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%s", "hello");
    left_rotate_string(buffer, 7);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%s", "test");
    left_rotate_string(buffer, 0);
    printf("%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%s", "");
    left_rotate_string(buffer, 3);
    printf("%s\n", buffer);

    return 0;
}