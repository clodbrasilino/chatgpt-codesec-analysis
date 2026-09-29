#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_substrings(const char *str, const char *substr, size_t **positions) {
    if (str == NULL || substr == NULL || positions == NULL) {
        return -1;
    }

    size_t str_len = strlen(str);
    size_t substr_len = strlen(substr);

    if (substr_len == 0 || str_len == 0 || substr_len > str_len) {
        *positions = NULL;
        return 0;
    }

    size_t count = 0;
    size_t capacity = 10;
    size_t *pos_array = (size_t *)malloc(capacity * sizeof(size_t));
    
    if (pos_array == NULL) {
        return -1;
    }

    const char *current = str;
    const char *found;

    while ((found = strstr(current, substr)) != NULL) {
        if (count >= capacity) {
            size_t new_capacity = capacity * 2;
            size_t *new_array = (size_t *)realloc(pos_array, new_capacity * sizeof(size_t));
            
            if (new_array == NULL) {
                free(pos_array);
                return -1;
            }
            
            pos_array = new_array;
            capacity = new_capacity;
        }

        pos_array[count] = (size_t)(found - str);
        count++;
        current = found + 1;
    }

    if (count == 0) {
        free(pos_array);
        *positions = NULL;
        return 0;
    }

    size_t *final_array = (size_t *)realloc(pos_array, count * sizeof(size_t));
    if (final_array != NULL) {
        pos_array = final_array;
    }

    *positions = pos_array;
    return (int)count;
}

int main(void) {
    char str[1024];
    char substr[256];
    size_t *positions = NULL;
    int result;

    printf("Enter the main string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    str[strcspn(str, "\n")] = '\0';

    printf("Enter the substring to find: ");
    if (fgets(substr, sizeof(substr), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    substr[strcspn(substr, "\n")] = '\0';

    result = find_substrings(str, substr, &positions);

    if (result < 0) {
        fprintf(stderr, "Error: Memory allocation failed or invalid parameters\n");
        return 1;
    } else if (result == 0) {
        printf("Substring not found\n");
    } else {
        printf("Found %d occurrence(s) at position(s): ", result);
        for (int i = 0; i < result; i++) {
            printf("%zu", positions[i]);
            if (i < result - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }

    free(positions);
    return 0;
}