#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidString(const char* str) {
    return (str && *str) ? true : false;
}

bool containsZ(const char* word){
    if(!isValidString(word) || strlen(word) < 3) {
        return false;
    }

    const size_t word_length = strlen(word);
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