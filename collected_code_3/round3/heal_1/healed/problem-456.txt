#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseString(char* str) {
    int len = strlen(str);
    char* buffer = malloc(sizeof(char)*(len+1));
    strcpy(buffer, str);

    for (int i = 0; i < len / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[len - i - 1];
        buffer[len - i - 1] = temp;
    }
    
    strcpy(str, buffer);
    free(buffer);
}

void reverseStringList(char** list, int size) {
    for (int i = 0; i < size; i++) {
        reverseString(list[i]);
    }
}

int main() {
    char list[4][20] = {"Hello", "World", "C", "Programming"};
    int size = sizeof(list) / sizeof(list[0]);

    reverseStringList((char**)list, size);

    for (int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}