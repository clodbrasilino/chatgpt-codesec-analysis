#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  */

char **extract_strings(const char *const *input, size_t count, size_t size, size_t *output_count) {
    if (input == NULL || count == 0 || size == 0) {
        *output_count = 0;
        return NULL;
    }

    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        *output_count = 0;
        return NULL;
    }

    *output_count = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t len = strlen(input[i]);
        if (len >= size - 1) {
            result[*output_count] = (char *)malloc(size);
            if (result[*output_count] == NULL) {
                while (*output_count > 0) {
                    free(result[--(*output_count)]);
                }
                free(result);
                *output_count = 0;
                return NULL;
            }
            strncpy(result[*output_count], input[i], size - 1);
            result[*output_count][size - 1] = '\0';
            (*output_count)++;
        } else if (len > 0) {
            result[*output_count] = (char *)malloc(len + 1);
            if (result[*output_count] == NULL) {
                while (*output_count > 0) {
                    free(result[--(*output_count)]);
                }
                free(result);
                *output_count = 0;
                return NULL;
            }
            strcpy(result[*output_count], input[i]);
            (*output_count)++;
        }
    }

    return result;
}

int main() {
    const char *strings[] = {"practice", "solution", "Python", "exercises"};
    size_t count = 4;
    size_t size = 5;
    size_t output_count;

    char **result = extract_strings(strings, count, size, &output_count);

    if (result != NULL) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}