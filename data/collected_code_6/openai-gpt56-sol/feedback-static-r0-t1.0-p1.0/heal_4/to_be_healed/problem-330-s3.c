#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>
#include <stdint.h>

static int report_regex_error(int status, const regex_t *regex,
                              const char *operation)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *message;

    if (size == 0) {
        fprintf(stderr, "%s failed\n", operation);
        return -1;
    }

    message = malloc(size);
    if (message == NULL) {
        fprintf(stderr, "%s failed\n", operation);
        return -1;
    }

    regerror(status, regex, message, size);
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
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return report_regex_error(status, NULL, "regcomp");
    }

    for (;;) {
        regoff_t start;
        regoff_t end;
        regoff_t consumed;
        regoff_t word_length;

        status = regexec(&regex, cursor, 4, matches, 0);
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
        report_regex_error(status, &regex, "regexec");
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

    if (required > SIZE_MAX) {
        return -1;
    }

    new_capacity = *capacity == 0 ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = SIZE_MAX;
        } else {
            new_capacity *= 2;
        }

        if (new_capacity < required && new_capacity == SIZE_MAX) {
            return -1;
        }
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length > SIZE_MAX - 2) {
            free(buffer);
            return NULL;
        }

        if (grow_buffer(&buffer, &capacity, length + 2) != 0) {
            free(buffer);
            return NULL;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (grow_buffer(&buffer, &capacity, length + 1) != 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        if (ferror(stdin)) {
            perror("input");
            return EXIT_FAILURE;
        }

        if (!feof(stdin)) {
            fputs("Failed to read input\n", stderr);
            return EXIT_FAILURE;
        }

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