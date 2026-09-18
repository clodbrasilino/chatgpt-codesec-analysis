#include <stdio.h>
#include <string.h>

#define MAX_SENTENCE_SIZE 1000
#define MAX_WORD_SIZE 100

int longest_word_length(char* sentence) {
    int max_len = 0;
    int curr_len = 0;
    for(int i = 0; i < strlen(sentence); i++){
        if (sentence[i] != ' '){
            curr_len++;
        }
        else{
            if(curr_len > max_len)
                max_len = curr_len;
            curr_len = 0;
        }
    }
    return (curr_len > max_len) ? curr_len : max_len;
}

int main(){
    
    char sentence[MAX_SENTENCE_SIZE];
    printf("Enter a sentence: ");
    fgets(sentence, MAX_SENTENCE_SIZE, stdin);

    int len = longest_word_length(sentence);
    printf("Longest word length: %d\n", len);

    return 0;
}