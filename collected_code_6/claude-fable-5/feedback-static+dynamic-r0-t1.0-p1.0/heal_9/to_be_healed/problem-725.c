#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCH_GROUPS 2
#define MAX_INPUT_LEN 4096
#define ERRBUF_SIZE 256

static void print_regex_error(int code, const regex_t *regex, const char *context)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[ERRBUF_SIZE];
    size_t written;

    memset(errbuf, 0, sizeof(errbuf));
    written = regerror(code, regex, errbuf, sizeof(errbuf) - 1U);
    if (written >= sizeof(errbuf)) {
        errbuf[sizeof(errbuf) - 1U] = '\0';
    } else {
        errbuf[written < sizeof(errbuf) ? written : sizeof(errbuf) - 1U] = '\0';
    }
    errbuf[sizeof(errbuf) - 1U] = '\0';
    fprintf(stderr, "%s: %s\n", context, errbuf);
}

static char *extract_quoted_value(const char *input, size_t *offset)
{
    regex_t regex;
    regmatch_t matches[MAX_MATCH_GROUPS];
    char *result = NULL;
    int ret;
    size_t input_len;

    if (input == NULL || offset == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    if (*offset >= input_len) {
        return NULL;
    }

    ret = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "Regex compilation failed");
        regfree(&regex);
        return NULL;
    }

    memset(matches, 0, sizeof(matches));

    ret = regexec(&regex, input + *offset, MAX_MATCH_GROUPS, matches, 0);
    if (ret == 0) {
        regoff_t start = matches[1].rm_so;
        regoff_t end = matches[1].rm_eo;

        if (start >= 0 && end >= start &&
            (*offset + (size_t)end) <= input_len) {
            size_t len = (size_t)(end - start);

            if (len < MAX_INPUT_LEN &&
                (*offset + (size_t)start) <= input_len &&
                (*offset + (size_t)start + len) <= input_len) {
                result = malloc(len + 1U);
                if (result != NULL) {
                    if (len > 0U) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(result, input + *offset + (size_t)start, len);
                    }
                    result[len] = '\0';
                    if (matches[0].rm_eo > 0 &&
                        (*offset + (size_t)matches[0].rm_eo) <= input_len) {
                        *offset += (size_t)matches[0].rm_eo;
                    } else {
                        free(result);
                        result = NULL;
                    }
                } else {
                    fprintf(stderr, "Memory allocation failed\n");
                }
            }
        }
    } else if (ret != REG_NOMATCH) {
        print_regex_error(ret, &regex, "Regex execution failed");
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *text = "Name: \"Alice\", City: \"Paris\", Job: \"Engineer\"";
    size_t offset = 0;

    printf("Input: %s\n", text);

    for (;;) {
        char *value = extract_quoted_value(text, &offset);
        if (value == NULL) {
            break;
        }
        printf("Extracted: %s\n", value);
        free(value);
    }

    return EXIT_SUCCESS;
}