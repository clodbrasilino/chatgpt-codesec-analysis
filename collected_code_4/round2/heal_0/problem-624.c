#include <ctype.h>
#include <stdio.h>
#include <string.h>

void stringToUpper(char *inputString) {
    for(int i = 0; inputString[i]; i++){
        inputString[i] = toupper(inputString[i]);
    }
}

int main() {
    char myString[] = "Hello, World!";
    stringToUpper(myString);
    printf("%s\n", myString);
    return 0;
}