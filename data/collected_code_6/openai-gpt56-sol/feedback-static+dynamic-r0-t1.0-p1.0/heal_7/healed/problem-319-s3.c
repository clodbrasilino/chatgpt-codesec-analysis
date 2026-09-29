#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *message)
{
    size_t size = regerror(status, regex, NULL, 0);

    if (size == 0) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    char *buffer = malloc(size);
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
    const char *cursor = text;
    int status = regcomp(&regex, pattern, REG_EXTENDED);

    if (status != 0) {
        report_regex_error(status, NULL, "Regex compilation failed");
        return EXIT_FAILURE;
    }

    while (*cursor != '\0') {
        status = regexec(&regex, cursor,
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

    regfree(&regex);
    return EXIT_SUCCESS;
}

static int get_argument_length(const char *argument, size_t *length)
{
    if (argument == NULL || length == NULL) {
        return 0;
    }

    *length = strlen(argument);
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argv == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <text>\n", program);
        return EXIT_FAILURE;
    }

    size_t argument_count = (size_t)argc - 1;
    size_t payload_length = 0;

    if (argument_count > SIZE_MAX / sizeof(size_t)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    size_t *lengths = malloc(argument_count * sizeof(*lengths));
    if (lengths == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < argument_count; ++i) {
        if (!get_argument_length(argv[i + 1], &lengths[i])) {
            fprintf(stderr, "Invalid input\n");
            free(lengths);
            return EXIT_FAILURE;
        }

        if (lengths[i] > SIZE_MAX - payload_length) {
            fprintf(stderr, "Input is too large\n");
            free(lengths);
            return EXIT_FAILURE;
        }

        payload_length += lengths[i];
    }

    size_t separator_count = argument_count - 1;

    if (separator_count > SIZE_MAX - payload_length) {
        fprintf(stderr, "Input is too large\n");
        free(lengths);
        return EXIT_FAILURE;
    }

    size_t content_length = payload_length + separator_count;

    if (content_length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        free(lengths);
        return EXIT_FAILURE;
    }

    size_t total_length = content_length + 1;
    char *text = malloc(total_length);

    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(lengths);
        return EXIT_FAILURE;
    }

    size_t offset = 0;

    for (size_t i = 0; i < argument_count; ++i) {
        size_t length = lengths[i];

        if (offset > content_length || length > content_length - offset) {
            fprintf(stderr, "Invalid input size\n");
            free(text);
            free(lengths);
            return EXIT_FAILURE;
        }

        if (length > 0) {
            memcpy(text + offset, argv[i + 1], length);
            offset += length;
        }

        if (i + 1 < argument_count) {
            if (offset >= content_length) {
                fprintf(stderr, "Invalid input size\n");
                free(text);
                free(lengths);
                return EXIT_FAILURE;
            }

            text[offset++] = ' ';
        }
    }

    if (offset != content_length) {
        fprintf(stderr, "Invalid input size\n");
        free(text);
        free(lengths);
        return EXIT_FAILURE;
    }

    text[offset] = '\0';
    free(lengths);

    int result = find_five_letter_words(text);
    free(text);
    return result;
}