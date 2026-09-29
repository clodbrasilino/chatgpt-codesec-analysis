#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

static void print_regex_error(int errcode, const regex_t *regex)
{
    size_t needed;
    char *errbuf;

    needed = regerror(errcode, regex, NULL, 0);
    if (needed == 0) {
        fprintf(stderr, "Error: unknown regex error\n");
        return;
    }
    errbuf = malloc(needed);
    if (errbuf == NULL) {
        fprintf(stderr, "Error: memory allocation failed for error buffer\n");
        return;
    }
    regerror(errcode, regex, errbuf, needed);
    errbuf[needed - 1] = '\0';
    fprintf(stderr, "Error: %s\n", errbuf);
    free(errbuf);
}

int find_sequences(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Z][a-z]+";
    const char *cursor;
    size_t remaining;
    int ret;

    if (input == NULL) {
        fprintf(stderr, "Error: input string is NULL\n");
        return -1;
    }

    remaining = strnlen(input, MAX_INPUT_LEN);
    if (remaining >= MAX_INPUT_LEN && input[MAX_INPUT_LEN - 1] != '\0') {
        fprintf(stderr, "Error: input string is not properly terminated or too long\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex);
        return -1;
    }

    cursor = input;

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            print_regex_error(ret, &regex);
            regfree(&regex);
            return -1;
        }

        {
            regoff_t start = match.rm_so;
            regoff_t end = match.rm_eo;
            size_t len;
            size_t bufsize;
            char *found;

            if (start < 0 || end < 0 || end < start) {
                fprintf(stderr, "Error: invalid match offsets\n");
                regfree(&regex);
                return -1;
            }

            if ((size_t)end > remaining || (size_t)start > remaining) {
                fprintf(stderr, "Error: match offsets exceed remaining input\n");
                regfree(&regex);
                return -1;
            }

            len = (size_t)(end - start);

            if (len == 0) {
                if ((size_t)end >= remaining) {
                    break;
                }
                cursor += end + 1;
                remaining -= (size_t)end + 1;
                continue;
            }

            if (len > remaining - (size_t)start) {
                fprintf(stderr, "Error: match length exceeds remaining input\n");
                regfree(&regex);
                return -1;
            }

            if (len > MAX_INPUT_LEN) {
                fprintf(stderr, "Error: match length too large\n");
                regfree(&regex);
                return -1;
            }

            if (len > SIZE_MAX - 1) {
                fprintf(stderr, "Error: match length overflow\n");
                regfree(&regex);
                return -1;
            }

            /* Possible weaknesses found:
             *  bufsize is assigned 'len+1' here.
             */
            bufsize = len + 1;

            found = calloc(bufsize, sizeof(char));
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (found == NULL) {
                fprintf(stderr, "Error: memory allocation failed\n");
                regfree(&regex);
                return -1;
            }

            /* Possible weaknesses found:
             *  Condition 'len>=bufsize' is always false [knownConditionTrueFalse]
             *  Condition 'len>=bufsize' is always false
             */
            if (len >= bufsize) {
                fprintf(stderr, "Error: destination buffer too small\n");
                free(found);
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
            remaining -= (size_t)end;
            if (remaining == 0 || *cursor == '\0') {
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