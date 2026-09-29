#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t count = 0;
    int in_segment = 0;

    for (size_t i = 0; i < len; i++) {
        if (islower((unsigned char)str[i])) {
            in_segment = 0;
        } else {
            if (!in_segment) {
                count++;
                in_segment = 1;
            }
        }
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
                result[seg_idx] = malloc(seg_len + 1);
                if (result[seg_idx] == NULL) {
                    for (size_t j = 0; j < seg_idx; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
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