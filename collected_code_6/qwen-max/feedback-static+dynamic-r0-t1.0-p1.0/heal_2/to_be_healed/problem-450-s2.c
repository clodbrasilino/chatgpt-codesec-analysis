#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char **extract_strings(const char *const *source, size_t count, size_t size, size_t *output_count) {
    if (source == NULL || count == 0 || size == 0 || output_count == NULL) {
        return NULL;
    }

    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    *output_count = 0;

    for (size_t i = 0; i < count; ++i) {
        if (strlen(source[i]) >= size) {
            result[*output_count] = (char *)malloc(strlen(source[i]) + 1);
            if (result[*output_count] == NULL) {
                for (size_t j = 0; j < *output_count; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strcpy(result[*output_count], source[i]);
            (*output_count)++;
        }
    }

    return result;
}

void free_strings(char **strings, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *const source[] = {
        "practice",
        "solution",
        "Python",
        "exercises"
    };

    size_t count = 4;
    size_t size = 2;
    size_t output_count = 0;

    char **result = extract_strings(source, count, size, &output_count);

    if (result != NULL) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", result[i]);
        }
        free_strings(result, output_count);
    }

    return 0;
}