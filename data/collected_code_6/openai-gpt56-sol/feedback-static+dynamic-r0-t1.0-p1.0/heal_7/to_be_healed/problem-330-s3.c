#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static void print_regex_error(int status, const regex_t *regex,
                              const char *prefix)
{
    size_t size;
    char *message;

    size = regerror(status, regex, NULL, 0);
    if (size == 0) {
        fprintf(stderr, "%s\n", prefix);
        return;
    }

    message = malloc(size);
    if (message == NULL) {
        fprintf(stderr, "%s\n", prefix);
        return;
    }

    (void)regerror(status, regex, message, size);
    fprintf(stderr, "%s: %s\n", prefix, message);
    free(message);
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
        print_regex_error(status, &regex, "regcomp failed");
        return -1;
    }

    cursor = text;

    for (;;) {
        regoff_t start;
        regoff_t end;
        regoff_t match_end;
        size_t word_length;

        status = regexec(&regex, cursor, 4, matches, 0);
        if (status != 0) {
            break;
        }

        start = matches[2].rm_so;
        end = matches[2].rm_eo;
        match_end = matches[0].rm_eo;

        if (start < 0 || end < start || match_end <= 0) {
            regfree(&regex);
            return -1;
        }

        word_length = (size_t)(end - start);
        if (fwrite(cursor + start, 1, word_length, stdout) != word_length ||
            fputc('\n', stdout) == EOF) {
            regfree(&regex);
            return -1;
        }

        cursor += (size_t)match_end;
    }

    if (status != REG_NOMATCH) {
        print_regex_error(status, &regex, "regexec failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

static int read_line(char **result)
{
    enum { INITIAL_CAPACITY = 256 };
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    char *input;

    if (result == NULL) {
        return -1;
    }

    *result = NULL;

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return -1;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                fputs("Input is too large\n", stderr);
                return -1;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Memory allocation failed\n", stderr);
                return -1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(input);
                perror("stdin");
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    input[length] = '\0';
    *result = input;
    return 0;
}

int main(void)
{
    char *input = NULL;
    int status;

    if (read_line(&input) != 0) {
        return EXIT_FAILURE;
    }

    status = find_words(input);
    free(input);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return status == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}