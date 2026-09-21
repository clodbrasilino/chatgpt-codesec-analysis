#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int status, const regex_t *regex, const char *operation)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *message = malloc(size);

    if (message == NULL) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    regerror(status, regex, message, size);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
}

static int find_five_character_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alnum:]_])([[:alpha:]]{5})($|[^[:alnum:]_])";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor;
    int status;

    if (text == NULL) {
        return 1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, &regex, "regcomp");
        return 1;
    }

    cursor = text;

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, sizeof(matches) / sizeof(matches[0]),
                         matches, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "regexec");
            regfree(&regex);
            return 1;
        }

        if (matches[2].rm_so < 0 ||
            matches[2].rm_eo < matches[2].rm_so ||
            matches[0].rm_eo <= 0) {
            regfree(&regex);
            return 1;
        }

        if (fwrite(cursor + matches[2].rm_so, 1,
                   (size_t)(matches[2].rm_eo - matches[2].rm_so),
                   stdout) != (size_t)(matches[2].rm_eo - matches[2].rm_so) ||
            fputc('\n', stdout) == EOF) {
            regfree(&regex);
            return 1;
        }

        cursor += matches[2].rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[])
{
    size_t total_length = 1;
    size_t position = 0;
    char *text;
    int result;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        size_t length;

        if (argv[i] == NULL) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }

        length = strlen(argv[i]);

        if (length > SIZE_MAX - total_length) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        total_length += length;

        if (i + 1 < argc) {
            if (total_length == SIZE_MAX) {
                fprintf(stderr, "Input is too large\n");
                return EXIT_FAILURE;
            }
            ++total_length;
        }
    }

    text = malloc(total_length);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        size_t length = strlen(argv[i]);
        size_t remaining = total_length - position;

        if (length >= remaining) {
            free(text);
            fprintf(stderr, "Input size error\n");
            return EXIT_FAILURE;
        }

        memcpy(text + position, argv[i], length);
        position += length;

        if (i + 1 < argc) {
            if (position + 1 >= total_length) {
                free(text);
                fprintf(stderr, "Input size error\n");
                return EXIT_FAILURE;
            }
            text[position++] = ' ';
        }
    }

    text[position] = '\0';
    result = find_five_character_words(text);
    free(text);

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}