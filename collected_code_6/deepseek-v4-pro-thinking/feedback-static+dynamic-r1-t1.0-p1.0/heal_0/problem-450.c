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

char **extract_strings(char **input, size_t input_count, size_t target_size, size_t *output_count)
{
    if (output_count == NULL) {
        return NULL;
    }
    *output_count = 0;

    if (input == NULL) {
        return NULL;
    }

    if (target_size == SIZE_MAX) {
        return NULL;
    }

    char **result = NULL;
    size_t capacity = 0;
    size_t found = 0;

    for (size_t i = 0; i < input_count; i++) {
        if (input[i] == NULL) {
            continue;
        }

        if (strlen(input[i]) == target_size) {
            if (found == capacity) {
                size_t new_capacity;

                if (capacity == 0) {
                    new_capacity = 4;
                } else {
                    if (capacity > SIZE_MAX / 2) {
                        free_string_array(result, found);
                        return NULL;
                    }
                    new_capacity = capacity * 2;
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

    *output_count = found;
    return result;
}

int main(void)
{
    char *words[] = {"apple", "banana", "cherry", "date", "fig", "grape"};
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t extracted_count = 0;
    char **extracted = extract_strings(words, count, 5, &extracted_count);

    if (extracted != NULL) {
        for (size_t i = 0; i < extracted_count; i++) {
            printf("%s\n", extracted[i]);
        }
        free_string_array(extracted, extracted_count);
    }

    return 0;
}