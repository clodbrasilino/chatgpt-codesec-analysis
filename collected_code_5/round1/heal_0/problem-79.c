#include <stdio.h>
#include <string.h>

int check_word_length(const char* word) {
    return strlen(word) % 2;
}

int main() {
    const char *str = "Hello, world";
    if (check_word_length(str))
        printf("The length of the word is odd\n");
    else
        printf("The length of the word is not odd\n");
    return 0;
}