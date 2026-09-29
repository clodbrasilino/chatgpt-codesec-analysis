#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_string_at_lowercase(const char *input, size_t *count) {
    *count = 0;
    if (input == NULL || *input == '\0') {
        return NULL;
    }

    size_t length = strlen(input);
    size_t max_parts = length + 1;
    char **parts = (char **)malloc(max_parts * sizeof(char *));
    if (parts == NULL) {
        return NULL;
    }

    const char *start = input;
    for (size_t i = 0; i < length; ++i) {
        if (islower((unsigned char)input[i])) {
            parts[*count] = (char *)malloc((i - (start - input) + 1) * sizeof(char));
            if (parts[*count] == NULL) {
                while (*count > 0) {
                    free(parts[--(*count)]);
                }
                free(parts);
                return NULL;
            }
            strncpy(parts[*count], start, i - (start - input));
            parts[*count][i - (start - input)] = '\0';
            (*count)++;
            start = input + i + 1;
        }
    }

    if (start < input + length) {
        parts[*count] = (char *)malloc((length - (start - input) + 1) * sizeof(char));
        if (parts[*count] == NULL) {
            while (*count > 0) {
                free(parts[--(*count)]);
            }
            free(parts);
            return NULL;
        }
        strcpy(parts[*count], start);
        (*count)++;
    }

    /* Possible weaknesses found:
     *  Common realloc mistake: 'parts' nulled but not freed upon failure [memleakOnRealloc]
     */
    parts = (char **)realloc(parts, (*count + 1) * sizeof(char *));
    parts[*count] = NULL;
    return parts;
}

void free_parts(char **parts) {
    if (parts != NULL) {
        size_t count = 0;
        while (parts[count] != NULL) {
            free(parts[count]);
            count++;
        }
        free(parts);
    }
}

int main() {
    const char *input = "HelloWorldExample";
    size_t count;
    char **result = split_string_at_lowercase(input, &count);

    if (result != NULL) {
        for (size_t i = 0; i < count; ++i) {
            printf("%s\n", result[i]);
        }
        free_parts(result);
    } else {
        printf("Failed to split the string.\n");
    }

    return 0;
}