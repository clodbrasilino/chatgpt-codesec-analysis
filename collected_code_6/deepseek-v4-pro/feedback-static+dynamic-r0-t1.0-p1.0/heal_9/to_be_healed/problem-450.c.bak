#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_strings_shorter_than(char **input, size_t count, size_t size) {
    size_t result = 0;
    for (size_t i = 0; i < count; i++) {
        if (input[i] != NULL && strlen(input[i]) < size) {
            result++;
        }
    }
    return result;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char **extract_strings(char **input, size_t count, size_t size, size_t *extracted_count) {
    if (input == NULL || count == 0 || size == 0 || extracted_count == NULL) {
        return NULL;
    }

    size_t selected_count = count_strings_shorter_than(input, count, size);
    if (selected_count == 0) {
        *extracted_count = 0;
        return NULL;
    }

    char **result = malloc(selected_count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < count; i++) {
        if (input[i] == NULL) {
            continue;
        }

        size_t len = strlen(input[i]);
        if (len < size) {
            result[index] = malloc((len + 1) * sizeof(char));
            if (result[index] == NULL) {
                for (size_t j = 0; j < index; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strcpy(result[index], input[i]);
            index++;
        }
    }

    *extracted_count = index;
    return result;
}

int main(void) {
    const char *strings[] = {"Python", "list", "exercise", "practice", "solution"};
    size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t extract_size = 8;

    char **input = malloc(count * sizeof(char *));
    if (input == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        input[i] = malloc((strlen(strings[i]) + 1) * sizeof(char));
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
        }

        for (size_t i = 0; i < extracted_count; i++) {
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