#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>
#include <stdint.h>

static int report_regex_error(int status, const regex_t *regex,
                              const char *operation)
{
    size_t size;
    char *message;

    size = regerror(status, regex, NULL, 0);
    if (size == 0U) {
        fprintf(stderr, "%s failed\n", operation);
        return -1;
    }

    message = malloc(size);
    if (message == NULL) {
        fprintf(stderr, "%s failed\n", operation);
        return -1;
    }

    (void)regerror(status, regex, message, size);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);

    return -1;
}

static int find_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:alpha:]]{3,5})([^[:alpha:]]|$)";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor;
    int status;

    if (text == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return report_regex_error(status, NULL, "regcomp");
    }

    cursor = text;

    for (;;) {
        regoff_t start;
        regoff_t end;
        regoff_t consumed;
        regoff_t word_length;

        status = regexec(&regex, cursor, 4U, matches, 0);
        if (status != 0) {
            break;
        }

        start = matches[2].rm_so;
        end = matches[2].rm_eo;
        consumed = matches[0].rm_eo;

        if (start < 0 || end < start || consumed <= 0) {
            regfree(&regex);
            return -1;
        }

        word_length = end - start;
        if ((uintmax_t)word_length > (uintmax_t)INT_MAX ||
            printf("%.*s\n", (int)word_length, cursor + start) < 0) {
            regfree(&regex);
            return -1;
        }

        cursor += consumed;
    }

    if (status != REG_NOMATCH) {
        (void)report_regex_error(status, &regex, "regexec");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = (*capacity == 0U) ? 128U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity < required) {
        return -1;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int ch;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }
            if (length == 0U) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2U) {
            free(buffer);
            return -1;
        }

        if (grow_buffer(&buffer, &capacity, length + 2U) != 0) {
            free(buffer);
            return -1;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length == SIZE_MAX ||
        grow_buffer(&buffer, &capacity, length + 1U) != 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    int status;

    status = read_line(stdin, &input);

    if (status < 0) {
        if (ferror(stdin)) {
            perror("input");
        } else {
            fputs("Failed to read input\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (find_words(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}