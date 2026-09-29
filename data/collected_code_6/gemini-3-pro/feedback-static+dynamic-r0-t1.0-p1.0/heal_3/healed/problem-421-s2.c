#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(char** tuple, int tuple_size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || tuple_size < 0) {
        return NULL;
    }

    if (tuple_size == 0) {
        char* empty_str = (char*)malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t delim_length = strlen(delimiter);
    size_t total_length = 0;

    for (int i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            total_length += strlen(tuple[i]);
        }
    }
    
    total_length += delim_length * (size_t)(tuple_size - 1) + 1; 

    char* result = (char*)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_pos = 0;

    for (int i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            int written = snprintf(result + current_pos, total_length - current_pos, "%s", tuple[i]);
            if (written > 0 && (size_t)written < total_length - current_pos) {
                current_pos += written;
            }
        }
        if (i < tuple_size - 1) {
            int written = snprintf(result + current_pos, total_length - current_pos, "%s", delimiter);
            if (written > 0 && (size_t)written < total_length - current_pos) {
                current_pos += written;
            }
        }
    }

    return result;
}

int main(void) {
    char* tuple[] = {"Hello", "World", "From", "C"};
    int tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = "-";

    char* result = concatenate_tuple(tuple, tuple_size, delimiter);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to concatenate tuple.\n");
    }

    return 0;
}