#include <stdio.h>
#include <string.h>

int wordChecker(char* sentence, char* word) {
    if(sentence == NULL || word == NULL) {
        return 0;
    }
    
    char *token = strtok(sentence, " ");
    while (token != NULL) {
        if(strcmp(token,word) == 0){
            return 1;
        }
        token = strtok(NULL, " ");
    }
    return 0;
}

int main() {
    char sentence[200]; 
    char word[50]; 

    printf("Enter the sentence:\n");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = 0;

    printf("Enter the word to be searched:\n");
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = 0;

    if(wordChecker(sentence, word)){
        printf("Word Found!\n");
    } else {
        printf("Word Not Found!\n");
    }
    return 0;
}