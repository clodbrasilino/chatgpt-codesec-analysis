#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdbool.h>

#define INPUT_SIZE 256
#define SUCCESS 0
#define ERR_NULL -1
#define ERR_NOT_FOUND -2

int find_first_max_even_word(const char *str, size_t *start, size_t *length)
{
    size_t i = 0;
    size_t word_start = 0;
    size_t word_len = 0;
    size_t max_start = 0;
    size_t max_len = 0;
    bool in_word = false;
    bool found = false;

    if (str == NULL || start == NULL || length == NULL) {
        return ERR_NULL;
    }

    for (;;) {
        unsigned char c = (unsigned char)str[i];

        if (c != '\0' && !isspace(c)) {
            if (!in_word) {
                word_start = i;
                in_word = true;
            }
            word_len++;
        } else {
            if (in_word) {
                if (word_len % 2 == 0 && word_len > max_len) {
                    max_len = word_len;
                    max_start = word_start;
                    found = true;
                }
                in_word = false;
                word_len = 0;
            }
            if (c == '\0') {
                break;
            }
        }
        i++;
    }

    if (!found) {
        return ERR_NOT_FOUND;
    }

    *start = max_start;
    *length = max_len;
    return SUCCESS;
}

int main(void)
{
    char buffer[INPUT_SIZE];
    size_t start = 0;
    size_t length = 0;
    int status;

    printf("Enter a sentence: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    status = find_first_max_even_word(buffer, &start, &length);

    if (status == SUCCESS) {
        printf("First maximum length even word: %.*s\n", (int)length, buffer + start);
        printf("Word length: %zu\n", length);
    } else if (status == ERR_NOT_FOUND) {
        printf("No even-length word found in the input.\n");
    } else {
        fprintf(stderr, "Invalid input provided.\n");
        return 1;
    }

    return 0;
}