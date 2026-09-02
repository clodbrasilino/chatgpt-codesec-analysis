#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[10];
    int match_count, i, j, start = 0, end, len = strlen(input);
    char **split_strings;
    int max_matches = 10;

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED)) {
        return;
    }

    while (1) {
        match_count = regexec(&regex, input + start, max_matches, matches, 0);
        if (match_count == REG_NOMATCH || match_count > max_matches) {
            break;
        }
        for (i = 0; i < match_count; i++) {
            if (matches[i].rm_so == -1) {
                continue;
            }
            end = start + matches[i].rm_so;
            if (end > start) {
                (*count)++;
            }
            start = end + 1;
        }
    }

    if (start < len) {
        (*count)++;
    }

    split_strings = (char **)malloc((*count) * sizeof(char *));
    if (!split_strings) {
        return;
    }

    *result = split_strings;
    *count = 0;
    start = 0;

    while (1) {
        match_count = regexec(&regex, input + start, max_matches, matches, 0);
        if (match_count == REG_NOMATCH || match_count > max_matches) {
            break;
        }
        for (i = 0; i < match_count; i++) {
            if (matches[i].rm_so == -1) {
                continue;
            }
            end = start + matches[i].rm_so;
            if (end > start) {
                split_strings[*count] = (char *)malloc((end - start) * sizeof(char));
                if (!split_strings[*count]) {
                    for (j = 0; j < *count; j++) {
                        free(split_strings[j]);
                    }
                    free(split_strings);
                    return;
                }
                strncpy(split_strings[*count], input + start, end - start);
                split_strings[*count][end - start] = '\0';
                (*count)++;
            }
            start = end + 1;
        }
    }

    if (start < len) {
        split_strings[*count] = (char *)malloc((len - start + 1) * sizeof(char));
        if (!split_strings[*count]) {
            for (j = 0; j < *count; j++) {
                free(split_strings[j]);
            }
            free(split_strings);
            return;
        }
        strncpy(split_strings[*count], input + start, len - start);
        split_strings[*count][len - start] = '\0';
        (*count)++;
    }

    regfree(&regex);
}

int main() {
    const char *input = "HelloWorldExample";
    char **result = NULL;
    int count = 0;

    split_string_at_uppercase(input, &result, &count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}