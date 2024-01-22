#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 101

void removeChar(char* str, char c, size_t str_size) {
    if(str == NULL)
        return;

    size_t count = 0;
    for (size_t i = 0; i < str_size && str[i] != '\0'; i++) {
        if (str[i] != c) {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

int main(void) {
    char str[MAX_SIZE] = {'\0'};
    char c;

    char temp[3] = {'\0'};

    printf("Enter a string: ");
    if(fgets(str, MAX_SIZE, stdin)) {
        str[strcspn(str, "\n")] = '\0';
    }

    printf("Enter the character to remove: ");
    if(fgets(temp, sizeof(temp), stdin)){
        if(temp[0] != '\n') {
            c = temp[0];
            removeChar(str, c, strlen(str));
            printf("String after removing character '%c': %s\n", c, str);
        }
    } else {
        printf("No character entered to remove\n");
    }

    return 0;
}