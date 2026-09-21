#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        const char *str = list[i];
        while (*str++) total_length++;
        total_length++;
    }

    char *result = (char *)malloc(total_length);
    if (!result) return NULL;

    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        const char *str = list[i];
        while (*str) {
            strncat(result, str, 1);
            str++;
        }
        strncat(result, " ", 1);
    }
    result[total_length - 1] = '\0';

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