#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_words(const char *str, char **results, int max_results) {
    regex_t regex;
    int ret;
    regmatch_t match;
    int count = 0;
    const char *pattern = "\\b[a-zA-Z]{3,5}\\b";
    const char *cursor = str;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    while (cursor && *cursor != '\0' && count < max_results) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            break;
        }

        if (match.rm_so == -1) {
            break;
        }

        size_t length = match.rm_eo - match.rm_so;
        if (length == 0) {
            if (*cursor != '\0') {
                cursor++;
            } else {
                break;
            }
            continue;
        }

        results[count] = malloc(length + 1);
        if (results[count] == NULL) {
            for (int i = 0; i < count; i++) {
                free(results[i]);
            }
            regfree(&regex);
            return 0;
        }

        snprintf(results[count], length + 1, "%.*s", (int)length, cursor + match.rm_so);
        count++;

        cursor += match.rm_eo;
    }

    regfree(&regex);
    return count;
}

int main() {
    const char *text = "I am a C developer and I write great code every day";
    int max_results = 32;
    char **results = malloc(max_results * sizeof(char *));
    if (results == NULL) {
        return 1;
    }

    int count = find_words(text, results, max_results);

    for (int i = 0; i < count; i++) {
        printf("%s\n", results[i]);
        free(results[i]);
    }
    free(results);

    return 0;
}