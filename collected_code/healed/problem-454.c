#include <stdio.h>
#include <stdbool.h>

bool containsZ(const char *word) {
    int i = 0;
    
    while (word[i] != '\0') {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
        i++;
    }
    
    return false;
}

int main() {
    const char word[] = "Hello, World!";
    
    if(containsZ(word)) {
        printf("The word contains a 'z' or a 'Z'\n");
    } else {
        printf("The word doesn't contain a 'z' or a 'Z'\n");
    }

    return 0;
}