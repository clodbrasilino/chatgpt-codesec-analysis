#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static size_t count_uppercase_splits(regex_t *regex, const char *input, size_t len) {
    size_t count = 1;
    const char *p = input;
    const char *end = input + len;
    regmatch_t match;

    while (p < end) {
        if (regexec(regex, p, 1, &match, 0) == 0 && match.rm_so == 0) {
            if (match.rm_eo > 0) {
                count++;
                p += match.rm_eo;
            } else {
                p++;
            }
        } else {
            break;
        }
    }
    return count;
}

char **split_at_uppercase(const char *input) {
    regex_t regex;
    regmatch_t match;
    size_t count;
    char **result;
    size_t i = 0;
    size_t start = 0;
    size_t len;

    if (!input) {
        return NULL;
    }

    len = strnlen(input, 4096);

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    if (len == 0) {
        result = malloc(2 * sizeof(char *));
        if (!result) {
            regfree(&regex);
            return NULL;
        }
        result[0] = malloc(1);
        if (!result[0]) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result[0][0] = '\0';
        result[1] = NULL;
        regfree(&regex);
        return result;
    }

    count = count_uppercase_splits(&regex, input, len);

    result = malloc((count + 1) * sizeof(char *));
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    start = 0;
    i = 0;

    while (i < count) {
        size_t end = len;

        if (i < count - 1) {
            int found = 0;
            const char *q = input + start;

            while (*q != '\0') {
                if (regexec(&regex, q, 1, &match, 0) == 0 && match.rm_so == 0) {
                    if (match.rm_eo > 0) {
                        end = (size_t)(q - input) + match.rm_eo;
                        found = 1;
                    }
                    break;
                }
                q++;
            }
            if (!found) {
                end = len;
            }
        }

        {
            size_t segment_len = end - start;
            result[i] = malloc(segment_len + 1);
            if (!result[i]) {
                size_t j;
                for (j = 0; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }

            if (segment_len > 0) {
                size_t max_copy = segment_len;
                if (max_copy > len - start) {
                    max_copy = len - start;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[i], input + start, max_copy);
            }
            result[i][segment_len] = '\0';
        }

        start = end;
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