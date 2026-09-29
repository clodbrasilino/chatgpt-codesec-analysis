#include <stdio.h>
#include <string.h>

int stringSearch(char *str, char *toFind) {
    if(!str || !toFind) {
        return -1;
    }
    
    char *res = strstr(str, toFind);
    if(res) {
        return (res - str);
    }else {
        return -1;
    }
}

int main() {
    char originalString[100], literalString[50];   

    printf("Enter the original string: ");
    fgets(originalString, sizeof(originalString), stdin);

    printf("Enter the literal string to be searched: ");
    fgets(literalString, sizeof(literalString), stdin);

    // Remove newline character from originalString and literalString
    originalString[strlen(originalString) - 1] = 0;
    literalString[strlen(literalString) - 1] = 0;

    int pos = stringSearch(originalString, literalString);
    if (pos != -1)
        printf("'%s' found at position: %d\n", literalString, pos);
    else
        printf("'%s' not found in the string.\n", literalString);

    return 0;
}