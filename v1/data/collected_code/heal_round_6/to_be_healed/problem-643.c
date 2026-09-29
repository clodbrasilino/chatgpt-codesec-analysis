#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidString(const char* str) {
    if(str == NULL) {
        return false;
    }
    while(*str) {
        if(*str == '\0') {
            return true;
        }
        ++str;
    }
    return false;
}

bool containsZ(const char* word){
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if(!isValidString(word) || strlen(word) < 3) {
        return false;
    }
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    for(size_t i = 1; i < strlen(word) - 1; i++) {
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