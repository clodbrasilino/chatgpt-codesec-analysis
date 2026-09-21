#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

#define MAX_STRING 1024

int longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;
    int in_word = 0;
    size_t pos = 0;

    while (pos < MAX_STRING && str[pos] != '\0') {
        if (isalpha((unsigned char)str[pos])) {
            if (!in_word) {
                in_word = 1;
                current_length = 1;
            } else {
                current_length++;
            }
            if (current_length > max_length) {
                max_length = current_length;
            }
        } else {
            if (in_word) {
                in_word = 0;
                current_length = 0;
            }
        }
        pos++;
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
        if (c == EOF) {
            if (ferror(stdin)) {
                printf("Error reading input.\n");
                return 1;
            }
            break;
        }
        if (c == '\n') {
            break;
        }
        if (i < sizeof(input) - 1) {
            input[i++] = (char)c;
        }
    }
    input[i] = '\0';

    if (i == 0 && c == EOF && ferror(stdin)) {
        printf("Error reading input.\n");
        return 1;
    }

    if (c != '\n' && c != EOF) {
        int discard;
        size_t discard_count = 0;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((discard = getchar()) != '\n' && discard != EOF) {
            if (discard == EOF && ferror(stdin)) {
                printf("Error reading input.\n");
                return 1;
            }
            discard_count++;
            if (discard_count > MAX_STRING) {
                break;
            }
        }
    }

    int result = longest_word_length(input);
    printf("Longest word length: %d\n", result);

    return 0;
}