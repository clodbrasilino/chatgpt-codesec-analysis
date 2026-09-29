#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void removeDigits(char *str) {
    char *i = str;
    char *j = str;
    
    while (*j != '\0') {
        if (!isdigit(*j)) {
            *i = *j;
            i++;
        }
        j++;
    }
    
    *i = '\0';
}

void removeDigitsFromList(char **list, int size) {
    for (int i = 0; i < size; i++) {
        removeDigits(list[i]);
    }
}

int main() {
    char *list[] = {"abc123", "def456", "ghi789", "jkl"};
    int size = sizeof(list) / sizeof(list[0]);
    
    removeDigitsFromList(list, size);
    
    for (int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }
    
    return 0;
}