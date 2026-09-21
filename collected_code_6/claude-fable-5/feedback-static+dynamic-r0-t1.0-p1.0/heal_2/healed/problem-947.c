#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

size_t shortest_word_length(const char *str)
{
    size_t min_len = 0;
    size_t current_len = 0;
    int found = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            current_len++;
        } else {
            if (current_len > 0) {
                if (!found || current_len < min_len) {
                    min_len = current_len;
                    found = 1;
                }
                current_len = 0;
            }
        }
    }

    if (current_len > 0) {
        if (!found || current_len < min_len) {
            min_len = current_len;
        }
    }

    return min_len;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;
    size_t result;

    printf("Enter a sentence: ");

    read_len = getline(&buffer, &buffer_size, stdin);
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (read_len > 0 && buffer[read_len - 1] == '\n') {
        buffer[read_len - 1] = '\0';
    }

    result = shortest_word_length(buffer);

    if (result == 0) {
        printf("No words found in input\n");
    } else {
        printf("Length of shortest word: %zu\n", result);
    }

    free(buffer);
    return EXIT_SUCCESS;
}