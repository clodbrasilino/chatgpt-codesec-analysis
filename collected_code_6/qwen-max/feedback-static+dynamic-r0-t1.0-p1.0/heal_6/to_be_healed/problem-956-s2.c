#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    size_t len = strnlen(input, 1024);
    char *str_copy = (char *)malloc((len + 1) * sizeof(char));
    if (str_copy == NULL) {
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str_copy, input, len + 1);

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        free(str_copy);
        return;
    }

    *count = 1;
    for (size_t i = 0; i < len; i++) {
        if (str_copy[i] >= 'A' && str_copy[i] <= 'Z') {
            (*count)++;
        }
    }

    *result = (char **)malloc(*count * sizeof(char *));
    if (*result == NULL) {
        free(str_copy);
        regfree(&regex);
        return;
    }

    int index = 0;
    size_t pos = 0;
    while (pos < len && index < *count) {
        if (regexec(&regex, str_copy + pos, 1, matches, 0) == 0) {
            if (matches[0].rm_so > 0 || pos > 0) {
                (*result)[index] = strdup(str_copy + pos);
                if ((*result)[index] == NULL) {
                    while (index > 0) {
                        free((*result)[--index]);
                    }
                    free(*result);
                    free(str_copy);
                    regfree(&regex);
                    return;
                }
                pos += matches[0].rm_eo;
            } else {
                pos += matches[0].rm_eo;
                continue;
            }
        } else {
            (*result)[index] = strdup(str_copy + pos);
            if ((*result)[index] == NULL) {
                while (index > 0) {
                    free((*result)[--index]);
                }
                free(*result);
                free(str_copy);
                regfree(&regex);
                return;
            }
            pos = len;
        }
        index++;
    }

    regfree(&regex);
    free(str_copy);
}

int main() {
    const char input[] = "HelloWorldThisIsATest";
    char **result;
    int count;

    split_string_at_uppercase(input, &result, &count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}