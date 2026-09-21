#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  */

char **extract_strings(char **strings, size_t count, size_t size, size_t *out_count) {
    if (out_count == NULL) {
        return NULL;
    }

    if (strings == NULL || count == 0 || size == 0) {
        *out_count = 0;
        return NULL;
    }

    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = strnlen(strings[i], size + 1);
        /* Possible weaknesses found:
         *  Assuming condition 'len<size' is false
         */
        if (len < size) {
            continue;
        }

        result[valid_count] = (char *)malloc((size + 1) * sizeof(char));
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (result[valid_count] == NULL) {
            for (size_t j = 0; j < valid_count; j++) {
                free(result[j]);
            }
            free(result);
            *out_count = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         *  Condition 'len<size' is always false [knownConditionTrueFalse]
         *  Condition 'len<size' is always false
         */
        size_t copy_len = (len < size) ? len : size;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[valid_count], strings[i], copy_len);
        result[valid_count][copy_len] = '\0';
        valid_count++;
    }

    if (valid_count == 0) {
        free(result);
        *out_count = 0;
        return NULL;
    }

    *out_count = valid_count;
    return result;
}

int main(void) {
    char *strings[] = {
        "hello",
        "world",
        "programming",
        "in",
        "c",
        "language"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t extract_size = 3;
    size_t result_count = 0;

    char **extracted = extract_strings(strings, count, extract_size, &result_count);

    if (extracted != NULL) {
        for (size_t i = 0; i < result_count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    } else {
        printf("No strings extracted or error occurred.\n");
    }

    return 0;
}