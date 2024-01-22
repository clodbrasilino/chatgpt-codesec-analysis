#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_ELEMENTS 4
#define MAX_LENGTH 11

void removeDigits(char *str, size_t length) {
    if(str == NULL)
        return;

    char *ptr = str;

    while (*str != '\0' && (ptr - str) < length) {
        if (!isdigit((unsigned char)*str)) {
            *ptr++ = *str;
        }
        str++;
    }

    *ptr = '\0';
}

void removeDigitsFromList(char (*list)[MAX_LENGTH], size_t size, size_t *lengths) {
    if(list == NULL) 
        return;

    for (size_t i = 0; i < size && i < MAX_ELEMENTS; i++) {
        removeDigits(list[i], lengths[i]);
    }
}

int main() {
    char list[MAX_ELEMENTS][MAX_LENGTH] = {"abc123", "def456", "ghi789", "jkl"};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t lengths[MAX_ELEMENTS] = {MAX_LENGTH, MAX_LENGTH, MAX_LENGTH, MAX_LENGTH};

    removeDigitsFromList(list, size, lengths);

    for (size_t i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }
    
    return 0;
}