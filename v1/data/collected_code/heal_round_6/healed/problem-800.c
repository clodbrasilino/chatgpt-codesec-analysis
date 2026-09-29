#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 101

void removeWhitespace(char *str, size_t str_length) {
    if (!str) return;

    int i = 0, j = 0;
    while(i < str_length && str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        ++i;
    }
    str[j] = '\0';
}

int main() {
    char str[MAX_LENGTH] = {0};
    char* newline;

    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin)) {
        newline = strchr(str, '\n');
        if (newline) 
           *newline = '\0';
    }

    printf("Before removing whitespaces: %s\n", str);

    if(strlen(str) < MAX_LENGTH) {
        removeWhitespace(str, strlen(str));
    } else {
        printf("The entered string exceed our input limit");
        return 1;
    }

    printf("After removing whitespaces: %s\n", str);

    return 0;
}
