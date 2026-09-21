#include <stdio.h>
#include <string.h>

void remove_spaces(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src != ' ') {
            *dst = *src;
            dst++;
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
        size_t len = strcspn(input, "\n");
        if (len > 0 && len < sizeof(input) - 1) {
            input[len] = '\0';
            remove_spaces(input);
            printf("String after removing spaces: %s\n", input);
        } else if (len == 0) {
            printf("Input is empty.\n");
        } else {
            printf("Input too long.\n");
        }
    } else {
        perror("Input error");
    }
    return 0;
}