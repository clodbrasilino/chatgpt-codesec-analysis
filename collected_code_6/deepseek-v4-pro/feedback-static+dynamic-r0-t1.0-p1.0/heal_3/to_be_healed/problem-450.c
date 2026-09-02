#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got ["Python","list","practice","solution"
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char **extract_strings(char **input, size_t count, size_t size) {
    if (input == NULL || count == 0 || size == 0) {
        return NULL;
    }

    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t actual_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (input[i] == NULL) {
            continue;
        }

        size_t len = strlen(input[i]);
        if (len <= size) {
            result[actual_count] = (char *)malloc((len + 1) * sizeof(char));
            if (result[actual_count] == NULL) {
                for (size_t j = 0; j < actual_count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strcpy(result[actual_count], input[i]);
            actual_count++;
        }
    }

    if (actual_count == 0) {
        free(result);
        return NULL;
    }

    char **final_result = (char **)realloc(result, actual_count * sizeof(char *));
    if (final_result == NULL) {
        for (size_t j = 0; j < actual_count; j++) {
            free(result[j]);
        }
        free(result);
        return NULL;
    }

    return final_result;
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

    char **extracted = extract_strings(input, count, extract_size);
    if (extracted == NULL) {
        for (size_t i = 0; i < count; i++) {
            free(input[i]);
        }
        free(input);
        return 1;
    }

    size_t extracted_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strlen(strings[i]) <= extract_size) {
            extracted_count++;
        }
    }

    for (size_t i = 0; i < extracted_count; i++) {
        printf("%s\n", extracted[i]);
    }

    for (size_t i = 0; i < extracted_count; i++) {
        free(extracted[i]);
    }
    free(extracted);

    for (size_t i = 0; i < count; i++) {
        free(input[i]);
    }
    free(input);

    return 0;
}