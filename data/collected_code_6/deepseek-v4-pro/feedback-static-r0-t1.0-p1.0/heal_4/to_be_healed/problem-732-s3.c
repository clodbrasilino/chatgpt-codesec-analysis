#include <stdio.h>
#include <string.h>

void replace_chars(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }

    for (size_t i = 0; i < max_len - 1 && str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
    str[max_len - 1] = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char text[100];

    if (sizeof(text) > 0) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
         */
        strncpy(text, "Hello, world. This is a test", sizeof(text) - 1);
        text[sizeof(text) - 1] = '\0';
    }

    printf("Original: %s\n", text);
    replace_chars(text, sizeof(text));
    printf("Modified: %s\n", text);

    return 0;
}