#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void concatenateTuple(const char tuple[][MAX_LENGTH], int size, const char delimiter[]) {
    char result[MAX_LENGTH] = "";

    for(int i = 0; i < size; i++) {
        if(strlen(result) + strlen(tuple[i]) + 1 > MAX_LENGTH) {
            printf("Error: Buffer overflow would occur.\n");
            return;
        }
        strncat(result, tuple[i], MAX_LENGTH - strlen(result) - 1);
        if(i != size - 1) {
            if(strlen(result) + strlen(delimiter) + 1 > MAX_LENGTH) {
                printf("Error: Buffer overflow would occur.\n");
                return;
            }
            strncat(result, delimiter, MAX_LENGTH - strlen(result) - 1);
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