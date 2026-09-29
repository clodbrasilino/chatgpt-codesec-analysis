#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *str, int *count) {
    if (!str || !count) {
        return NULL;
    }

    size_t len = strnlen(str, 65536);
    size_t max_parts = len + 1;
    char **parts = malloc(max_parts * sizeof(char *));
    if (!parts) {
        return NULL;
    }

    int part_count = 0;
    size_t start = 0;

    for (size_t i = 0; i <= len; i++) {
        if (i == len || (i > 0 && isupper((unsigned char)str[i]))) {
            size_t part_len = i - start;
            /* Possible weaknesses found:
             *  Assuming that condition 'part_len>0' is not redundant
             */
            if (part_len > 0) {
                /* Possible weaknesses found:
                 *  alloc_size is assigned 'part_len+1' here.
                 */
                size_t alloc_size = part_len + 1;
                /* Possible weaknesses found:
                 *  Condition 'alloc_size<part_len' is always false
                 *  Condition 'alloc_size<part_len' is always false [knownConditionTrueFalse]
                 */
                if (alloc_size < part_len) {
                    for (int j = 0; j < part_count; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    return NULL;
                }
                parts[part_count] = malloc(alloc_size * sizeof(char));
                /* Possible weaknesses found:
                 *  Assuming condition is false
                 */
                if (!parts[part_count]) {
                    for (int j = 0; j < part_count; j++) {
                        free(parts[j]);
                    }
                    free(parts);
                    return NULL;
                }
                /* Possible weaknesses found:
                 *  Condition 'part_len>0' is always true [knownConditionTrueFalse]
                 *  Condition 'part_len>0' is always true
                 */
                if (part_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(parts[part_count], str + start, part_len);
                }
                parts[part_count][part_len] = '\0';
                part_count++;
            }
            start = i;
        }
    }

    if (part_count == 0) {
        free(parts);
        *count = 0;
        return NULL;
    }

    char **result = realloc(parts, part_count * sizeof(char *));
    if (!result) {
        for (int j = 0; j < part_count; j++) {
            free(parts[j]);
        }
        free(parts);
        return NULL;
    }

    *count = part_count;
    return result;
}

int main(void) {
    const char *input = "helloWorldExample";
    int count = 0;

    char **result = split_at_uppercase(input, &count);
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return EXIT_SUCCESS;
}