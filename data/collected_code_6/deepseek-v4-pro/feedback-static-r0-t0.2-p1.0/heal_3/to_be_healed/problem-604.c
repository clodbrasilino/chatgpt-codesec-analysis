#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void reverse_range(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char *reverse_words(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return str;
    }

    reverse_range(str, str + len - 1);

    char *word_start = str;
    char *p = str;

    while (*p != '\0') {
        if (*p == ' ') {
            reverse_range(word_start, p - 1);
            word_start = p + 1;
        }
        p++;
    }

    reverse_range(word_start, p - 1);

    return str;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 256;
    size_t input_len;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    /* Possible weaknesses found:
     *  The scope of the variable 'overflow_detected' can be reduced. [variableScope]
     *  Variable 'overflow_detected' is assigned a value that is never used. [unreadVariable]
     */
    int overflow_detected = 0;

    input = (char *)malloc(buffer_size);
    if (input == NULL) {
        return 1;
    }

    printf("Enter a string: ");
    if (fgets(input, (int)buffer_size, stdin) == NULL) {
        free(input);
        return 1;
    }

    input_len = strnlen(input, buffer_size);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
    } else {
        overflow_detected = 1;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            /* Possible weaknesses found:
             *  Condition 'c!='\n'' is always true [knownConditionTrueFalse]
             */
            if (overflow_detected && c != '\n' && c != EOF) {
                overflow_detected = 2;
            }
        }
        if (overflow_detected == 2) {
            fprintf(stderr, "Input too long, truncation occurred.\n");
        }
        if (input_len == buffer_size - 1 && input[buffer_size - 2] != '\n') {
            input[buffer_size - 1] = '\0';
        }
    }

    reverse_words(input);

    printf("Reversed words: %s\n", input);

    free(input);
    return 0;
}