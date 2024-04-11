#include <stdio.h>
#include <string.h>

int searchLiteral(char* str, char* literal) {
    char* ptr = strstr(str, literal);

    if(ptr != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char str[100];
    char literal[50];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    printf("Enter a literal to search: ");
    fgets(literal, sizeof(literal), stdin);
    literal[strlen(literal) - 1] = '\0';

    if(searchLiteral(str, literal)) {
        printf("Literal found in the string.\n");
    } else {
        printf("Literal not found in the string.\n");
    }

    return 0;
}