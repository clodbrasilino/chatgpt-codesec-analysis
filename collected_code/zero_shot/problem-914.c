#include <stdbool.h>

bool isMadeOfAlternatingCharacters(char *str) {
    int i = 0;
    int length = 0;
    
    //get the length of the string
    while (str[length] != '\0') {
        length++;
    }
    
    //check if the string has only two characters
    if (length != 2) {
        return false;
    }
    
    //check if the characters alternate
    while (i < length - 1) {
        if (str[i] == str[i + 1]) {
            return false;
        }
        i++;
    }
    
    return true;
}