#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_literals(const char *haystack, const char **literals, size_t count) {
    if (haystack == NULL || literals == NULL) {
        return -1;
    }

    regex_t regex;
    int ret;
    size_t i;
    size_t len;
    char *escaped;
    size_t escaped_len;
    size_t j;
    size_t k;
    size_t cap;

    for (i = 0; i < count; i++) {
        if (literals[i] == NULL) {
            continue;
        }

        len = strlen(literals[i]);
        if (len == 0) {
            continue;
        }

        cap = len * 2 + 1;
        escaped = (char *)malloc(cap);
        if (escaped == NULL) {
            return -1;
        }

        escaped_len = 0;
        for (j = 0; j < len; j++) {
            char c = literals[i][j];
            switch (c) {
                case '^':
                case '.':
                case '[':
                case '$':
                case '(':
                case ')':
                case '|':
                case '*':
                case '+':
                case '?':
                case '{':
                case '\\':
                    if (escaped_len + 2 > cap) {
                        cap *= 2;
                        char *tmp = (char *)realloc(escaped, cap);
                        if (tmp == NULL) {
                            free(escaped);
                            return -1;
                        }
                        escaped = tmp;
                    }
                    escaped[escaped_len++] = '\\';
                    escaped[escaped_len++] = c;
                    break;
                default:
                    if (escaped_len + 1 > cap) {
                        cap *= 2;
                        char *tmp = (char *)realloc(escaped, cap);
                        if (tmp == NULL) {
                            free(escaped);
                            return -1;
                        }
                        escaped = tmp;
                    }
                    escaped[escaped_len++] = c;
                    break;
            }
        }
        escaped[escaped_len] = '\0';

        ret = regcomp(&regex, escaped, REG_EXTENDED | REG_NOSUB);
        free(escaped);

        if (ret != 0) {
            return -1;
        }

        ret = regexec(&regex, haystack, 0, NULL, 0);
        regfree(&regex);

        if (ret == 0) {
            return (int)i;
        } else if (ret != REG_NOMATCH) {
            return -1;
        }
    }

    return -1;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. Price: $100. [Tag]";
    const char *literals[] = {
        "quick",
        "$100",
        "[Tag]",
        "missing"
    };
    size_t count = sizeof(literals) / sizeof(literals[0]);

    int result = search_literals(text, literals, count);
    if (result >= 0) {
        printf("Found literal at index %d: %s\n", result, literals[result]);
    } else {
        printf("No literals found or error occurred.\n");
    }

    return 0;
}