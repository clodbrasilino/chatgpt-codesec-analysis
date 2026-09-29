#include <regex.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *operation)
{
    size_t size;
    char *message;

    size = regerror(status, regex, NULL, 0);
    if (size == 0) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    message = malloc(size);
    if (message == NULL) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    (void)regerror(status, regex, message, size);
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
        status = regexec(&regex, cursor,
                         sizeof(matches) / sizeof(matches[0]),
                         matches, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "regexec");
            regfree(&regex);
            return 1;
        }

        if (matches[0].rm_so < 0 ||
            matches[0].rm_eo <= matches[0].rm_so ||
            matches[2].rm_so < 0 ||
            matches[2].rm_eo <= matches[2].rm_so ||
            matches[2].rm_so < matches[0].rm_so ||
            matches[2].rm_eo > matches[0].rm_eo) {
            regfree(&regex);
            return 1;
        }

        {
            size_t word_length =
                (size_t)(matches[2].rm_eo - matches[2].rm_so);

            if (fwrite(cursor + matches[2].rm_so, 1, word_length, stdout) !=
                    word_length ||
                fputc('\n', stdout) == EOF) {
                regfree(&regex);
                return 1;
            }
        }

        cursor += matches[2].rm_eo;
    }

    regfree(&regex);
    return 0;
}

static int build_text(int argc, char *argv[], char **output)
{
    size_t total_length = 1;
    size_t position = 0;
    char *text;

    if (output == NULL) {
        return 1;
    }

    *output = NULL;

    if (argc < 2 || argv == NULL) {
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        size_t length;

        if (argv[i] == NULL) {
            return 1;
        }

        length = strlen(argv[i]);

        if (length > SIZE_MAX - total_length) {
            return 1;
        }

        total_length += length;

        if (i < argc - 1) {
            if (total_length == SIZE_MAX) {
                return 1;
            }
            ++total_length;
        }
    }

    text = malloc(total_length);
    if (text == NULL) {
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        size_t available = total_length - position;
        int written;

        if (available == 0) {
            free(text);
            return 1;
        }

        written = snprintf(text + position, available, "%s%s",
                           argv[i], i < argc - 1 ? " " : "");

        if (written < 0 || (size_t)written >= available) {
            free(text);
            return 1;
        }

        position += (size_t)written;
    }

    if (position != total_length - 1) {
        free(text);
        return 1;
    }

    *output = text;
    return 0;
}

int main(int argc, char *argv[])
{
    char *text;
    int result;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    if (build_text(argc, argv, &text) != 0) {
        fprintf(stderr, "Unable to process input\n");
        return EXIT_FAILURE;
    }

    result = find_five_character_words(text);
    free(text);

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}