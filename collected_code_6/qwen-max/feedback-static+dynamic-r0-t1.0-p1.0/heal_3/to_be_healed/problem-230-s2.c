#include <stdio.h>
#include <string.h>

void replace_spaces_with_char(char *str, char replacement, size_t max_len) {
    if (str == NULL) return;
    for (size_t i = 0; i < max_len && str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100] = "This is a test string";
    char replacement = '*';
    replace_spaces_with_char(input, replacement, sizeof(input));
    printf("%s\n", input);
    return 0;
}