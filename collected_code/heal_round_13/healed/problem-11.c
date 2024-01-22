#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_SIZE 101

bool isValidString(const char* str) {
    if(str == NULL) return false;
    size_t len = strnlen(str, MAX_STR_SIZE);
    return len < MAX_STR_SIZE ? (str[len] == '\0') : false;
}

void removeOccurrences(char* str, const char c) {
    if(!isValidString(str)) {
        return;
    }

    int i, j;
    size_t len = strnlen(str, MAX_STR_SIZE);
    
    for(i = 0, j = 0; i < len; i++) {
        if(str[i] != c && j < MAX_STR_SIZE - 1) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char* str = calloc(MAX_STR_SIZE, sizeof(char));
    
    if(!str) {
        printf("Memory allocation failed\n");
        return 1;
    }

    char c;

    printf("Enter a string: ");
    if(!fgets(str, MAX_STR_SIZE, stdin)) {
        free(str);
        return 1;
    }

    size_t len = strnlen(str, MAX_STR_SIZE);
    if(len > 0 && str[len - 1] == '\n') str[--len] = '\0';

    printf("Enter a character: ");
    if(scanf(" %c", &c) != 1) {
        free(str);
        return 1;
    }

    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);

    removeOccurrences(str, c);

    printf("Modified string: %s\n", str);

    free(str);

    return 0;
}