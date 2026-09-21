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
        /* Possible weaknesses found:
         *  buffer_size is assigned 'length+1' here.
         */
        size_t buffer_size = length + 1;
        results[count] = malloc(buffer_size);
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (results[count] == NULL) {
            for (int i = 0; i < count; i++) {
                free(results[i]);
            }
            regfree(&regex);
            return 0;
        }

        /* Possible weaknesses found:
         *  Condition 'buffer_size<=length+1' is always true [knownConditionTrueFalse]
         *  Condition 'buffer_size<=length+1' is always true
         */
        if (length > 0 && buffer_size <= length + 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(results[count], cursor + match.rm_so, length);
        }
        results[count][length] = '\0';
        count++;

        cursor += match.rm_eo;
        if (match.rm_so == match.rm_eo) {
            if (*cursor != '\0') {
                cursor++;
            } else {
                break;
            }
        }
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