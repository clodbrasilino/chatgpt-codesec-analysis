#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str, size_t *out_count) {
    if (str == NULL || out_count == NULL) {
        return NULL;
    }

    size_t count = 0;
    const char *p = str;

    while (*p != '\0') {
        if (!islower((unsigned char)*p)) {
            count++;
            while (*p != '\0' && !islower((unsigned char)*p)) {
                p++;
            }
        } else {
            p++;
        }
    }

    /* Possible weaknesses found:
     *  alloc_items is assigned 'count+1' here.
     */
    size_t alloc_items = count + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_items<=count' is always false
     *  Condition 'alloc_items<=count' is always false [knownConditionTrueFalse]
     */
    if (alloc_items <= count) {
        return NULL;
    }

    char **result = malloc(alloc_items * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t index = 0;
    p = str;

    while (*p != '\0') {
        if (!islower((unsigned char)*p)) {
            const char *start = p;
            while (*p != '\0' && !islower((unsigned char)*p)) {
                p++;
            }
            size_t len = p - start;
            /* Possible weaknesses found:
             *  alloc_size is assigned 'len+1' here.
             */
            size_t alloc_size = len + 1;
            /* Possible weaknesses found:
             *  Condition 'alloc_size<=len' is always false [knownConditionTrueFalse]
             *  Condition 'alloc_size<=len' is always false
             */
            if (alloc_size <= len) {
                for (size_t i = 0; i < index; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }
            result[index] = malloc(alloc_size);
            if (result[index] == NULL) {
                for (size_t i = 0; i < index; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[index], start, len);
            result[index][len] = '\0';
            index++;
        } else {
            p++;
        }
    }

    result[index] = NULL;
    *out_count = count;
    return result;
}

int main(void) {
    const char *input = "HelloWorldABCdefGHI";
    size_t count = 0;
    char **parts = split_at_lowercase(input, &count);

    if (parts != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    }

    return 0;
}