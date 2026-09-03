#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char **extract_strings(char **input, size_t count, size_t size, size_t *extracted_count) {
    if (input == NULL || count == 0 || size == 0 || extracted_count == NULL) {
        if (extracted_count != NULL) {
            *extracted_count = 0;
        }
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (input[i] != NULL && strlen(input[i]) > 0) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        *extracted_count = 0;
        return NULL;
    }

    char **result = (char **)malloc(valid_count * sizeof(char *));
    if (result == NULL) {
        *extracted_count = 0;
        return NULL;
    }

    size_t result_index = 0;
    for (size_t i = 0; i < count && result_index < valid_count; i++) {
        if (input[i] == NULL || strlen(input[i]) == 0) {
            continue;
        }

        size_t str_len = strlen(input[i]);
        size_t copy_size = str_len < size ? str_len : size;
        result[result_index] = (char *)malloc((copy_size + 1) * sizeof(char));
        if (result[result_index] == NULL) {
            for (size_t j = 0; j < result_index; j++) {
                free(result[j]);
            }
            free(result);
            *extracted_count = 0;
            return NULL;
        }

        memcpy(result[result_index], input[i], copy_size);
        result[result_index][copy_size] = '\0';
        result_index++;
    }

    *extracted_count = result_index;
    return result;
}

int main(void) {
    const char *strings[] = {"Python", "list", "exercise", "practice", "solution"};
    size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t extract_size = 8;

    char **input = (char **)malloc(count * sizeof(char *));
    if (input == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        input[i] = (char *)malloc((strlen(strings[i]) + 1) * sizeof(char));
        if (input[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(input[j]);
            }
            free(input);
            return 1;
        }
        strcpy(input[i], strings[i]);
    }

    size_t extracted_count = 0;
    char **extracted = extract_strings(input, count, extract_size, &extracted_count);
    
    if (extracted != NULL) {
        for (size_t i = 0; i < extracted_count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    }

    for (size_t i = 0; i < count; i++) {
        free(input[i]);
    }

    free(input);
    return 0;
}