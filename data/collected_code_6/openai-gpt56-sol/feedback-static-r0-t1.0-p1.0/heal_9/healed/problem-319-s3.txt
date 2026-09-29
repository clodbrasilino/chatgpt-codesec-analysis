#include <stdint.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_regex_error(int status, const regex_t *regex,
                              const char *message)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *buffer;

    if (size == 0) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    buffer = malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    (void)regerror(status, regex, buffer, size);
    fprintf(stderr, "%s: %s\n", message, buffer);
    free(buffer);
}

static int find_five_letter_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:alpha:]]{5})([^[:alpha:]]|$)";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        print_regex_error(status, NULL, "Regex compilation failed");
        return EXIT_FAILURE;
    }

    while (*cursor != '\0') {
        size_t remaining = strlen(cursor);

        status = regexec(&regex, cursor, 4, matches, 0);
        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            print_regex_error(status, &regex, "Regex matching failed");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (matches[2].rm_so < 0 ||
            matches[2].rm_eo < matches[2].rm_so ||
            (uintmax_t)matches[2].rm_eo > (uintmax_t)remaining) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        {
            size_t start = (size_t)matches[2].rm_so;
            size_t end = (size_t)matches[2].rm_eo;
            size_t length = end - start;

            if (fwrite(cursor + start, 1, length, stdout) != length ||
                fputc('\n', stdout) == EOF) {
                fprintf(stderr, "Output failed\n");
                regfree(&regex);
                return EXIT_FAILURE;
            }

            cursor += end;
        }
    }

    regfree(&regex);

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Output failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    size_t total_length = 0;
    size_t position = 0;
    size_t *lengths;
    char *text;
    int result;

    if (argc < 2 || argv == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <text>\n", program);
        return EXIT_FAILURE;
    }

    if ((size_t)(argc - 1) > SIZE_MAX / sizeof(*lengths)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    lengths = malloc((size_t)(argc - 1) * sizeof(*lengths));
    if (lengths == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        size_t length;

        if (argv[i] == NULL) {
            fprintf(stderr, "Invalid input\n");
            free(lengths);
            return EXIT_FAILURE;
        }

        length = strlen(argv[i]);
        lengths[i - 1] = length;

        if (length > SIZE_MAX - total_length) {
            fprintf(stderr, "Input is too large\n");
            free(lengths);
            return EXIT_FAILURE;
        }

        total_length += length;

        if (i + 1 < argc) {
            if (total_length == SIZE_MAX) {
                fprintf(stderr, "Input is too large\n");
                free(lengths);
                return EXIT_FAILURE;
            }
            ++total_length;
        }
    }

    if (total_length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        free(lengths);
        return EXIT_FAILURE;
    }

    text = malloc(total_length + 1);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(lengths);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        size_t length = lengths[i - 1];

        if (length > total_length - position) {
            fprintf(stderr, "Invalid input size\n");
            free(text);
            free(lengths);
            return EXIT_FAILURE;
        }

        if (length != 0) {
            memcpy(text + position, argv[i], length);
            position += length;
        }

        if (i + 1 < argc) {
            if (position >= total_length) {
                fprintf(stderr, "Invalid input size\n");
                free(text);
                free(lengths);
                return EXIT_FAILURE;
            }
            text[position++] = ' ';
        }
    }

    if (position != total_length) {
        fprintf(stderr, "Invalid input size\n");
        free(text);
        free(lengths);
        return EXIT_FAILURE;
    }

    text[position] = '\0';
    free(lengths);

    result = find_five_letter_words(text);
    free(text);

    return result;
}