#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidString(const char* str) {
    return (str && *str);
}

bool containsZ(const char* word){
    if(!isValidString(word)) {
        return false;
    }
    
    size_t word_length = 0;
    const char* temp = word;
    while(*temp++)
        word_length++;
    
    if(word_length < 3) {
        return false;
    }

    for(size_t i = 1; i < word_length - 1; i++) {
        if(word[i] == 'z') {
            return true;
        }
    }
    return false;
}

int main() {
    char word1[] = "zebra";
    char word2[] = "aztec";
    char word3[] = "blizzard";

    printf("%s: %s\n", word1, containsZ(word1) ? "Match" : "No match");
    printf("%s: %s\n", word2, containsZ(word2) ? "Match" : "No match");
    printf("%s: %s\n", word3, containsZ(word3) ? "Match" : "No match");

    return 0;
}