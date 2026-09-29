#include <stdio.h>
#include <string.h>

void remove_spaces(char *str, size_t len) {
    char *src = str, *dst = str;
    while (src - str < len && *src != '\0') {
        if (*src != ' ') {
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
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        size_t len = strnlen(input, sizeof(input));
        if (len > 0 && len < sizeof(input)) {
            remove_spaces(input, len);
            printf("String after removing spaces: %s\n", input);
        } else {
            fprintf(stderr, "Input is too long or empty.\n");
        }
    } else {
        perror("Input error");
    }
    return 0;
}