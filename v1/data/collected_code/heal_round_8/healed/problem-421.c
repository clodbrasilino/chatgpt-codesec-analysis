#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void concatenateTuple(const char tuple[][MAX_LENGTH], int size, const char delimiter[]) {
    char result[MAX_LENGTH] = "";
    int result_len = 0;
    int delimiter_len = strnlen(delimiter, MAX_LENGTH);
    
    for (int i = 0; i < size; i++) {    
        int tuple_len = strnlen(tuple[i], MAX_LENGTH - 1 - delimiter_len);
        
        if (result_len + tuple_len + delimiter_len >= MAX_LENGTH) {
            printf("Error: Buffer overflow would occur.\n");
            return;
        }

        strncat(result, tuple[i], tuple_len);
        result_len += tuple_len;

        if (i != size - 1) {
            strncat(result, delimiter, delimiter_len);
            result_len += delimiter_len;
        }
    }

    printf("%s\n", result);
}

int main() {
    const char tuple[][MAX_LENGTH] = {"Hello", "World", "How", "Are", "You"};
    const char delimiter[] = "-";
    int size = sizeof(tuple) / sizeof(tuple[0]);
    
    concatenateTuple(tuple, size, delimiter);

    return 0;
}