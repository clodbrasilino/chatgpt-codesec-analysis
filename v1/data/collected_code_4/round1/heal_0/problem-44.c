#include <stdio.h>
#include <string.h>

int match_beginning_word(const char* str, const char* word){
    if(!str || !word) {
        return 0;
    }
    int wordLength = strlen(word);
    if(strlen(str) < wordLength) {
        return 0;
    }
    for(int i = 0; i < wordLength; ++i) {
        if(str[i] != word[i]) {
            return 0;
        }
    }
    return 1;
}

int main(){
    char string[] = "stackoverflow";
    char word[] = "stack";

    if(match_beginning_word(string, word)){
        printf("Yes, there is a match.\n");
    }
    else{
        printf("No, there is no match.\n");
    }

    return 0;
}