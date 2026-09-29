#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void concatenateTuple(char tuple[][MAX_LENGTH], int size, char delimiter[]) {
    char result[MAX_LENGTH] = "";
    
    for(int i = 0; i < size; i++) {
        strcat(result, tuple[i]);
        if(i != size - 1) {
            strcat(result, delimiter);
        }
    }
    
    printf("%s\n", result);
}

int main() {
    char tuple[][MAX_LENGTH] = {"Hello", "World", "How", "Are", "You"};
    char delimiter[] = "-";
    int size = sizeof(tuple) / sizeof(tuple[0]);
    
    concatenateTuple(tuple, size, delimiter);
    
    return 0;
}