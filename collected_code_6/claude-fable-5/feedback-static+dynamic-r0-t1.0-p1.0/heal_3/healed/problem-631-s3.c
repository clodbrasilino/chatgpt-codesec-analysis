#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_STR_LEN 4096
#define ERRBUF_SIZE 128

static void report_regex_error(int errcode, const regex_t *regex, const char *context)
{
    char errbuf[ERRBUF_SIZE];

    memset(errbuf, 0, sizeof(errbuf));
    regerror(errcode, regex, errbuf, sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';
    fprintf(stderr, "%s failed: %s\n", context, errbuf);
}

int swap_whitespace_underscore(char *str, size_t max_len)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t offset = 0;
    size_t len;

    if (str == NULL || max_len == 0 || max_len > MAX_STR_LEN) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        fprintf(stderr, "Input string is not properly terminated or too long\n");
        return -1;
    }

    ret = regcomp(&regex, "[ _]", REG_EXTENDED);
    if (ret != 0) {
        report_regex_error(ret, &regex, "regcomp");
        return -1;
    }

    while (offset < len) {
        ret = regexec(&regex, str + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            report_regex_error(ret, &regex, "regexec");
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0) {
            break;
        }

        {
            size_t pos = offset + (size_t)match.rm_so;

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
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char input[] = "Hello world_this is_a test_string";
    char *copy;
    size_t input_len;
    size_t copy_size;

    input_len = strnlen(input, sizeof(input));
    if (input_len >= sizeof(input)) {
        fprintf(stderr, "Input string is not properly terminated\n");
        return EXIT_FAILURE;
    }

    if (input_len >= MAX_STR_LEN) {
        fprintf(stderr, "Input string exceeds maximum allowed length\n");
        return EXIT_FAILURE;
    }

    copy_size = input_len + 1;
    copy = malloc(copy_size);
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (snprintf(copy, copy_size, "%s", input) < 0) {
        fprintf(stderr, "String copy failed\n");
        free(copy);
        return EXIT_FAILURE;
    }

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