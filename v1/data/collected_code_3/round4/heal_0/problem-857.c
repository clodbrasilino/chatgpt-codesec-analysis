#include <stdio.h>

void printString(char* str) {
    printf("%s\n", str);
}

void map(char** arr, int size, void (*f)(char*)) {
    for(int i = 0; i < size; i++) {
        f(arr[i]);
    }
}

int main() {
    char* strings[] = {"Hello", "World", "This", "Is", "C"};
    int size = sizeof(strings) / sizeof(strings[0]);

    map(strings, size, printString);

    return 0;
}