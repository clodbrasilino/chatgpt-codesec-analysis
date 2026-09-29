#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void concatenateTuple(const char tuple[][MAX_LENGTH], int size, const char delimiter[]) {
    char result[MAX_LENGTH] = "";
    int available_length = MAX_LENGTH;

    for(int i = 0; i < size; i++) {
        int delimiter_len = strnlen(delimiter, available_length);
        int tuple_len = strnlen(tuple[i], available_length - delimiter_len);

        if(tuple_len + delimiter_len >= available_length) {
            printf("Error: Buffer overflow would occur.\n");
            return;
        }

        strncat(result, tuple[i], tuple_len);
        available_length -= tuple_len;

        if(i != size - 1) {
            strncat(result, delimiter, delimiter_len);
            available_length -= delimiter_len;
        }
    }

    result[MAX_LENGTH - 1] = '\0';

    printf("%s\n", result);
}

int main() {
    const char tuple[][MAX_LENGTH] = {"Hello", "World", "How", "Are", "You"};
    const char delimiter[] = "-";
    int size = sizeof(tuple) / sizeof(tuple[0]);
    
    concatenateTuple(tuple, size, delimiter);

    return 0;
}