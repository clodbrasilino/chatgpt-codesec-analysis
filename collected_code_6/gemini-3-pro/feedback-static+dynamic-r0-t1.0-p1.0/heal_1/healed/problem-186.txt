#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_literals(const char *text, const char **literals, size_t num_literals) {
    if (text == NULL || literals == NULL || num_literals == 0) {
        return -1;
    }

    size_t total_len = 0;
    for (size_t i = 0; i < num_literals; i++) {
        if (literals[i] != NULL) {
            size_t len = strnlen(literals[i], 4096);
            if (len > 0) {
                total_len += len + 3;
            }
        }
    }

    if (total_len == 0) {
        return -1;
    }

    total_len += 1;

    char *pattern = (char *)malloc(total_len);
    if (pattern == NULL) {
        return -1;
    }

    pattern[0] = '\0';
    size_t pos = 0;
    int is_first = 1;

    for (size_t i = 0; i < num_literals; i++) {
        if (literals[i] != NULL) {
            size_t len = strnlen(literals[i], 4096);
            if (len > 0) {
                if (!is_first) {
                    int wrote = snprintf(pattern + pos, total_len - pos, "|");
                    if (wrote > 0 && (size_t)wrote < total_len - pos) {
                        pos += (size_t)wrote;
                    }
                }
                int wrote = snprintf(pattern + pos, total_len - pos, "(%s)", literals[i]);
                if (wrote > 0 && (size_t)wrote < total_len - pos) {
                    pos += (size_t)wrote;
                }
                is_first = 0;
            }
        }
    }

    if (is_first) {
        free(pattern);
        return -1;
    }

    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    free(pattern);

    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog.";
    const char *literals[] = {"fox", "cat", "dog"};
    size_t num_literals = sizeof(literals) / sizeof(literals[0]);

    int result = search_literals(text, literals, num_literals);

    if (result == 1) {
        printf("Match found.\n");
    } else if (result == 0) {
        printf("No match found.\n");
    } else {
        printf("An error occurred.\n");
    }

    return 0;
}