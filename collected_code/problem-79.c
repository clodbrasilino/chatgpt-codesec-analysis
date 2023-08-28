#include <stdbool.h>

bool isLengthOdd(char* word) {
    int length = 0;
    
    while (word[length] != '\0') {
        length++;
    }
    
    return length % 2 != 0;
}