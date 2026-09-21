#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_chars(char *str1, size_t str1_len, const char *str2) {
    char *src, *dst;
    for (src = dst = str1; src - str1 < str1_len; ++src) {
        if (strchr(str2, *src) == NULL) {
            if (dst - str1 < str1_len) {
                *dst++ = *src;
            }
        }
    }
    if (dst - str1 < str1_len) {
        *dst = '\0';
    } else {
        str1[str1_len - 1] = '\0';
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[100] = "Hello, World!";
    const char *str2 = ",!";
    size_t str1_len = sizeof(str1) / sizeof(str1[0]) - 1;

    remove_chars(str1, str1_len, str2);
    printf("%s\n", str1);

    return 0;
}