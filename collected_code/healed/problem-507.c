#include <stdio.h>
#include <string.h>

void removeSpecificWords(char list[][100], int *size, const char word[]) {
    int i, j;

    for (i = 0; i < *size; ) {
        if (strcmp(list[i], word) == 0) {
            for (j = i; j < *size - 1; j++) {
                strncpy(list[j], list[j + 1], 100 - 1);
                list[j][100 - 1] = '\0';
            }
            strncpy(list[*size - 1], "", 100 - 1);
            list[*size - 1][100 - 1] = '\0';
            (*size)--;
        } else {
            i++;
        }
    }
}

int main() {
    char words[][100] = {"apple", "banana", "orange", "grape", "apple"};
    int size = sizeof(words) / sizeof(words[0]); 

    removeSpecificWords(words, &size, "apple");
  
    for (int i = 0; i < size; i++) {
        printf("%s\n", words[i]);
    }
    
    return 0;
}