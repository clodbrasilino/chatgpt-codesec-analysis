#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 102

void removeChar(char* str, const size_t str_len, char c) {
    if(str == NULL || str_len <= 0)
        return;

    size_t count = 0;
    for (size_t i = 0; i < str_len && str[i] != '\0'; i++) {
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
            removeChar(str, strlen(str), c);
            printf("String after removing character '%c': %s\n", c, str);
        }
    } else {
        printf("No character entered to remove\n");
    }

    return 0;
}