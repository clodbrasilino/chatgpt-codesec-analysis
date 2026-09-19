#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_k_length_words(char *str, int k) {
    int len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (!result) return NULL;
    result[0] = '\0';
    
    int i = 0;
    while (i < len) {
        int j = i;
        while (j < len && str[j] != ' ') j++;
        int word_len = j - i;
        if (word_len != k) {
            strcat(result, str + i);
            if (j < len) strcat(result, " ");
        }
        i = j + 1;
    }
    
    return result;
}

int main() {
    char str[] = "this is a test string with some words of length four and five";
    int k = 4;
    char *result = remove_k_length_words(str, k);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}