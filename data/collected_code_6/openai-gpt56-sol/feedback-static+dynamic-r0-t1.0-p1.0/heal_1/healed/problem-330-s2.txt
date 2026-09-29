#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *message)
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

static int find_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alnum:]_])([[:alpha:]]{3,5})([^[:alnum:]_]|$)";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, &regex, "Regex compilation failed");
        regfree(&regex);
        return EXIT_FAILURE;
    }

    for (;;) {
        status = regexec(&regex, cursor,
                         sizeof(matches) / sizeof(matches[0]),
                         matches, 0);

        if (status != 0) {
            break;
        }

        if (matches[2].rm_so < 0 ||
            matches[2].rm_eo < matches[2].rm_so) {
            fprintf(stderr, "Regex returned an invalid match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        {
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
    }

    if (status != REG_NOMATCH) {
        report_regex_error(status, &regex, "Regex matching failed");
        regfree(&regex);
        return EXIT_FAILURE;
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        if (ferror(stdin)) {
            perror("Failed to read input");
        } else {
            fprintf(stderr, "No input provided\n");
        }

        free(input);
        return EXIT_FAILURE;
    }

    result = find_words(input);
    free(input);
    return result;
}