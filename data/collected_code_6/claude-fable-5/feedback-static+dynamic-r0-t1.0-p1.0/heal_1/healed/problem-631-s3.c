#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_STR_LEN 4096
#define ERRBUF_SIZE 128

int swap_whitespace_underscore(char *str, size_t max_len)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t offset = 0;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == max_len) {
        fprintf(stderr, "Input string is not properly terminated or too long\n");
        return -1;
    }

    ret = regcomp(&regex, "[ _]", REG_EXTENDED);
    if (ret != 0) {
        char errbuf[ERRBUF_SIZE];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    while (offset < len) {
        ret = regexec(&regex, str + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            char errbuf[ERRBUF_SIZE];
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            errbuf[sizeof(errbuf) - 1] = '\0';
            fprintf(stderr, "regexec failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || offset + (size_t)match.rm_so >= len) {
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
    char input[] = "Hello world_this is_a test_string";
    char *copy;
    size_t input_len;
    size_t copy_size;

    input_len = strnlen(input, sizeof(input));
    if (input_len >= sizeof(input)) {
        fprintf(stderr, "Input string is not properly terminated\n");
        return EXIT_FAILURE;
    }

    copy_size = input_len + 1;
    copy = malloc(copy_size);
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(copy, input, copy_size);
    copy[copy_size - 1] = '\0';

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