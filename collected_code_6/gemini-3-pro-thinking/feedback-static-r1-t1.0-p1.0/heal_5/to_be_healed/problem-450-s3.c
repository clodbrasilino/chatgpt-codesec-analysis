#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings_by_length(const char **input_list, size_t list_size, size_t target_length, size_t *out_count);
void free_extracted_strings(char **strings, size_t count);

char **extract_strings_by_length(const char **input_list, size_t list_size, size_t target_length, size_t *out_count) {
    if (!input_list || !out_count) {
        return NULL;
    }

    size_t match_count = 0;
    size_t capacity = 4;
    char **result = malloc(capacity * sizeof(char *));
    
    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < list_size; ++i) {
        if (input_list[i]) {
            size_t len = 0;
            while (len <= target_length && input_list[i][len] != '\0') {
                len++;
            }

            if (len == target_length) {
                if (match_count == capacity) {
                    size_t new_capacity = capacity * 2;
                    char **temp = realloc(result, new_capacity * sizeof(char *));
                    
                    if (!temp) {
                        for (size_t j = 0; j < match_count; ++j) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    capacity = new_capacity;
                }

                result[match_count] = malloc(target_length + 1);
                if (!result[match_count]) {
                    for (size_t j = 0; j < match_count; ++j) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[match_count], input_list[i], target_length);
                result[match_count][target_length] = '\0';
                match_count++;
            }
        }
    }

    *out_count = match_count;
    return result;
}

void free_extracted_strings(char **strings, size_t count) {
    if (!strings) {
        return;
    }
    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main(void) {
    const char *test_strings[] = {"hello", "world", "hi", "bye", "test", "apple", "cat"};
    size_t test_size = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t target_len = 3;
    size_t extracted_count = 0;

    char **extracted = extract_strings_by_length(test_strings, test_size, target_len, &extracted_count);

    if (extracted) {
        for (size_t i = 0; i < extracted_count; ++i) {
            if (printf("%s\n", extracted[i]) < 0) {
                break; 
            }
        }
        free_extracted_strings(extracted, extracted_count);
    }

    return 0;
}