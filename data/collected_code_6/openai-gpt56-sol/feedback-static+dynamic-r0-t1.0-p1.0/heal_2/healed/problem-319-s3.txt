#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int status, const regex_t *regex,
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

    regerror(status, regex, buffer, size);
    fprintf(stderr, "%s: %s\n", message, buffer);
    free(buffer);
}

static int find_five_letter_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:alpha:]]{5})([^[:alpha:]]|$)";
    regex_t regex;
    regmatch_t matches[4];
    size_t offset = 0;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, NULL, "Regex compilation failed");
        return EXIT_FAILURE;
    }

    while (text[offset] != '\0') {
        status = regexec(&regex, text + offset,
                         sizeof(matches) / sizeof(matches[0]),
                         matches, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "Regex matching failed");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (matches[2].rm_so < 0 ||
            matches[2].rm_eo < matches[2].rm_so) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        {
            size_t start = (size_t)matches[2].rm_so;
            size_t length =
                (size_t)(matches[2].rm_eo - matches[2].rm_so);

            if (fwrite(text + offset + start, 1, length, stdout) != length ||
                fputc('\n', stdout) == EOF) {
                fprintf(stderr, "Output failed\n");
                regfree(&regex);
                return EXIT_FAILURE;
            }
        }

        if (matches[2].rm_eo <= 0) {
            ++offset;
        } else {
            offset += (size_t)matches[2].rm_eo;
        }
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(int argc, char *const argv[])
{
    size_t argument_count;
    size_t total_length = 1;
    size_t position = 0;
    size_t *lengths;
    char *text;
    int result;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    argument_count = (size_t)argc - 1;

    if (argument_count > SIZE_MAX / sizeof(*lengths)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    lengths = malloc(argument_count * sizeof(*lengths));
    if (lengths == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < argument_count; ++i) {
        const char *argument = argv[i + 1];
        size_t length;
        size_t separator = i + 1 < argument_count ? 1 : 0;

        if (argument == NULL) {
            fprintf(stderr, "Invalid input\n");
            free(lengths);
            return EXIT_FAILURE;
        }

        length = strlen(argument);
        lengths[i] = length;

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
    }

    text = malloc(total_length);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(lengths);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < argument_count; ++i) {
        size_t length = lengths[i];

        if (length > total_length - position - 1) {
            fprintf(stderr, "Invalid input size\n");
            free(text);
            free(lengths);
            return EXIT_FAILURE;
        }

        if (length != 0) {
            memcpy(text + position, argv[i + 1], length);
            position += length;
        }

        if (i + 1 < argument_count) {
            if (position >= total_length - 1) {
                fprintf(stderr, "Invalid input size\n");
                free(text);
                free(lengths);
                return EXIT_FAILURE;
            }
            text[position++] = ' ';
        }
    }

    text[position] = '\0';
    free(lengths);

    result = find_five_letter_words(text);
    free(text);

    return result;
}