#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 102

void removeWhitespace(char *str, size_t len) {
    if (!str || len >= MAX_LENGTH) return;

    size_t i = 0, j = 0;

    while(i < len && str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    
    str[j] = '\0';
}

int main() {
    char str[MAX_LENGTH+1] = {0};
    size_t length = 0;

    printf("Enter a string: ");
    
    if(fgets(str, sizeof(str), stdin)) {
        char* newline = strchr(str, '\n');
        
        if (newline) {
            *newline = '\0';
            length = newline - str;
        } else {
            while(getchar()!='\n');
            length = strlen(str);

            if (length >= MAX_LENGTH){
                printf("Input string is too long. Please enter a string with less than %d characters\n", MAX_LENGTH);
                return 1;
            }
        }
    }

    printf("Before removing whitespaces: %s\n", str);
    removeWhitespace(str, length);
    printf("After removing whitespaces: %s\n", str);

    return 0;
}