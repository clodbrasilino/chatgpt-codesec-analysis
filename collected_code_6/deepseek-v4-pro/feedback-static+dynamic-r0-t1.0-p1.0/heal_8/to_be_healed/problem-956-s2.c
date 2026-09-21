#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t count_uppercase_splits(const char *input, size_t len) {
    size_t count = 1;
    const char *p = input;
    const char *end = input + len;

    while (p < end) {
        if (*p >= 'A' && *p <= 'Z') {
            count++;
        }
        p++;
    }
    return count;
}

char **split_at_uppercase(const char *input) {
    size_t count;
    char **result;
    size_t i = 0;
    size_t start = 0;
    size_t len;

    if (!input) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 4096) {
        len = 4096;
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

    count = count_uppercase_splits(input, len);

    result = malloc((count + 1) * sizeof(char *));
    if (!result) {
        return NULL;
    }

    start = 0;
    i = 0;

    while (i < count) {
        size_t end = len;

        if (i < count - 1) {
            size_t q = start;
            int found = 0;

            while (q < len) {
                if (input[q] >= 'A' && input[q] <= 'Z') {
                    /* Possible weaknesses found:
                     *  Assuming that condition 'q>start' is not redundant
                     */
                    if (q > start) {
                        /* Possible weaknesses found:
                         *  Assignment 'end=q', assigned value is symbolic=start+1
                         */
                        end = q;
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
            /* Possible weaknesses found:
             *  Assignment 'segment_len=end-start', assigned value is greater than 0
             */
            size_t segment_len = end - start;
            char *segment = malloc(segment_len + 1);
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (!segment) {
                size_t j;
                for (j = 0; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            result[i] = segment;

            /* Possible weaknesses found:
             *  Condition 'segment_len>0' is always true [knownConditionTrueFalse]
             *  Condition 'segment_len>0' is always true
             */
            if (segment_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(segment, input + start, segment_len);
            }
            segment[segment_len] = '\0';
        }

        start = end;
        i++;
    }

    result[count] = NULL;
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