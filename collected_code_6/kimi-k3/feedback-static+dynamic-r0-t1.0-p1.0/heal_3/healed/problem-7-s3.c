#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int find_words(const char *str) {
    regex_t regex;
    regmatch_t match;
    const char *cursor = str;
    int reti;

    if (str == NULL) {
        fprintf(stderr, "Input string is NULL\n");
        return 1;
    }

    reti = regcomp(&regex, "[a-zA-Z]{4,}", REG_EXTENDED);
    if (reti != 0) {
        char error_buffer[512];
        size_t error_buffer_size = sizeof(error_buffer);
        
        regerror(reti, &regex, error_buffer, error_buffer_size);
        error_buffer[error_buffer_size - 1] = '\0';
        fprintf(stderr, "Could not compile regex: %s\n", error_buffer);
        return 1;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so != -1) {
            size_t word_length = (size_t)(match.rm_eo - match.rm_so);
            if (word_length > 0 && word_length < 1024) {
                printf("%.*s\n", (int)word_length, cursor + match.rm_so);
            }
            cursor += match.rm_eo;
        } else {
            break;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *text = "This is a simple example string to find words which are at least four characters long";
    if (find_words(text) != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}