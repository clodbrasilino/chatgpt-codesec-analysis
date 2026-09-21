#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_elements(char **list, int length) {
    if (length <= 0) return NULL;

    size_t total_length = 0;
    for (int i = 0; i < length; ++i) {
        total_length += strlen(list[i]);
    }
    total_length += length - 1;

    char *result = malloc(total_length + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';

    for (int i = 0; i < length; ++i) {
        strcat(result, list[i]);
        if (i < length - 1) {
            strcat(result, " ");
        }
    }

    return result;
}

int main() {
    char *elements[] = {"Hello", "", "World", ""};
    int num_elements = 4;

    char *concatenated = concatenate_elements(elements, num_elements);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}