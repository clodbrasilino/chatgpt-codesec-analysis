#include <stdio.h>
#include <string.h>

int searchLiteral(char* str, char* literal) {
    char* result = strstr(str, literal);
    if (result != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char str[100] = "Hello, I am a C developer";
    char literal[10] = "developer";

    int found = searchLiteral(str, literal);

    if (found) {
        printf("Literal found in the string.\n");
    } else {
        printf("Literal not found in the string.\n");
    }

    return 0;
}