#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_chars(char *str1, const char *str2, size_t max_len) {
    char *src = str1;
    char *dst = str1;

    while (*src != '\0' && (dst - str1) < max_len - 1) {
        if (strchr(str2, *src) == NULL) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[100] = "Hello, World!";
    const char *str2 = ",!";

    remove_chars(str1, str2, sizeof(str1));
    printf("%s\n", str1);

    return 0;
}