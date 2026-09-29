#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void report_regex_error(const char *operation, int status,
                               const regex_t *regex)
{
    size_t size;
    char *message;

    size = regerror(status, regex, NULL, 0);
    if (size == 0) {
        fprintf(stderr, "%s failed\n", operation);
        return;
    }

    message = malloc(size);
    if (message == NULL) {
        fprintf(stderr, "%s failed\n", operation);
        return;
    }

    if (regerror(status, regex, message, size) == 0) {
        fprintf(stderr, "%s failed: %s\n", operation, message);
    } else {
        fprintf(stderr, "%s failed\n", operation);
    }

    free(message);
}

static int find_sequences(const char *input, size_t input_length)
{
    regex_t regex;
    regmatch_t match;
    size_t offset = 0;
    int status;

    if (input == NULL || input[input_length] != '\0') {
        return -1;
    }

    status = regcomp(&regex, "[[:upper:]][[:lower:]]+", REG_EXTENDED);
    if (status != 0) {
        report_regex_error("regcomp", status, NULL);
        return -1;
    }

    while (offset < input_length) {
        size_t remaining = input_length - offset;
        size_t start;
        size_t end;
        size_t match_length;

        status = regexec(&regex, input + offset, 1, &match, 0);
        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error("regexec", status, &regex);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < 0) {
            fprintf(stderr, "Invalid regular expression match\n");
            regfree(&regex);
            return -1;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;

        if (start > remaining || end > remaining || end <= start) {
            fprintf(stderr, "Invalid regular expression match\n");
            regfree(&regex);
            return -1;
        }

        match_length = end - start;

        if (fwrite(input + offset + start, 1, match_length, stdout) !=
            match_length) {
            perror("fwrite");
            regfree(&regex);
            return -1;
        }

        if (fputc('\n', stdout) == EOF) {
            perror("fputc");
            regfree(&regex);
            return -1;
        }

        if (end > SIZE_MAX - offset) {
            fprintf(stderr, "Input offset overflow\n");
            regfree(&regex);
            return -1;
        }

        offset += end;
    }

    regfree(&regex);
    return 0;
}

static int ensure_capacity(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || required == 0) {
        return -1;
    }

    if (required <= *capacity) {
        return *buffer == NULL ? -1 : 0;
    }

    new_capacity = *capacity == 0 ? 1U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int append_argument(char **buffer, size_t *length, size_t *capacity,
                           const char *argument, size_t argument_length,
                           int add_separator)
{
    size_t separator_length = add_separator != 0 ? 1U : 0U;
    size_t required;

    if (buffer == NULL || length == NULL || capacity == NULL ||
        argument == NULL || *buffer == NULL || *length >= *capacity ||
        (*buffer)[*length] != '\0') {
        return -1;
    }

    if (argument_length > SIZE_MAX - *length) {
        return -1;
    }
    required = *length + argument_length;

    if (separator_length > SIZE_MAX - required) {
        return -1;
    }
    required += separator_length;

    if (required == SIZE_MAX) {
        return -1;
    }
    ++required;

    if (ensure_capacity(buffer, capacity, required) != 0) {
        return -1;
    }

    if (argument_length != 0) {
        memmove(*buffer + *length, argument, argument_length);
        *length += argument_length;
    }

    if (add_separator != 0) {
        (*buffer)[(*length)++] = ' ';
    }

    (*buffer)[*length] = '\0';
    return 0;
}

int main(int argc, char *const argv[])
{
    size_t length = 0;
    size_t capacity = 64U;
    char *input;
    int i;

    if (argc < 2 || argv == NULL) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s <text>\n", program_name);
        return EXIT_FAILURE;
    }

    input = malloc(capacity);
    if (input == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    input[0] = '\0';

    for (i = 1; i < argc; ++i) {
        size_t argument_length;

        if (argv[i] == NULL) {
            fprintf(stderr, "Invalid argument\n");
            free(input);
            return EXIT_FAILURE;
        }

        argument_length = strnlen(argv[i], SIZE_MAX);
        if (argument_length == SIZE_MAX) {
            fprintf(stderr, "Argument is not properly terminated\n");
            free(input);
            return EXIT_FAILURE;
        }

        if (append_argument(&input, &length, &capacity, argv[i],
                            argument_length, i + 1 < argc) != 0) {
            fprintf(stderr, "Unable to construct input\n");
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (find_sequences(input, length) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}