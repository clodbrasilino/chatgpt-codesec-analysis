#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(char *list[], int size, char delimiter) {
    if (size <= 0) return NULL;
    
    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        total_length += strlen(list[i]);
    }
    total_length += size - 1; // for delimiters
    total_length += 1; // for null terminator

    char *result = (char *)malloc(total_length * sizeof(char));
    if (result == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < size; ++i) {
        strcpy(result + index, list[i]);
        index += strlen(list[i]);
        if (i < size - 1) {
            result[index++] = delimiter;
        }
    }
    result[index] = '\0';

    return result;
}

int main() {
    char *tuple_list[] = {"one", "two", "three"};
    int size = 3;
    char delimiter = ',';
    char *flattened = flatten_tuple_list(tuple_list, size, delimiter);
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    } else {
        fprintf(stderr, "Failed to flatten the tuple list.\n");
    }
    return 0;
}