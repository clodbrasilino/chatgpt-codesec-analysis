#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeWord(char* string, char* word) {
    char* result;
    int i, cnt = 0;
    int len1 = strlen(string);
    int len2 = strlen(word);
  
    for (i = 0; i <= len1 - len2; i++) {
        if (strstr(&string[i], word) == &string[i]) {
            cnt++;
            i += len2 - 1;
        }
    }
  
    result = (char*)malloc(i + cnt + 1);
    if(!result) {
        return NULL;
    }
    i = 0;
    while (*string) {
        if (strstr(string, word) == string) {
            string += len2;
        }
        else {
            result[i++] = *string++;
        }
    }
    result[i] = '\0';
    return result;
}

int main() {
    char string[100];
    char word[100];
    printf("Enter a string: ");
    fgets(string, sizeof(string), stdin);
    string[strlen(string) - 1] = '\0';
    printf("Enter a word to remove from the string: ");
    fgets(word, sizeof(word), stdin);
    word[strlen(word) - 1] = '\0';
    char* result = removeWord(string, word);
    if(result) {
        printf("String after removing '%s': %s\n", word, result);
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}