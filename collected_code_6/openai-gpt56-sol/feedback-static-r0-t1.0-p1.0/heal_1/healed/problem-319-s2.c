#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>

static void report_regex_error(int status, const regex_t *regex, const char *message)
{
    size_t size = regerror(status, regex, NULL, 0);
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
    const char *cursor;
    int status;

    if (text == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, &regex, "regcomp failed");
        return -1;
    }

    cursor = text;

    for (;;) {
        status = regexec(&regex, cursor, 4, matches, 0);
        if (status != 0) {
            break;
        }

        if (matches[2].rm_so < 0 ||
            matches[2].rm_eo <= matches[2].rm_so) {
            regfree(&regex);
            return -1;
        }

        if (fwrite(cursor + matches[2].rm_so,
                   1,
                   (size_t)(matches[2].rm_eo - matches[2].rm_so),
                   stdout) !=
            (size_t)(matches[2].rm_eo - matches[2].rm_so) ||
            fputc('\n', stdout) == EOF) {
            regfree(&regex);
            return -1;
        }

        cursor += matches[2].rm_eo;
    }

    if (status != REG_NOMATCH) {
        report_regex_error(status, &regex, "regexec failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result = EXIT_FAILURE;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        fprintf(stderr, "Failed to read input\n");
        goto cleanup;
    }

    if (find_five_letter_words(input) != 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(input);
    return result;
}