#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    int capacity = 10;
    char **result = malloc((size_t)capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t start = 0;
    int num_tokens = 0;

    for (size_t i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)str[i])) {
            size_t token_len = i - start;
            /* Possible weaknesses found:
             *  Assuming that condition 'token_len>0' is not redundant
             */
            if (token_len > 0) {
                if (num_tokens >= capacity) {
                    capacity *= 2;
                    char **temp = realloc(result, (size_t)capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (int j = 0; j < num_tokens; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }

                result[num_tokens] = malloc(token_len + 1);
                /* Possible weaknesses found:
                 *  Assuming condition is false
                 */
                if (result[num_tokens] == NULL) {
                    for (int j = 0; j < num_tokens; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                /* Possible weaknesses found:
                 *  Condition 'token_len>0' is always true [knownConditionTrueFalse]
                 *  Condition 'token_len>0' is always true
                 */
                if (token_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result[num_tokens], str + start, token_len);
                }
                result[num_tokens][token_len] = '\0';
                num_tokens++;
            }
            start = i + 1;
        }
    }

    *count = num_tokens;
    return result;
}

int main(void) {
    const char *test_str = "HelloWorldThisIsATest";
    int count = 0;
    char **tokens = split_at_lowercase(test_str, &count);

    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", tokens[i]);
        free(tokens[i]);
    }
    free(tokens);

    return 0;
}