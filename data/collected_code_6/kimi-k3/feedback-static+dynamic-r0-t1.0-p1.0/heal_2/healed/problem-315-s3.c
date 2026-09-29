#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int find_first_max_even_word_length(const char *str) {
    int max_len = 0;
    int curr_len = 0;
    int in_word = 0;
    const char *p = str;

    if (str == NULL) {
        return 0;
    }

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
            in_word = 1;
            curr_len++;
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
    size_t buffer_size = 0;
    ssize_t read_len;

    printf("Enter a string: ");
    
    read_len = getline(&input, &buffer_size, stdin);
    
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (read_len > 0 && input[read_len - 1] == '\n') {
        input[read_len - 1] = '\0';
    }

    int result = find_first_max_even_word_length(input);
    printf("Maximum length of even word: %d\n", result);

    free(input);
    return EXIT_SUCCESS;
}