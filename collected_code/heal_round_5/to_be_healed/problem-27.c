#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_ELEMENTS 4
#define MAX_LENGTH 11

void removeDigits(char *str, int length) {
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

void removeDigitsFromList(char ***list, int size, int *lengths) {
    if(list == NULL) 
        return;

    for (int i = 0; i < size && i < MAX_ELEMENTS; i++) {
        if((*list)[i] != NULL)
            removeDigits((*list)[i], lengths[i]);
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char list[MAX_ELEMENTS][MAX_LENGTH] = {"abc123", "def456", "ghi789", "jkl"};
    int size = sizeof(list) / sizeof(list[0]);
    int lengths[MAX_ELEMENTS] = {MAX_LENGTH, MAX_LENGTH, MAX_LENGTH, MAX_LENGTH};

    removeDigitsFromList((char ***)&list, size, lengths);

    for (int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }
    
    return 0;
}
