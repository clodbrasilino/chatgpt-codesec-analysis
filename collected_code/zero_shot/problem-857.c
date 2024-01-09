#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printString(char* str) {
    printf("%s\n", str);
}

void listStrings(char** strings, int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        printString(strings[i]);
    }
}

int main() {
    char* strings[] = {"Hello", "World", "C", "Programming"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);
    
    listStrings(strings, numStrings);
    
    return 0;
}
