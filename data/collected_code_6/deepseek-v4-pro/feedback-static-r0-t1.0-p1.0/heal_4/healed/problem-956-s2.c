#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *input) {
    regex_t regex;
    regmatch_t match;
    int count = 1;
    const char *p;
    char **result;
    int i = 0;
    int start = 0;
    size_t len;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, 4096);
    if (len >= 4096) {
        return NULL;
    }

    if (len == 0) {
        result = malloc(2 * sizeof(char *));
        if (!result) {
            return NULL;
        }
        result[0] = malloc(1);
        if (!result[0]) {
            free(result);
            return NULL;
        }
        result[0][0] = '\0';
        result[1] = NULL;
        return result;
    }

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    p = input;
    while (*p != '\0') {
        if (regexec(&regex, p, 1, &match, 0) == 0) {
            count++;
            p += match.rm_eo;
            if (match.rm_eo == 0) {
                p++;
            }
        } else {
            break;
        }
    }

    result = malloc((count + 1) * sizeof(char *));
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    p = input;
    start = 0;
    i = 0;

    while (i < count) {
        int found = 0;
        size_t end = len;
        const char *q = p;

        while (*q != '\0') {
            if (regexec(&regex, q, 1, &match, 0) == 0) {
                end = (q - input) + match.rm_eo;
                found = 1;
                break;
            }
            q++;
        }

        if (!found) {
            end = len;
        }

        if (i == count - 1) {
            end = len;
        }

        {
            size_t segment_len = end - start;
            if (segment_len > len - start) {
                segment_len = len - start;
            }
            result[i] = malloc((segment_len + 1) * sizeof(char));
            if (!result[i]) {
                int j;
                for (j = 0; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }

            if (segment_len > 0) {
                if (segment_len <= len - start) {
                    memcpy(result[i], input + start, segment_len);
                } else {
                    free(result[i]);
                    result[i] = NULL;
                    {
                        int j;
                        for (j = 0; j < i; j++) {
                            free(result[j]);
                        }
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                }
            }
            result[i][segment_len] = '\0';
        }

        start = (int)end;
        p = input + start;
        i++;
    }

    result[count] = NULL;
    regfree(&regex);
    return result;
}

void free_split_result(char **result) {
    int i = 0;
    if (!result) return;
    while (result[i] != NULL) {
        free(result[i]);
        i++;
    }
    free(result);
}

int main(void) {
    const char *test_string = "helloWorldThisIsATest";
    char **parts = split_at_uppercase(test_string);
    int i = 0;

    if (!parts) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    printf("Original: %s\n", test_string);
    printf("Split parts:\n");
    while (parts[i] != NULL) {
        printf("  [%d]: '%s'\n", i, parts[i]);
        i++;
    }

    free_split_result(parts);
    return 0;
}