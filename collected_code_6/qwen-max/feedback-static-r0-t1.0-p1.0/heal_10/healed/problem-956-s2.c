#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    size_t len = strnlen(input, 256);
    if (len == 256 && input[len - 1] != '\0') {
        return;
    }
    char *str_copy = malloc((len + 1) * sizeof(char));
    if (str_copy == NULL) {
        return;
    }
    memcpy(str_copy, input, len);
    str_copy[len] = '\0';

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        free(str_copy);
        return;
    }

    *count = 1;
    for (int i = 0; i < len; i++) {
        if (str_copy[i] >= 'A' && str_copy[i] <= 'Z') {
            (*count)++;
        }
    }

    *result = malloc(*count * sizeof(char *));
    if (*result == NULL) {
        free(str_copy);
        regfree(&regex);
        return;
    }

    int index = 0;
    int pos = 0;
    while (pos < len && index < *count) {
        if (regexec(&regex, str_copy + pos, 1, matches, 0) == 0 && matches[0].rm_so == 0) {
            (*result)[index] = strndup(str_copy + pos, matches[0].rm_eo);
            if ((*result)[index] == NULL) {
                break;
            }
            pos += matches[0].rm_eo;
        } else {
            (*result)[index] = strndup(str_copy + pos, len - pos);
            if ((*result)[index] == NULL) {
                break;
            }
            pos = len;
        }
        index++;
    }

    if (index != *count) {
        for (int i = 0; i < index; i++) {
            free((*result)[i]);
        }
        free(*result);
        *result = NULL;
        *count = 0;
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