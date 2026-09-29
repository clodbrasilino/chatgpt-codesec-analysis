#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    char *str_copy = strdup(input);
    size_t len = strlen(str_copy);

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        free(str_copy);
        *result = NULL;
        *count = 0;
        return;
    }

    *count = 1;
    for (int i = 0; i < len; i++) {
        if (str_copy[i] >= 'A' && str_copy[i] <= 'Z') {
            (*count)++;
        }
    }

    *result = (char **)malloc((*count) * sizeof(char *));
    if (*result == NULL) {
        free(str_copy);
        regfree(&regex);
        *count = 0;
        return;
    }

    int index = 0;
    int pos = 0;
    while (pos < len && index < *count) {
        if (regexec(&regex, str_copy + pos, 1, matches, 0) == 0 && matches[0].rm_so == 0) {
            (*result)[index] = strdup(str_copy + pos);
            if ((*result)[index] == NULL) {
                while (index-- > 0) {
                    free((*result)[index]);
                }
                free(*result);
                *result = NULL;
                *count = 0;
                break;
            }
            pos += matches[0].rm_eo;
            index++;
        } else {
            (*result)[index] = strndup(str_copy + pos, len - pos);
            if ((*result)[index] == NULL) {
                while (index-- > 0) {
                    free((*result)[index]);
                }
                free(*result);
                *result = NULL;
                *count = 0;
                break;
            }
            pos = len;
            index++;
        }
    }

    regfree(&regex);
    free(str_copy);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    char **result = NULL;
    int count = 0;

    split_string_at_uppercase(input, &result, &count);

    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * ASan: SEGV
         */
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}