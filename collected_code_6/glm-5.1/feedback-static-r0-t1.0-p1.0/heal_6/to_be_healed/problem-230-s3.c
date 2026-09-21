#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char c) {
    if (str == NULL) {
        return;
    }
    while (*str != '\0') {
        if (*str == ' ') {
            *str = c;
        }
        str++;
    }
}

int main(int argc, char *argv[]) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    const char *input = "Replace blank spaces with any character";
    size_t buffer_size = sizeof(buffer);
    if (strnlen(input, buffer_size) >= buffer_size) {
        return 1;
    }
    snprintf(buffer, buffer_size, "%s", input);
    printf("Original: %s\n", buffer);
    replace_spaces(buffer, '-');
    printf("Modified: %s\n", buffer);
    return 0;
}