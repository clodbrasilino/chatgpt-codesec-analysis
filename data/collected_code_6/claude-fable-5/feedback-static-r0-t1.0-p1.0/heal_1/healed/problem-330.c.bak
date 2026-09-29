#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static int find_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char errbuf[256];
    int rc;

    if (text == NULL) {
        fprintf(stderr, "Error: input text is NULL\n");
        return -1;
    }

    rc = regcomp(&regex, "[[:alpha:]]+", REG_EXTENDED);
    if (rc != 0) {
        regerror(rc, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error: regcomp failed: %s\n", errbuf);
        return -1;
    }

    cursor = text;
    for (;;) {
        rc = regexec(&regex, cursor, 1, &match, 0);
        if (rc == REG_NOMATCH) {
            break;
        }
        if (rc != 0) {
            regerror(rc, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Error: regexec failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }
        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            fprintf(stderr, "Error: invalid match offsets\n");
            regfree(&regex);
            return -1;
        }
        {
            const size_t length = (size_t)(match.rm_eo - match.rm_so);
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