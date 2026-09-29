#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_lowercase(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t out_len = 0;
    const char *cursor;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strlen(cursor);
            if (out_len + remaining >= output_size) {
                regfree(&regex);
                return -1;
            }
            memcpy(output + out_len, cursor, remaining);
            out_len += remaining;
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            return -1;
        }
        if (match.rm_so > 0) {
            if (out_len + (size_t)match.rm_so >= output_size) {
                regfree(&regex);
                return -1;
            }
            memcpy(output + out_len, cursor, (size_t)match.rm_so);
            out_len += (size_t)match.rm_so;
        }
        cursor += match.rm_eo;
    }

    output[out_len] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *test_strings[] = {
        "HelloWorldFooBAR",
        "abcDEFghiJKL",
        "ALLUPPERCASE",
        "alllowercase",
        "Mix3d C4s3 Str1ng"
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char result[256];
        if (remove_lowercase(test_strings[i], result, sizeof(result)) == 0) {
            printf("Input:  %s\n", test_strings[i]);
            printf("Output: %s\n\n", result);
        } else {
            fprintf(stderr, "Failed to process string: %s\n", test_strings[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}