#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

void remove_words_of_length(char *str, size_t k, size_t str_size)
{
    if (str == NULL || str_size == 0) {
        return;
    }

    size_t read_idx = 0;
    size_t write_idx = 0;
    size_t str_len = strnlen(str, str_size);
    bool last_was_space = true;

    while (read_idx < str_len) {
        while (read_idx < str_len && isspace((unsigned char)str[read_idx])) {
            read_idx++;
        }

        if (read_idx >= str_len) {
            break;
        }

        size_t word_start = read_idx;
        while (read_idx < str_len && !isspace((unsigned char)str[read_idx])) {
            read_idx++;
        }
        size_t word_len = read_idx - word_start;

        if (word_len != k) {
            if (!last_was_space && write_idx < str_size - 1) {
                str[write_idx++] = ' ';
            }
            if (write_idx + word_len < str_size) {
                memmove(&str[write_idx], &str[word_start], word_len);
                write_idx += word_len;
                last_was_space = false;
            } else {
                size_t remaining = str_size - 1 - write_idx;
                if (remaining > 0) {
                    memmove(&str[write_idx], &str[word_start], remaining);
                    write_idx += remaining;
                }
                break;
            }
        }
    }

    str[write_idx] = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t k;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    printf("Enter word length to remove: ");
    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    remove_words_of_length(buffer, k, sizeof(buffer));

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}