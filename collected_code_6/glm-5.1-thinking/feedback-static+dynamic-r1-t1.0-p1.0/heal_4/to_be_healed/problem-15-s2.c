#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char **split_at_lowercase(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t count = 0;
    int in_segment = 0;

    for (size_t i = 0; i < len; i++) {
        if (islower((unsigned char)str[i])) {
            in_segment = 0;
        } else {
            if (!in_segment) {
                if (count == SIZE_MAX) {
                    return NULL;
                }
                count++;
                in_segment = 1;
            }
        }
    }

    if (count > (SIZE_MAX / sizeof(char *)) - 1) {
        return NULL;
    }

    char **result = malloc((count + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t seg_idx = 0;
    const char *start = NULL;

    for (size_t i = 0; i <= len; i++) {
        if (i < len && !islower((unsigned char)str[i])) {
            if (start == NULL) {
                start = &str[i];
            }
        } else {
            if (start != NULL) {
                size_t seg_len = &str[i] - start;
                if (seg_len == SIZE_MAX) {
                    for (size_t j = 0; j < seg_idx; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                size_t buf_size = seg_len + 1;
                result[seg_idx] = malloc(buf_size);
                if (result[seg_idx] == NULL) {
                    for (size_t j = 0; j < seg_idx; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[seg_idx], start, seg_len);
                result[seg_idx][seg_len] = '\0';
                seg_idx++;
                start = NULL;
            }
        }
    }

    result[seg_idx] = NULL;
    return result;
}

void free_split_result(char **result) {
    if (result == NULL) {
        return;
    }
    for (size_t i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *tests[] = {
        "HELLOworldTHISisAtest",
        "lowercaseonly",
        "UPPERCASEONLY",
        "MixedCASEString",
        "",
        NULL
    };

    for (size_t t = 0; tests[t] != NULL; t++) {
        char **res = split_at_lowercase(tests[t]);
        if (res != NULL) {
            printf("Input: \"%s\"\n", tests[t]);
            if (res[0] == NULL) {
                printf("  (no segments)\n");
            } else {
                for (size_t i = 0; res[i] != NULL; i++) {
                    printf("  Segment %zu: \"%s\"\n", i, res[i]);
                }
            }
            free_split_result(res);
        }
    }

    return 0;
}