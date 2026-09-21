#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void report_regex_error(const char *operation, int status,
                               const regex_t *regex)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *message = malloc(size);

    if (message != NULL) {
        regerror(status, regex, message, size);
        fprintf(stderr, "%s failed: %s\n", operation, message);
        free(message);
    } else {
        fprintf(stderr, "%s failed\n", operation);
    }
}

static int find_sequences(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int status;

    if (input == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[[:upper:]][[:lower:]]+", REG_EXTENDED);
    if (status != 0) {
        report_regex_error("regcomp", status, &regex);
        return -1;
    }

    cursor = input;

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error("regexec", status, &regex);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regular expression match\n");
            regfree(&regex);
            return -1;
        }

        {
            size_t start = (size_t)match.rm_so;
            size_t length = (size_t)(match.rm_eo - match.rm_so);

            if (fwrite(cursor + start, 1, length, stdout) != length ||
                fputc('\n', stdout) == EOF) {
                perror("output");
                regfree(&regex);
                return -1;
            }
        }

        cursor += (size_t)match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

static int append_argument(char **buffer, size_t *length, size_t *capacity,
                           const char *argument, int add_separator)
{
    const char *source;

    if (buffer == NULL || length == NULL || capacity == NULL ||
        argument == NULL) {
        return -1;
    }

    source = argument;

    for (;;) {
        char character = *source;

        if (character == '\0') {
            break;
        }

        if (*length > SIZE_MAX - 2U) {
            return -1;
        }

        if (*length + 1U >= *capacity) {
            size_t required = *length + 2U;
            size_t new_capacity;
            char *new_buffer;

            if (*capacity > SIZE_MAX / 2U) {
                new_capacity = required;
            } else {
                new_capacity = *capacity * 2U;
                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            new_buffer = realloc(*buffer, new_capacity);
            if (new_buffer == NULL) {
                return -1;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[(*length)++] = character;
        ++source;
    }

    if (add_separator) {
        if (*length > SIZE_MAX - 2U) {
            return -1;
        }

        if (*length + 1U >= *capacity) {
            size_t required = *length + 2U;
            size_t new_capacity;
            char *new_buffer;

            if (*capacity > SIZE_MAX / 2U) {
                new_capacity = required;
            } else {
                new_capacity = *capacity * 2U;
                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            new_buffer = realloc(*buffer, new_capacity);
            if (new_buffer == NULL) {
                return -1;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[(*length)++] = ' ';
    }

    (*buffer)[*length] = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    size_t length = 0;
    size_t capacity = 64U;
    char *input;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input = malloc(capacity);
    if (input == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    input[0] = '\0';

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == NULL) {
            fprintf(stderr, "Invalid argument\n");
            free(input);
            return EXIT_FAILURE;
        }

        if (append_argument(&input, &length, &capacity, argv[i],
                            i + 1 < argc) != 0) {
            fprintf(stderr, "Unable to construct input\n");
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (find_sequences(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}