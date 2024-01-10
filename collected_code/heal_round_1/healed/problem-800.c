#include<stdio.h>
#include<string.h>

void removeWhitespace(char *str) {
    int i = 0, j = 0;
    size_t size_of_str = strlen(str);

    for(i= 0; i < size_of_str; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[100] = {0};
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0'; // to remove newline character
    printf("Before removing whitespaces: %s\n", str);
    removeWhitespace(str);
    printf("After removing whitespaces: %s\n", str);
    return 0;
}