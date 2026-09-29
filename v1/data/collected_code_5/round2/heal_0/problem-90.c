#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longest_word_length(const char* str) {
    int max_len = 0;
    int cur_len = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == ' ' || str[i] == '\n' || str[i] == '\t'){
            max_len = cur_len > max_len ? cur_len : max_len;
            cur_len = 0;
        } else {
            cur_len++;
        }
    }
    max_len = cur_len > max_len ? cur_len : max_len;
    return max_len;
}

int main(){
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    int length = longest_word_length(str);
    printf("Length of the longest word is: %d", length);
    return 0;
}