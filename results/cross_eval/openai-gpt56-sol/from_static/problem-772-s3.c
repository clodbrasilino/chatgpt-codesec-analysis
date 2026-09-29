#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int remove_words_of_length(char *string, size_t k)
{
    char *read_ptr;
    char *write_ptr;
    int pending_space = 0;
    int written_word = 0;

    if (string == NULL) {
        return -1;
    }

    read_ptr = string;
    write_ptr = string;

    while (*read_ptr != '\0') {
        const char *word_start;
        size_t word_length;

        while (*read_ptr != '\0' &&
               isspace((unsigned char)*read_ptr) != 0) {
            pending_space = written_word;
            ++read_ptr;
        }

        word_start = read_ptr;

        while (*read_ptr != '\0' &&
               isspace((unsigned char)*read_ptr) == 0) {
            ++read_ptr;
        }

        word_length = (size_t)(read_ptr - word_start);

        if (word_length != 0U && word_length != k) {
            if (pending_space != 0) {
                *write_ptr++ = ' ';
            }

            while (word_start < read_ptr) {
                *write_ptr++ = *word_start++;
            }

            written_word = 1;
            pending_space = 0;
        }
    }

    *write_ptr = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    char *end_ptr;
    unsigned long parsed_length;
    size_t k;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <k> <string>\n",
                (argc > 0 && argv[0] != NULL) ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    end_ptr = NULL;
    parsed_length = strtoul(argv[1], &end_ptr, 10);

    if (errno == ERANGE ||
        end_ptr == argv[1] ||
        end_ptr == NULL ||
        *end_ptr != '\0' ||
        argv[1][0] == '-' ||
        parsed_length > SIZE_MAX) {
        fprintf(stderr, "Invalid word length\n");
        return EXIT_FAILURE;
    }

    k = (size_t)parsed_length;

    if (remove_words_of_length(argv[2], k) != 0) {
        fprintf(stderr, "Failed to process the string\n");
        return EXIT_FAILURE;
    }

    puts(argv[2]);
    return EXIT_SUCCESS;
}