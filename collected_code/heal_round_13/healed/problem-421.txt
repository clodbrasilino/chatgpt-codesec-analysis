#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 100

void concatenateTuple(const char tuple[][MAX_LENGTH], int size, const char* delimiter) {

    char *result = malloc(MAX_LENGTH * sizeof(char));
    if (result == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    
    size_t result_len = 0;
    size_t delimiter_len = strnlen(delimiter, MAX_LENGTH);

    for (int i = 0; i < size; i++) {
        
        size_t tuple_len = strnlen(tuple[i], MAX_LENGTH);

        if (result_len + tuple_len + delimiter_len >= MAX_LENGTH) {
            printf("Error: Buffer overflow would occur.\n");
            free(result);
            return;
        }

        strncpy(result + result_len, tuple[i], tuple_len);
        result_len += tuple_len;

        if (i != size - 1) {
            
            strncpy(result + result_len, delimiter, delimiter_len);
            result_len += delimiter_len;
        }
    }
    
    result[result_len] = '\0';
    printf("%s\n", result);
    free(result);
}

int main() {
    const char tuple[][MAX_LENGTH] = {"Hello", "World", "How", "Are", "You"};
    const char *delimiter = "-";
    unsigned int size = sizeof(tuple) / sizeof(tuple[0]);
    
    concatenateTuple(tuple, size, delimiter);

    return 0;
}