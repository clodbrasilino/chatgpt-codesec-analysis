#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void concatenateTuple(const char tuple[][MAX_LENGTH], int size, const char* delimiter) {
    char result[MAX_LENGTH] = "";
    size_t result_len = strlen(result);
    size_t delimiter_len = strlen(delimiter);
   
    for (int i = 0; i < size; i++) {
        size_t tuple_len = strlen(tuple[i]);
      
        if (result_len + tuple_len + delimiter_len >= MAX_LENGTH) {
            printf("Error: Buffer overflow would occur.\n");
            return;
        }
    
        strncat(result, tuple[i], MAX_LENGTH - result_len - 1);
        result_len += tuple_len;

        if (i != size - 1) {
            strncat(result, delimiter, MAX_LENGTH - result_len - 1);
            result_len += delimiter_len;
        }
    }

    printf("%s\n", result);
}

int main() {
    const char tuple[][MAX_LENGTH] = {"Hello", "World", "How", "Are", "You"};
    const char *delimiter = "-";
    unsigned int size = sizeof(tuple) / sizeof(tuple[0]);
    
    concatenateTuple(tuple, size, delimiter);

    return 0;
}