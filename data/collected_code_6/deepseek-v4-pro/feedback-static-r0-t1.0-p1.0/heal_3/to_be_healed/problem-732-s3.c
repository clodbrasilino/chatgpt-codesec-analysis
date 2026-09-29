#include <stdio.h>
#include <string.h>

void replace_chars(char *str, size_t max_len) {
    if (str == NULL) {
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
    char text[100] = "Hello, world. This is a test";

    printf("Original: %s\n", text);
    replace_chars(text, sizeof(text));
    printf("Modified: %s\n", text);

    return 0;
}