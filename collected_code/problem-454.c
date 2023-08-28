#include <stdio.h>
#include <stdbool.h>

bool containsZ(char *word) {
    int i = 0;
    
    while (word[i] != '\0') {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
        i++;
    }
    
    return false;
}