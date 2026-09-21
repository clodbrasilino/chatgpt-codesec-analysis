#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static char **split_at_uppercase(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    const char *pattern = "[A-Z]";
    char **result = NULL;
    int capacity = 0;
    int segment_count = 0;
    size_t start = 0;
    size_t i = 0;
    size_t len;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);

    if (len == 0) {
        *count = 1;
        result = malloc(sizeof(char *));
        if (result == NULL) {
            return NULL;
        }
        result[0] = malloc(1);
        if (result[0] == NULL) {
            free(result);
            return NULL;
        }
        result[0][0] = '\0';
        return result;
    }

    *count = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    result = malloc(sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    capacity = 1;

    while (i < len) {
        if (regexec(&regex, input + i, 1, matches, 0) == 0) {
            size_t match_pos = i + (size_t)matches[0].rm_so;
            size_t segment_len = match_pos - start;

            if (segment_len > 0) {
                if (segment_count >= capacity) {
                    int new_capacity = capacity * 2;
                    char **temp = realloc(result, (size_t)new_capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (int j = 0; j < segment_count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                    capacity = new_capacity;
                }

                result[segment_count] = malloc(segment_len + 1);
                if (result[segment_count] == NULL) {
                    for (int j = 0; j < segment_count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }

                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[segment_count], input + start, segment_len);
                result[segment_count][segment_len] = '\0';
                segment_count++;
            }

            start = match_pos;
            i = match_pos + 1;
        } else {
            i++;
        }
    }

    if (start < len) {
        size_t segment_len = len - start;

        if (segment_count >= capacity) {
            int new_capacity = capacity * 2;
            char **temp = realloc(result, (size_t)new_capacity * sizeof(char *));
            if (temp == NULL) {
                for (int j = 0; j < segment_count; j++) {
                    free(result[j]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
            /* Possible weaknesses found:
             *  Value stored to 'capacity' is never read [deadcode.DeadStores]
             *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
             */
            capacity = new_capacity;
        }

        result[segment_count] = malloc(segment_len + 1);
        if (result[segment_count] == NULL) {
            for (int j = 0; j < segment_count; j++) {
                free(result[j]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[segment_count], input + start, segment_len);
        result[segment_count][segment_len] = '\0';
        segment_count++;
    }

    *count = segment_count;
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "helloWorldExample";
    int count = 0;
    char **parts = split_at_uppercase(test_string, &count);

    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);

    return 0;
}