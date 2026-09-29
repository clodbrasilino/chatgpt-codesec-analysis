#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    char *output = malloc(input_len + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t out_idx = 0;
    const char *ptr = input;
    regmatch_t match;

    while (1) {
        ret = regexec(&regex, ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = strnlen(ptr, input_len - (ptr - input));
            if (out_idx + remaining_len < input_len + 1) {
                memcpy(output + out_idx, ptr, remaining_len);
                out_idx += remaining_len;
            }
            break;
        }

        if (ret != 0) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        size_t valid_len = match.rm_so;
        if (valid_len > 0) {
            if (out_idx + valid_len < input_len + 1) {
                memcpy(output + out_idx, ptr, valid_len);
                out_idx += valid_len;
            }
        }

        ptr += match.rm_eo;
    }

    output[out_idx] = '\0';

    regfree(&regex);

    char *shrunk = realloc(output, out_idx + 1);
    if (shrunk != NULL) {
        return shrunk;
    }

    return output;
}

int main(void) {
    const char *test = "Hello, World! 123 @#$%";
    char *result = remove_non_alnum(test);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}