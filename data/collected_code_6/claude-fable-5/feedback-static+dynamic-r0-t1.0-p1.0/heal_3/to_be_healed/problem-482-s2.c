#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERRBUF_SIZE 256

static int report_regex_error(int code, const regex_t *regex, const char *context)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[ERRBUF_SIZE];

    regerror(code, regex, errbuf, sizeof(errbuf));
    errbuf[sizeof(errbuf) - 1] = '\0';
    fprintf(stderr, "Error: %s: %s\n", context, errbuf);
    return -1;
}

int find_sequences(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Z][a-z]+";
    const char *cursor;
    int ret;

    if (input == NULL) {
        fprintf(stderr, "Error: input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return report_regex_error(ret, &regex, "could not compile regex");
    }

    cursor = input;
    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            report_regex_error(ret, &regex, "regex match failed");
            regfree(&regex);
            return -1;
        }

        {
            regoff_t start = match.rm_so;
            regoff_t end = match.rm_eo;
            size_t remaining;
            size_t len;
            char *found;

            if (start < 0 || end < start) {
                fprintf(stderr, "Error: invalid match offsets\n");
                regfree(&regex);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            remaining = strlen(cursor);
            if ((size_t)end > remaining) {
                fprintf(stderr, "Error: match offsets exceed input length\n");
                regfree(&regex);
                return -1;
            }

            len = (size_t)(end - start);

            if (len == 0) {
                if (*cursor == '\0') {
                    break;
                }
                cursor++;
                continue;
            }

            found = malloc(len + 1);
            if (found == NULL) {
                fprintf(stderr, "Error: memory allocation failed\n");
                regfree(&regex);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(found, cursor + start, len);
            found[len] = '\0';
            printf("Found sequence: %s\n", found);
            free(found);

            cursor += end;
            if (*cursor == '\0') {
                break;
            }
        }
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *test_string = "Hello world This is a Test String with Sequences";
    int result;

    printf("Input: %s\n", test_string);
    result = find_sequences(test_string);
    if (result != 0) {
        fprintf(stderr, "Error: sequence search failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}