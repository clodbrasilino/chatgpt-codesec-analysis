#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096
#define ERRBUF_SIZE 128

static void print_regex_error(int errcode, const regex_t *regex, const char *context)
{
    char errbuf[ERRBUF_SIZE];
    size_t needed;

    memset(errbuf, 0, sizeof(errbuf));
    needed = regerror(errcode, regex, errbuf, sizeof(errbuf));
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

        if (str[offset + (size_t)match.rm_so] == ' ') {
            str[offset + (size_t)match.rm_so] = '_';
        } else {
            str[offset + (size_t)match.rm_so] = ' ';
        }

        offset += (size_t)match.rm_so + 1;
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

    copy_size = input_len + 1;

    copy = malloc(copy_size);
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

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