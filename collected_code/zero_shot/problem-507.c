#include <stdio.h>
#include <string.h>

void removeSpecificWords(char list[][100], int size, char word[]) {
    int i, j, k;
    
    for (i = 0; i < size; i++) {
        if (strcmp(list[i], word) == 0) {
            for (j = i; j < size - 1; j++) {
                strcpy(list[j], list[j + 1]);
            }
            strcpy(list[size - 1], "");
            size--;
            i--;
        }
    }
}

int main() {
    char words[][100] = {"apple", "banana", "orange", "grape", "apple"};
    int size = sizeof(words) / sizeof(words[0]);
    
    removeSpecificWords(words, size, "apple");
    
    for (int i = 0; i < size; i++) {
        printf("%s\n", words[i]);
    }
    
    return 0;
}