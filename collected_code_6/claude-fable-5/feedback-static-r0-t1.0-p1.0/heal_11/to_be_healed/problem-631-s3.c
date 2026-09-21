#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096
#define ERRBUF_SIZE 128

static void print_regex_error(int errcode, const regex_t *regex, const char *context)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[ERRBUF_SIZE];
    size_t needed;

    memset(errbuf, 0, sizeof(errbuf));
    needed = regerror(errcode, regex, errbuf, sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';

    if (needed > sizeof(errbuf)) {
        fprintf(stderr, "%s failed: %s (message truncated)\n", context, errbuf);
    } else {
        fprintf(stderr, "%s failed: %s\n", context, errbuf);
    }
}

static int swap_whitespace_underscore(char *str, size_t max_len)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t offset = 0;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'pos' can be reduced. [variableScope]
     */
    size_t pos;

    if (str == NULL || max_len == 0) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        fprintf(stderr, "Input string is not null-terminated within %zu bytes\n", max_len);
        return -1;
    }

    ret = regcomp(&regex, "[ _]", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "regcomp");
        regfree(&regex);
        return -1;
    }

    while (offset < len) {
        ret = regexec(&regex, str + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            print_regex_error(ret, &regex, "regexec");
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0) {
            break;
        }

        if ((size_t)match.rm_so >= len - offset) {
            break;
        }

        pos = offset + (size_t)match.rm_so;
        if (pos >= len) {
            break;
        }

        if (str[pos] == ' ') {
            str[pos] = '_';
        } else {
            str[pos] = ' ';
        }

        offset = pos + 1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    static const char input[] = "Hello world_this is_a test_string";
    char *copy;
    size_t input_len;
    size_t copy_size;

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input string too long or not null-terminated\n");
        return EXIT_FAILURE;
    }

    if (input_len >= SIZE_MAX - 1) {
        fprintf(stderr, "Size calculation overflow\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  copy_size is assigned 'input_len+1' here.
     */
    copy_size = input_len + 1;

    copy = malloc(copy_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Condition 'input_len>=copy_size' is always false [knownConditionTrueFalse]
     *  Condition 'input_len>=copy_size' is always false
     */
    if (input_len >= copy_size) {
        fprintf(stderr, "Destination buffer too small\n");
        free(copy);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, input, input_len);
    copy[input_len] = '\0';

    printf("Original: %s\n", copy);

    if (swap_whitespace_underscore(copy, copy_size) != 0) {
        fprintf(stderr, "Failed to process string\n");
        free(copy);
        return EXIT_FAILURE;
    }

    printf("Modified: %s\n", copy);

    free(copy);
    return EXIT_SUCCESS;
}