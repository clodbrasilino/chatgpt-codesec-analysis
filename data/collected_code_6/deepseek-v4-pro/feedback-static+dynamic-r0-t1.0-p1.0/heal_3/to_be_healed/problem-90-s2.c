#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STRING 1024

int longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;
    int in_word = 0;

    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            if (!in_word) {
                in_word = 1;
                current_length = 1;
            } else {
                current_length++;
            }
        } else {
            if (in_word) {
                if (current_length > max_length) {
                    max_length = current_length;
                }
                in_word = 0;
                current_length = 0;
            }
        }
        str++;
    }

    if (in_word && current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_STRING];
    int c;
    size_t i = 0;

    printf("Enter a string: ");

    while (i < sizeof(input) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        input[i++] = (char)c;
    }
    input[i] = '\0';

    if (c != '\n' && c != EOF) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }

    if (i == 0 && c == EOF) {
        printf("Error reading input.\n");
        return 1;
    }

    int result = longest_word_length(input);
    printf("Longest word length: %d\n", result);

    return 0;
}