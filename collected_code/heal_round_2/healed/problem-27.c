#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void removeDigits(char *str) {
    if(str == NULL)
        return;
    
    char *ptr = str;

    while (*str != '\0') {
        if (!isdigit((unsigned char)*str)) {
            *ptr++ = *str;
        }
        str++;
    }

    *ptr = '\0';
}

void removeDigitsFromList(char ***list, int size) {
    if(list == NULL) 
        return;
        
    for (int i = 0; i < size; i++) {
        if((*list)[i] != NULL)
            removeDigits((*list)[i]);
    }
}

int main() {
    char list[4][10] = {"abc123", "def456", "ghi789", "jkl"};
    int size = sizeof(list) / sizeof(list[0]);
    
    removeDigitsFromList((char ***)&list, size);

    for (int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }
    
    return 0;
}