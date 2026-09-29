#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool is_length_even(char* word) {
    return strlen(word) % 2 == 0;
}

int main() {
    char word[100];
    printf("Enter a word: ");
    scanf("%s", word);

    if(is_length_even(word)) {
        printf("The length of the word is even.\n");
    } else {
        printf("The length of the word is odd.\n");
    }

    return 0;
}