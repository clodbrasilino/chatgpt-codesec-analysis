#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_len = strlen(input) * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t res_idx = 0;
    const char *ptr = input;
    regmatch_t matches[3];

    while (*ptr != '\0') {
        if (regexec(&regex, ptr, 3, matches, 0) == 0) {
            size_t match_start = matches[0].rm_so;
            for (size_t i = 0; i < match_start; i++) {
                if (res_idx < max_len - 1) {
                    result[res_idx++] = ptr[i];
                }
            }
            if (res_idx < max_len - 1) {
                result[res_idx++] = ptr[matches[1].rm_so];
            }
            if (res_idx < max_len - 1) {
                result[res_idx++] = ' ';
            }
            if (res_idx < max_len - 1) {
                result[res_idx++] = ptr[matches[2].rm_so];
            }
            ptr += matches[0].rm_eo;
        } else {
            while (*ptr != '\0') {
                if (res_idx < max_len - 1) {
                    result[res_idx++] = *ptr;
                }
                ptr++;
            }
        }
    }

    result[res_idx] = '\0';
    regfree(&regex);

    char *shrunk = realloc(result, res_idx + 1);
    if (shrunk != NULL) {
        return shrunk;
    }
    return result;
}

int main(void) {
    const char *text = "HelloWorldThisIsATest";
    char *spaced = add_spaces(text);
    if (spaced != NULL) {
        printf("%s\n", spaced);
        free(spaced);
    }
    return 0;
}