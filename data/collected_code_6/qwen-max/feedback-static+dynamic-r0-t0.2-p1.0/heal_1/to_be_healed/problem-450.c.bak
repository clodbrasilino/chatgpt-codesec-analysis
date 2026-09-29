#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char **extract_strings(const char *const *input, size_t count, size_t size, size_t *output_count) {
    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        *output_count = 0;
        return NULL;
    }
    *output_count = 0;

    for (size_t i = 0; i < count; ++i) {
        if (strlen(input[i]) >= size) {
            result[*output_count] = (char *)malloc(size + 1);
            if (result[*output_count] == NULL) {
                while (*output_count > 0) {
                    free(result[--(*output_count)]);
                }
                free(result);
                *output_count = 0;
                return NULL;
            }
            strncpy(result[*output_count], input[i], size);
            result[*output_count][size] = '\0';
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
    const char *input[] = {"hello", "world", "this", "is", "a", "test"};
    size_t count = sizeof(input) / sizeof(input[0]);
    size_t size = 5;
    size_t output_count;

    char **result = extract_strings(input, count, size, &output_count);

    if (result != NULL) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", result[i]);
        }
        free_strings(result, output_count);
    } else {
        printf("Failed to allocate memory.\n");
    }

    return 0;
}