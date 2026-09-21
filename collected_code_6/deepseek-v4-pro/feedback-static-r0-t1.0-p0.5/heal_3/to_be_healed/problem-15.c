#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    int capacity = 10;
    char **result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    int start = 0;
    int num_tokens = 0;
    int i = 0;

    while (1) {
        if (str[i] == '\0' || islower((unsigned char)str[i])) {
            int token_len = i - start;
            /* Possible weaknesses found:
             *  Assuming that condition 'token_len>0' is not redundant
             */
            if (token_len > 0) {
                if (num_tokens >= capacity) {
                    int new_capacity = capacity * 2;
                    if (new_capacity < capacity) {
                        for (int j = 0; j < num_tokens; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    char **temp = realloc(result, new_capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (int j = 0; j < num_tokens; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    capacity = new_capacity;
                }

                /* Possible weaknesses found:
                 *  alloc_size is assigned '(unsigned long)token_len+1' here.
                 */
                size_t alloc_size = (size_t)token_len + 1;
                /* Possible weaknesses found:
                 *  Condition 'alloc_size<=(unsigned long)token_len' is always false
                 *  Condition 'alloc_size<=(unsigned long)token_len' is always false [knownConditionTrueFalse]
                 */
                if (alloc_size <= (size_t)token_len) {
                    for (int j = 0; j < num_tokens; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                result[num_tokens] = malloc(alloc_size);
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
                 *  Condition 'token_len>0' is always true
                 *  Condition 'token_len>0' is always true [knownConditionTrueFalse]
                 */
                if (token_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result[num_tokens], str + start, (size_t)token_len);
                }
                result[num_tokens][token_len] = '\0';
                num_tokens++;
            }
            if (str[i] == '\0') {
                break;
            }
            start = i + 1;
        }
        i++;
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