#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LIST_SIZE 3

// Function to remove all digits from a string

void removeDigitsFromString(char* str) {
    int i, j = 0, len;
    len = strlen(str);

    for (i = 0; i < len; i++) {
        if(!isdigit(str[i])) {
            str[j] = str[i];
            j++;
        }
    }
    
    str[j] = '\0';
}

// Function to remove all digits from a list of strings

void removeDigitsFromList(char list[][200], int listSize) {
    int i;
    for (i = 0; i < listSize; i++) {
        removeDigitsFromString(list[i]);
    }
}

// Main function

int main() {
    char list[LIST_SIZE][200] = {"str1ng1", "string2", "strin3g"};
    int i;
    
    removeDigitsFromList(list, LIST_SIZE);
    
    printf("After removing digits from list:\n");
    for (i = 0; i < LIST_SIZE; i++) {
        printf("%s\n", list[i]);
    }
    
    return 0;
}