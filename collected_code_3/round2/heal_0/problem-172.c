#include <stdio.h>
#include <string.h>

int findOccurrence(char* str) {
    int count = 0;
    for(int i = 0; i < strlen(str) - 2; i++) {
        if(str[i] == 's' && str[i+1] == 't' && str[i+2] == 'd') {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    printf("Occurrence of 'std': %d\n", findOccurrence(str));
    return 0;
}