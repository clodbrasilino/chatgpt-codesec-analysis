#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 65536

static void print_regex_error(int ret, const regex_t *regex, const char *prefix)
{
    size_t errlen;
    char *errbuf;

    errlen = regerror(ret, regex, NULL, 0);
    errbuf = malloc(errlen);
    if (errbuf != NULL) {
        regerror(ret, regex, errbuf, errlen);
        fprintf(stderr, "%s: %s\n", prefix, errbuf);
        free(errbuf);
    } else {
        fprintf(stderr, "%s: unable to allocate error buffer\n", prefix);
    }
}

char *remove_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_len;
    size_t result_pos;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input exceeds maximum allowed length\n");
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "Regex compilation failed");
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    result_pos = 0;
    cursor = input;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, input_len - (size_t)(cursor - input));
            if (result_pos + remaining > input_len) {
                fprintf(stderr, "Internal bounds error\n");
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + result_pos, cursor, remaining);
            result_pos += remaining;
            break;
        }
        if (ret != 0) {
            print_regex_error(ret, &regex, "Regex execution failed");
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            fprintf(stderr, "Invalid match offsets\n");
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (result_pos + (size_t)match.rm_so > input_len) {
            fprintf(stderr, "Internal bounds error\n");
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + result_pos, cursor, (size_t)match.rm_so);
        result_pos += (size_t)match.rm_so;
        cursor += match.rm_eo;
    }

    result[result_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "helloWORLDfooBARbaz",
        "ABCdefGHIjkl",
        "no uppercase here",
        "ALLUPPERCASE",
        ""
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *cleaned = remove_uppercase(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Failed to process string: %s\n", test_strings[i]);
            return EXIT_FAILURE;
        }
        printf("Original: \"%s\" -> Result: \"%s\"\n", test_strings[i], cleaned);
        free(cleaned);
    }

    return EXIT_SUCCESS;
}