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

static int find_five_letter_words(const char *text, size_t text_length)
{
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:alpha:]]{5})([^[:alpha:]]|$)";
    regex_t regex;
    regmatch_t matches[4];
    size_t offset = 0;
    int status;

    if (text == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        print_regex_error(status, NULL, "Regex compilation failed");
        return EXIT_FAILURE;
    }

    while (offset < text_length) {
        size_t remaining = text_length - offset;
        size_t start;
        size_t end;
        size_t length;

        status = regexec(&regex, text + offset, 4, matches, 0);
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
            (uintmax_t)matches[2].rm_so > (uintmax_t)remaining ||
            (uintmax_t)matches[2].rm_eo > (uintmax_t)remaining) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        start = (size_t)matches[2].rm_so;
        end = (size_t)matches[2].rm_eo;
        length = end - start;

        if (length != 0 &&
            fwrite(text + offset + start, 1, length, stdout) != length) {
            fprintf(stderr, "Output failed\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (fputc('\n', stdout) == EOF) {
            fprintf(stderr, "Output failed\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (end == 0) {
            ++offset;
        } else {
            offset += end;
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
    size_t argument_count;
    size_t total_length = 0;
    size_t position = 0;
    size_t *lengths = NULL;
    char *text = NULL;
    int result;

    if (argc < 2 || argv == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <text>\n", program);
        return EXIT_FAILURE;
    }

    argument_count = (size_t)argc - 1;

    if (argument_count > SIZE_MAX / sizeof(*lengths)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    lengths = calloc(argument_count, sizeof(*lengths));
    if (lengths == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < argument_count; ++i) {
        const char *argument = argv[i + 1];
        size_t length;
        size_t separator = i + 1 < argument_count ? 1U : 0U;

        if (argument == NULL) {
            fprintf(stderr, "Invalid input\n");
            free(lengths);
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(argument);

        if (length > SIZE_MAX - total_length) {
            fprintf(stderr, "Input is too large\n");
            free(lengths);
            return EXIT_FAILURE;
        }
        total_length += length;

        if (separator > SIZE_MAX - total_length) {
            fprintf(stderr, "Input is too large\n");
            free(lengths);
            return EXIT_FAILURE;
        }
        total_length += separator;
        lengths[i] = length;
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

    for (size_t i = 0; i < argument_count; ++i) {
        size_t length = lengths[i];

        if (position > total_length ||
            length > total_length - position) {
            fprintf(stderr, "Invalid input size\n");
            free(text);
            free(lengths);
            return EXIT_FAILURE;
        }

        for (size_t j = 0; j < length; ++j) {
            text[position + j] = argv[i + 1][j];
        }
        position += length;

        if (i + 1 < argument_count) {
            if (position >= total_length) {
                fprintf(stderr, "Invalid input size\n");
                free(text);
                free(lengths);
                return EXIT_FAILURE;
            }

            text[position++] = ' ';
        }
    }

    free(lengths);

    if (position != total_length) {
        fprintf(stderr, "Invalid input size\n");
        free(text);
        return EXIT_FAILURE;
    }

    text[position] = '\0';
    result = find_five_letter_words(text, total_length);
    free(text);

    return result;
}