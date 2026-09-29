#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int rc, const regex_t *regex, const char *context)
{
    size_t needed;
    char *errbuf;

    needed = regerror(rc, regex, NULL, 0);
    errbuf = malloc(needed);
    if (errbuf == NULL) {
        fprintf(stderr, "Error: %s failed (unable to allocate error buffer)\n", context);
        return;
    }
    (void)regerror(rc, regex, errbuf, needed);
    fprintf(stderr, "Error: %s failed: %s\n", context, errbuf);
    free(errbuf);
}

static int find_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int rc;

    if (text == NULL) {
        fprintf(stderr, "Error: input text is NULL\n");
        return -1;
    }

    rc = regcomp(&regex, "[[:alpha:]]+", REG_EXTENDED);
    if (rc != 0) {
        print_regex_error(rc, &regex, "regcomp");
        return -1;
    }

    cursor = text;
    for (;;) {
        rc = regexec(&regex, cursor, 1, &match, 0);
        if (rc == REG_NOMATCH) {
            break;
        }
        if (rc != 0) {
            print_regex_error(rc, &regex, "regexec");
            regfree(&regex);
            return -1;
        }
        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            fprintf(stderr, "Error: invalid match offsets\n");
            regfree(&regex);
            return -1;
        }

        {
            size_t length = (size_t)(match.rm_eo - match.rm_so);
            if (length >= 3U && length <= 5U) {
                if (printf("%.*s\n", (int)length, cursor + match.rm_so) < 0) {
                    fprintf(stderr, "Error: printf failed\n");
                    regfree(&regex);
                    return -1;
                }
            }
        }

        if (match.rm_eo == 0) {
            break;
        }
        cursor += match.rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "The quick brown fox jumps over a lazy dog near riverbanks";

    if (find_words(input) != 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error: fflush failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}