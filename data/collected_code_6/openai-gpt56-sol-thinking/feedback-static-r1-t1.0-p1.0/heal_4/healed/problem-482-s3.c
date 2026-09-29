#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t message_size;
    char *message;

    message_size = regerror(error_code, regex, NULL, 0);
    if (message_size == 0) {
        fprintf(stderr, "Regex error: code %d\n", error_code);
        return;
    }

    message = malloc(message_size);
    if (message == NULL) {
        fprintf(stderr, "Regex error: code %d\n", error_code);
        return;
    }

    if (regerror(error_code, regex, message, message_size) > message_size) {
        fprintf(stderr, "Regex error: code %d\n", error_code);
    } else {
        fprintf(stderr, "Regex error: %s\n", message);
    }

    free(message);
}

static int write_all(FILE *stream, const char *data, size_t length)
{
    while (length != 0) {
        size_t written = fwrite(data, 1, length, stream);

        if (written == 0) {
            return -1;
        }

        data += written;
        length -= written;
    }

    return 0;
}

static int find_sequences(const char *input)
{
    regex_t regex;
    const char *cursor;
    int result;

    if (input == NULL) {
        return -1;
    }

    result = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, NULL);
        return -1;
    }

    cursor = input;

    while (*cursor != '\0') {
        regmatch_t match;
        uintmax_t start_value;
        uintmax_t end_value;
        size_t start;
        size_t end;
        size_t length;

        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        start_value = (uintmax_t)match.rm_so;
        end_value = (uintmax_t)match.rm_eo;

        if (start_value > (uintmax_t)SIZE_MAX ||
            end_value > (uintmax_t)SIZE_MAX) {
            regfree(&regex);
            return -1;
        }

        start = (size_t)start_value;
        end = (size_t)end_value;
        length = end - start;

        if (write_all(stdout, cursor + start, length) != 0 ||
            fputc('\n', stdout) == EOF) {
            regfree(&regex);
            return -1;
        }

        cursor += end;
    }

    regfree(&regex);

    return fflush(stdout) == EOF ? -1 : 0;
}

int main(int argc, char **argv)
{
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    if (find_sequences(argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}