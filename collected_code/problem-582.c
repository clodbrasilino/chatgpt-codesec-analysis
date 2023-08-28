#include <stdio.h>
#include <stdbool.h>

bool isEmptyDictionary(int numWords) {
    if(numWords == 0) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    int numWords = 0;
    bool empty = isEmptyDictionary(numWords);
    
    if(empty) {
        printf("The dictionary is empty.\n");
    }
    else {
        printf("The dictionary is not empty.\n");
    }
    
    return 0;
}