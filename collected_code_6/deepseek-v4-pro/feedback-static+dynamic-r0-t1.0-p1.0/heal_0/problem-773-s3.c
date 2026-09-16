#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int count;
    int *positions;
} OccurrenceResult;

OccurrenceResult find_occurrences(const char *str, const char *substr) {
    OccurrenceResult result;
    result.count = 0;
    result.positions = NULL;

    if (str == NULL || substr == NULL) {
        return result;
    }

    size_t str_len = strlen(str);
    size_t substr_len = strlen(substr);

    if (substr_len == 0 || substr_len > str_len) {
        return result;
    }

    int capacity = 16;
    result.positions = (int *)malloc(capacity * sizeof(int));
    if (result.positions == NULL) {
        result.count = 0;
        return result;
    }

    const char *current = str;
    const char *found = strstr(current, substr);

    while (found != NULL) {
        if (result.count >= capacity) {
            capacity *= 2;
            int *new_positions = (int *)realloc(result.positions, capacity * sizeof(int));
            if (new_positions == NULL) {
                free(result.positions);
                result.positions = NULL;
                result.count = 0;
                return result;
            }
            result.positions = new_positions;
        }

        result.positions[result.count] = (int)(found - str);
        result.count++;
        current = found + 1;
        found = strstr(current, substr);
    }

    return result;
}

void free_occurrences(OccurrenceResult *result) {
    if (result == NULL) {
        return;
    }

    free(result->positions);
    result->positions = NULL;
    result->count = 0;
}

int main(void) {
    const char *text = "abababab";
    const char *pattern = "aba";

    OccurrenceResult result = find_occurrences(text, pattern);

    printf("Occurrences: %d\n", result.count);
    for (int i = 0; i < result.count; i++) {
        printf("Position %d: %d\n", i + 1, result.positions[i]);
    }

    free_occurrences(&result);

    const char *empty_pattern = "";
    OccurrenceResult empty_result = find_occurrences(text, empty_pattern);
    printf("Empty pattern occurrences: %d\n", empty_result.count);

    free_occurrences(&empty_result);

    const char *null_str = NULL;
    OccurrenceResult null_result = find_occurrences(null_str, pattern);
    printf("Null string occurrences: %d\n", null_result.count);

    free_occurrences(&null_result);

    return 0;
}