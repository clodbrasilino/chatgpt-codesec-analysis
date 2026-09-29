#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *replace_spaces(char *str, char replacement) {
    if (str == NULL) {
        return NULL;
    }

    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
        i++;
    }
    return str;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[512];
    char replacement;
    char *result;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    printf("Enter replacement character: ");
    if (scanf(" %c", &replacement) != 1) {
        fprintf(stderr, "Error reading character\n");
        return 1;
    }

    result = replace_spaces(input, replacement);
    if (result == NULL) {
        fprintf(stderr, "Invalid input string\n");
        return 1;
    }

    printf("Modified string: %s\n", result);
    return 0;
}