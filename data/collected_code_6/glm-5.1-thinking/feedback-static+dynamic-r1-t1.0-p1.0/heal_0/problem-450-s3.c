#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings_by_size(const char * const *list, size_t count, size_t target_size, size_t *out_count) {
    if (list == NULL || out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (count == 0) {
        return NULL;
    }

    size_t match_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL && strlen(list[i]) == target_size) {
            match_count++;
        }
    }

    if (match_count == 0) {
        return NULL;
    }

    char **result = malloc(match_count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t current_index = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL && strlen(list[i]) == target_size) {
            result[current_index] = malloc(target_size + 1);
            if (result[current_index] == NULL) {
                for (size_t j = 0; j < current_index; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            memcpy(result[current_index], list[i], target_size);
            result[current_index][target_size] = '\0';
            current_index++;
        }
    }

    *out_count = match_count;
    return result;
}

void free_extracted_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void) {
    const char *list[] = {
        "apple",
        "banana",
        "cherry",
        "date",
        "fig",
        "grape",
        "kiwi",
        "lemon"
    };
    size_t count = sizeof(list) / sizeof(list[0]);
    size_t target_size = 5;
    size_t out_count = 0;

    char **extracted = extract_strings_by_size(list, count, target_size, &out_count);

    if (extracted != NULL) {
        for (size_t i = 0; i < out_count; i++) {
            printf("%s\n", extracted[i]);
        }
        free_extracted_strings(extracted, out_count);
    } else {
        printf("No strings found of size %zu\n", target_size);
    }

    return 0;
}