#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *prefix)
{
    size_t needed;
    char *errbuf;

    needed = regerror(errcode, regex, NULL, 0);
    errbuf = malloc(needed);
    if (errbuf == NULL) {
        (void)fprintf(stderr, "%s: unable to allocate error buffer\n", prefix);
        return;
    }
    (void)regerror(errcode, regex, errbuf, needed);
    (void)fprintf(stderr, "%s: %s\n", prefix, errbuf);
    free(errbuf);
}

static int find_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int rc;

    if (text == NULL) {
        return -1;
    }

    rc = regcomp(&regex, "[[:alpha:]]{3,5}", REG_EXTENDED);
    if (rc != 0) {
        print_regex_error(rc, &regex, "regcomp failed");
        return -1;
    }

    cursor = text;
    while (*cursor != '\0') {
        rc = regexec(&regex, cursor, 1, &match, 0);
        if (rc == REG_NOMATCH) {
            break;
        }
        if (rc != 0) {
            print_regex_error(rc, &regex, "regexec failed");
            regfree(&regex);
            return -1;
        }

        {
            regoff_t start = match.rm_so;
            regoff_t end = match.rm_eo;
            regoff_t len = end - start;
            int left_ok = (start == 0) ||
                          !((cursor[start - 1] >= 'a' && cursor[start - 1] <= 'z') ||
                            (cursor[start - 1] >= 'A' && cursor[start - 1] <= 'Z'));
            int right_ok = !((cursor[end] >= 'a' && cursor[end] <= 'z') ||
                             (cursor[end] >= 'A' && cursor[end] <= 'Z'));

            if ((left_ok != 0) && (right_ok != 0)) {
                if (printf("%.*s\n", (int)len, cursor + start) < 0) {
                    regfree(&regex);
                    return -1;
                }
            }

            if (end == 0) {
                cursor += 1;
            } else {
                cursor += end;
                while ((*cursor >= 'a' && *cursor <= 'z') ||
                       (*cursor >= 'A' && *cursor <= 'Z')) {
                    cursor++;
                }
            }
        }
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "The quick brown fox jumps over a lazy dog nearby the extraordinary riverbank";

    if (printf("Input: %s\n", input) < 0) {
        return EXIT_FAILURE;
    }

    if (printf("Words with 3, 4, or 5 characters:\n") < 0) {
        return EXIT_FAILURE;
    }

    if (find_words(input) != 0) {
        (void)fprintf(stderr, "Word search failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}