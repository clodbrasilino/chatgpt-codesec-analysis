#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str, size_t *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, 4096);
    if (len == 0) {
        *count = 0;
        return NULL;
    }

    size_t max_parts = 1;
    for (size_t i = 0; i < len; i++) {
        if (islower((unsigned char)str[i])) {
            max_parts++;
        }
    }

    char **result = calloc(max_parts, sizeof(char *));
    if (result == NULL) {
        *count = 0;
        return NULL;
    }

    size_t part_count = 0;
    size_t start = 0;

    for (size_t i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)str[i])) {
            size_t part_len = i - start;
            
            result[part_count] = malloc(part_len + 1);
            if (result[part_count] == NULL) {
                for (size_t j = 0; j < part_count; j++) {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }

            if (part_len > 0) {
                /* Possible weaknesses found:
                 *  'copy_len' is assigned value 'part_len' here.
                 */
                size_t copy_len = part_len;
                /* Possible weaknesses found:
                 *  The comparison 'copy_len > part_len' is always false because 'copy_len' and 'part_len' represent the same value.
                 *  The comparison 'copy_len > part_len' is always false because 'copy_len' and 'part_len' represent the same value. [knownConditionTrueFalse]
                 */
                if (copy_len > part_len) {
                    copy_len = part_len;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[part_count], str + start, copy_len);
            }
            result[part_count][part_len] = '\0';
            part_count++;
            start = i;
        }
    }

    *count = part_count;
    return result;
}

void free_split_result(char **result, size_t count) {
    if (result == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    size_t count = 0;

    char **parts = split_at_lowercase(test_string, &count);
    
    if (parts == NULL && count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original string: %s\n", test_string);
    printf("Split into %zu parts:\n", count);
    
    for (size_t i = 0; i < count; i++) {
        printf("Part %zu: \"%s\"\n", i + 1, parts[i]);
    }

    free_split_result(parts, count);

    return EXIT_SUCCESS;
}