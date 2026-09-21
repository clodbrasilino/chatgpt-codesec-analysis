#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int find_first_max_even_word_length(const char *str) {
    int max_len = 0;
    int curr_len = 0;
    int in_word = 0;
    const char *p;

    if (str == NULL) {
        return 0;
    }

    p = str;
    while (*p != '\0') {
        if (isspace((unsigned char)*p)) {
            if (in_word) {
                if (curr_len % 2 == 0 && curr_len > max_len) {
                    max_len = curr_len;
                }
                in_word = 0;
                curr_len = 0;
            }
        } else {
            if (curr_len < INT_MAX) {
                curr_len++;
            }
            in_word = 1;
        }
        p++;
    }

    if (in_word && curr_len % 2 == 0 && curr_len > max_len) {
        max_len = curr_len;
    }

    return max_len;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t len;
    int result;

    printf("Enter a string: ");
    
    len = getline(&input, &input_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    }

    result = find_first_max_even_word_length(input);
    printf("Maximum length of even word: %d\n", result);

    free(input);
    return EXIT_SUCCESS;
}