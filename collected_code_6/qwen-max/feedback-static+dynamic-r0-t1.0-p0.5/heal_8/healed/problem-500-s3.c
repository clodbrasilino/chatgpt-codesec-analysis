#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        total_length += strlen(list[i]);
        total_length++;
    }
    total_length--; // Remove the extra space at the end

    char *result = malloc(total_length + 1);
    if (!result) return NULL;

    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        strncat(result, list[i], total_length - strlen(result));
        if (i < size - 1) {
            strncat(result, " ", total_length - strlen(result));
        }
    }

    return result;
}

int main() {
    const char *list[] = {"Hello", " ", "World", "!"};
    int size = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, size);
    if (concatenated) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Failed to concatenate list.\n");
    }

    return 0;
}