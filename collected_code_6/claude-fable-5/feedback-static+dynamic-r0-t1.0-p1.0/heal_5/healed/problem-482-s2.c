#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERRBUF_SIZE 256
#define MAX_INPUT_LEN 4096

static int report_regex_error(int code, const regex_t *regex, const char *context)
{
    char errbuf[ERRBUF_SIZE];
    size_t needed;

    memset(errbuf, 0, sizeof(errbuf));
    needed = regerror(code, regex, errbuf, sizeof(errbuf) - 1);
    if (needed >= sizeof(errbuf)) {
        errbuf[sizeof(errbuf) - 1] = '\0';
    }
    fprintf(stderr, "Error: %s: %s\n", context, errbuf);
    return -1;
}

int find_sequences(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Z][a-z]+";
    const char *cursor;
    size_t input_len;
    size_t consumed;
    int ret;

    if (input == NULL) {
        fprintf(stderr, "Error: input string is NULL\n");
        return -1;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN && input[MAX_INPUT_LEN - 1] != '\0') {
        fprintf(stderr, "Error: input string too long or not terminated\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return report_regex_error(ret, &regex, "could not compile regex");
    }

    cursor = input;
    consumed = 0;

    while (consumed <= input_len) {
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

            remaining = input_len - consumed;
            if ((size_t)end > remaining) {
                fprintf(stderr, "Error: match offsets exceed input length\n");
                regfree(&regex);
                return -1;
            }

            len = (size_t)(end - start);

            if (len == 0) {
                if (consumed >= input_len) {
                    break;
                }
                cursor++;
                consumed++;
                continue;
            }

            if (len > remaining || (size_t)start > remaining - len) {
                fprintf(stderr, "Error: match length exceeds remaining input\n");
                regfree(&regex);
                return -1;
            }

            found = malloc(len + 1);
            if (found == NULL) {
                fprintf(stderr, "Error: memory allocation failed\n");
                regfree(&regex);
                return -1;
            }

            memcpy(found, cursor + start, len);
            found[len] = '\0';
            printf("Found sequence: %s\n", found);
            free(found);

            cursor += end;
            consumed += (size_t)end;
            if (consumed >= input_len) {
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