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

int main(int argc, char *const argv[])
{
    if (argc < 2) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <text>\n", program);
        return EXIT_FAILURE;
    }

    size_t argument_count = (size_t)argc - 1;
    size_t payload_length = 0;

    for (size_t i = 0; i < argument_count; ++i) {
        if (argv[i + 1] == NULL) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }

        size_t length = strlen(argv[i + 1]);

        if (length > SIZE_MAX - payload_length) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        payload_length += length;
    }

    size_t separator_count = argument_count - 1;

    if (separator_count > SIZE_MAX - payload_length ||
        payload_length + separator_count == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    size_t total_length = payload_length + separator_count + 1;
    char *text = malloc(total_length);

    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    char *destination = text;
    size_t remaining = total_length;

    for (size_t i = 0; i < argument_count; ++i) {
        size_t length = strlen(argv[i + 1]);

        if (length >= remaining) {
            fprintf(stderr, "Invalid input size\n");
            free(text);
            return EXIT_FAILURE;
        }

        if (length != 0) {
            memcpy(destination, argv[i + 1], length);
            destination += length;
            remaining -= length;
        }

        if (i + 1 < argument_count) {
            if (remaining <= 1) {
                fprintf(stderr, "Invalid input size\n");
                free(text);
                return EXIT_FAILURE;
            }

            *destination++ = ' ';
            --remaining;
        }
    }

    *destination = '\0';

    int result = find_five_letter_words(text);
    free(text);
    return result;
}