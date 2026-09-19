#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

static void free_string_array(char **array, size_t count)
{
    if (array != NULL) {
        for (size_t i = 0; i < count; i++) {
            free(array[i]);
        }
        free(array);
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Python'], got <no output>
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  */

char **extract_strings(char **input, size_t input_count, size_t target_size, size_t *output_count)
{
    if (output_count != NULL) {
        *output_count = 0;
    }
    if (target_size == SIZE_MAX) {
        return NULL;
    }
    if (input == NULL || input_count == 0) {
        return NULL;
    }

    size_t str_len = target_size;
    char **result = NULL;
    size_t capacity = 0;
    size_t found = 0;

    for (size_t i = 0; i < input_count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        if (strlen(input[i]) == str_len) {
            if (found + 1 >= capacity) {
                size_t new_capacity = (capacity == 0) ? 4 : capacity * 2;
                if (new_capacity <= capacity) {
                    free_string_array(result, found);
                    return NULL;
                }
                if (new_capacity > SIZE_MAX / sizeof(*result)) {
                    free_string_array(result, found);
                    return NULL;
                }
                char **temp = realloc(result, new_capacity * sizeof(*temp));
                if (temp == NULL) {
                    free_string_array(result, found);
                    return NULL;
                }
                result = temp;
                capacity = new_capacity;
            }
            char *copy = malloc(target_size + 1);
            if (copy == NULL) {
                free_string_array(result, found);
                return NULL;
            }
            memcpy(copy, input[i], target_size);
            copy[target_size] = '\0';
            result[found] = copy;
            found++;
        }
    }

    if (found == 0) {
        free(result);
        return NULL;
    }

    if (found + 1 > capacity) {
        char **temp = realloc(result, (found + 1) * sizeof(*temp));
        if (temp == NULL) {
            free_string_array(result, found);
            return NULL;
        }
        result = temp;
    }
    result[found] = NULL;

    if (output_count != NULL) {
        *output_count = found;
    }
    return result;
}

int main(void)
{
    char *words[] = {"apple", "banana", "cherry", "date", "fig", "grape"};
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t extracted_count = 0;
    char **extracted = extract_strings(words, count, 6, &extracted_count);
    if (extracted != NULL) {
        for (size_t i = 0; i < extracted_count; i++) {
            printf("%s\n", extracted[i]);
        }
        free_string_array(extracted, extracted_count);
    }
    return 0;
}