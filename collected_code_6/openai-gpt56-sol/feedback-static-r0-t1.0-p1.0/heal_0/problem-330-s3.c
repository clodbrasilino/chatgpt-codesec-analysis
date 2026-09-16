#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int find_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "(^|[^[:alpha:]])([[:alpha:]]{3,5})([^[:alpha:]]|$)";
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        size_t size = regerror(status, &regex, NULL, 0);
        char *message = malloc(size);

        if (message != NULL) {
            regerror(status, &regex, message, size);
            fprintf(stderr, "regcomp failed: %s\n", message);
            free(message);
        } else {
            fputs("regcomp failed\n", stderr);
        }

        return -1;
    }

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t start = (size_t)match.rm_so;
        size_t end = (size_t)match.rm_eo;
        size_t word_start;
        size_t word_end;

        while (start < end && !((cursor[start] >= 'A' && cursor[start] <= 'Z') ||
                                (cursor[start] >= 'a' && cursor[start] <= 'z'))) {
            ++start;
        }

        word_start = start;
        while (start < end && ((cursor[start] >= 'A' && cursor[start] <= 'Z') ||
                               (cursor[start] >= 'a' && cursor[start] <= 'z'))) {
            ++start;
        }
        word_end = start;

        if (word_end > word_start &&
            printf("%.*s\n", (int)(word_end - word_start), cursor + word_start) < 0) {
            regfree(&regex);
            return -1;
        }

        if (end == 0) {
            break;
        }

        cursor += end;
    }

    if (status != REG_NOMATCH) {
        size_t size = regerror(status, &regex, NULL, 0);
        char *message = malloc(size);

        if (message != NULL) {
            regerror(status, &regex, message, size);
            fprintf(stderr, "regexec failed: %s\n", message);
            free(message);
        } else {
            fputs("regexec failed\n", stderr);
        }

        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("fgets");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        fputs("Input is too long\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_words(input) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}