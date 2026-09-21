#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t required = regerror(error_code, regex, NULL, 0);

    if (required == 0) {
        fputs("Unknown regex error\n", stderr);
        return;
    }

    char *message = malloc(required);

    if (message == NULL) {
        fputs("Unable to allocate memory for regex error message\n", stderr);
        return;
    }

    regerror(error_code, regex, message, required);
    fprintf(stderr, "Regex error: %s\n", message);
    free(message);
}

static int get_string_length(const char *text, size_t *length)
{
    size_t count = 0;

    if (text == NULL || length == NULL) {
        return -1;
    }

    while (text[count] != '\0') {
        if (count == SIZE_MAX - 1) {
            return -1;
        }

        ++count;
    }

    *length = count;
    return 0;
}

static int copy_input(const char *source, size_t source_length, char **destination)
{
    char *copy;
    size_t index;

    if (source == NULL || destination == NULL || source_length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(source_length + 1);

    if (copy == NULL) {
        return -1;
    }

    for (index = 0; index < source_length; ++index) {
        copy[index] = source[index];
    }

    copy[source_length] = '\0';
    *destination = copy;
    return 0;
}

int find_sequences(const char *text, size_t text_length)
{
    regex_t regex;
    char *input = NULL;
    const char *cursor;
    size_t remaining;
    int result;
    int status = -1;

    if (text == NULL) {
        fputs("Input is NULL\n", stderr);
        return -1;
    }

    if (text_length == SIZE_MAX) {
        fputs("Input is too large\n", stderr);
        return -1;
    }

    if (memchr(text, '\0', text_length) != NULL) {
        fputs("Input contains an embedded null character\n", stderr);
        return -1;
    }

    if (copy_input(text, text_length, &input) != 0) {
        fputs("Unable to allocate or copy input\n", stderr);
        return -1;
    }

    result = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);

    if (result != 0) {
        report_regex_error(result, &regex);
        free(input);
        return -1;
    }

    cursor = input;
    remaining = text_length;

    while (remaining > 0) {
        regmatch_t match;
        uintmax_t start_value;
        uintmax_t end_value;
        size_t start;
        size_t end;
        size_t match_length;

        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            status = 0;
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex);
            goto cleanup;
        }

        if (match.rm_so < 0 || match.rm_eo < 0) {
            fputs("Invalid regex match range\n", stderr);
            goto cleanup;
        }

        start_value = (uintmax_t)match.rm_so;
        end_value = (uintmax_t)match.rm_eo;

        if (end_value <= start_value ||
            start_value > (uintmax_t)SIZE_MAX ||
            end_value > (uintmax_t)SIZE_MAX) {
            fputs("Invalid regex match range\n", stderr);
            goto cleanup;
        }

        start = (size_t)start_value;
        end = (size_t)end_value;

        if (start >= end || end > remaining) {
            fputs("Invalid regex match range\n", stderr);
            goto cleanup;
        }

        match_length = end - start;

        if (fwrite(cursor + start, 1, match_length, stdout) != match_length) {
            fputs("Failed to write output\n", stderr);
            goto cleanup;
        }

        if (fputc('\n', stdout) == EOF) {
            fputs("Failed to write output\n", stderr);
            goto cleanup;
        }

        cursor += end;
        remaining -= end;
    }

    if (remaining == 0) {
        status = 0;
    }

cleanup:
    regfree(&regex);
    free(input);
    return status;
}

int main(int argc, char **argv)
{
    size_t text_length;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (get_string_length(argv[1], &text_length) != 0) {
        fputs("Unable to determine input length\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_sequences(argv[1], text_length) != 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}