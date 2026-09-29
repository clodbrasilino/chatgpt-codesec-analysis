#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void concatenateTuple(const char tuple[][MAX_LENGTH], int size, const char delimiter[]) {
    char result[MAX_LENGTH] = "";
    int result_length = 0;
    int delimiter_len = strnlen(delimiter, MAX_LENGTH);

    for (int i = 0; i < size; i++) {
        int tuple_len = strnlen(tuple[i], MAX_LENGTH - 1 - delimiter_len);

        if (result_length + tuple_len + delimiter_len >= MAX_LENGTH) {
            printf("Error: Buffer overflow would occur.\n");
            return;
        }

        strncpy(result + result_length, tuple[i], tuple_len);
        result_length += tuple_len;

        if (i != size - 1) {
            strncpy(result + result_length, delimiter, delimiter_len);
            result_length += delimiter_len;
        }
    }

    result[result_length] = '\0';

    printf("%s\n", result);
}

int main() {
    const char tuple[][MAX_LENGTH] = {"Hello", "World", "How", "Are", "You"};
    const char delimiter[] = "-";
    int size = sizeof(tuple) / sizeof(tuple[0]);
    
    concatenateTuple(tuple, size, delimiter);

    return 0;
}