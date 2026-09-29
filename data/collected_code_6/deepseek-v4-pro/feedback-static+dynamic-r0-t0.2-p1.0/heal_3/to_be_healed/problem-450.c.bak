#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char **extract_strings(char **input, int count, int size, int *result_count) {
    if (input == NULL || count <= 0 || size <= 0 || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    char **result = (char **)malloc((size_t)count * sizeof(char *));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    int extracted = 0;
    for (int i = 0; i < count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        size_t len = strlen(input[i]);
        if (len == (size_t)size) {
            continue;
        }
        result[extracted] = (char *)malloc(((size_t)size + 1) * sizeof(char));
        if (result[extracted] == NULL) {
            for (int j = 0; j < extracted; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0;
            return NULL;
        }
        memcpy(result[extracted], input[i], (size_t)size);
        result[extracted][size] = '\0';
        extracted++;
    }

    if (extracted == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    char **final_result = (char **)realloc(result, (size_t)extracted * sizeof(char *));
    if (final_result == NULL) {
        for (int j = 0; j < extracted; j++) {
            free(result[j]);
        }
        free(result);
        *result_count = 0;
        return NULL;
    }

    *result_count = extracted;
    return final_result;
}

int main(void) {
    char *strings[] = {"practice", "solution", "Python", "exercise"};
    int count = sizeof(strings) / sizeof(strings[0]);
    int result_count = 0;

    char **extracted = extract_strings(strings, count, 7, &result_count);

    if (extracted != NULL) {
        for (int i = 0; i < result_count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    } else {
        printf("No strings extracted or error occurred.\n");
    }

    return 0;
}