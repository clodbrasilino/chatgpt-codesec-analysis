#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_literals_in_string(const char *haystack, const char **literals, size_t count) {
    regex_t regex;
    int ret;
    size_t i;
    char *escaped;
    size_t escaped_size;
    size_t j;
    size_t k;

    if (haystack == NULL || literals == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (literals[i] == NULL) {
            return -1;
        }

        size_t literal_len = strlen(literals[i]);
        if (literal_len == 0) {
            continue;
        }

        escaped_size = (literal_len * 2) + 4;
        escaped = (char *)malloc(escaped_size);
        if (escaped == NULL) {
            return -1;
        }

        j = 0;
        escaped[j++] = '(';
        escaped[j++] = '^';

        for (k = 0; k < literal_len; k++) {
            char c = literals[i][k];
            if (c == '.' || c == '*' || c == '+' || c == '?' || c == '|' ||
                c == '(' || c == ')' || c == '[' || c == ']' || c == '{' ||
                c == '}' || c == '\\' || c == '^' || c == '$') {
                if (j + 2 >= escaped_size) {
                    free(escaped);
                    return -1;
                }
                escaped[j++] = '\\';
                escaped[j++] = c;
            } else {
                if (j + 1 >= escaped_size) {
                    free(escaped);
                    return -1;
                }
                escaped[j++] = c;
            }
        }

        escaped[j++] = '$';
        escaped[j] = '\0';

        ret = regcomp(&regex, escaped, REG_NOSUB | REG_EXTENDED);
        free(escaped);
        if (ret != 0) {
            return -1;
        }

        ret = regexec(&regex, haystack, 0, NULL, 0);
        regfree(&regex);

        if (ret == 0) {
            return 1;
        } else if (ret != REG_NOMATCH) {
            return -1;
        }
    }

    return 0;
}

int main(void) {
    const char *haystack = "The quick brown fox jumps over the lazy dog";
    const char *literals[] = {"lazy dog", "cat", "fox"};
    size_t count = sizeof(literals) / sizeof(literals[0]);

    int result = search_literals_in_string(haystack, literals, count);

    if (result == 1) {
        printf("Match found\n");
    } else if (result == 0) {
        printf("No match found\n");
    } else {
        printf("Error occurred\n");
    }

    return 0;
}