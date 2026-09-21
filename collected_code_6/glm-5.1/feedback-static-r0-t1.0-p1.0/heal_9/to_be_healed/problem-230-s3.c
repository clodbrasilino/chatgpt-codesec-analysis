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
    size_t input_len = strnlen(input, buffer_size);
    if (input_len >= buffer_size) {
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, input_len + 1);
    printf("Original: %s\n", buffer);
    replace_spaces(buffer, '-');
    printf("Modified: %s\n", buffer);
    return 0;
}