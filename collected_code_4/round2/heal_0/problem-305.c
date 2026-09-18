#include <stdio.h>
#include <string.h>

int match_words(char* words[], int size, char* word1, char* word2) {
    if(!words || size <= 0 || !word1 || !word2)
        return -1;

    int found1 = 0;
    int found2 = 0;

    for(int i=0; i<size; i++) {
        if(!words[i])
            continue;

        if(words[i][0] != 'p')
            continue;

        if(strcmp(words[i], word1) == 0)
            found1 = 1;

        if(strcmp(words[i], word2) == 0)
            found2 = 1;

        if(found1 && found2)
            return 1;
    }

    return 0;
}

int main() {
    char* words[] = {"pear", "apple", "banana", "peach", "grape"};
    int size = sizeof(words) / sizeof(words[0]);

    int result = match_words(words, size, "pear", "peach");

    if(result == 1)
        printf("Both words found.\n");
    else if(result == 0)
        printf("One or both words not found.\n");
    else
        printf("Invalid input.\n");

    return 0;
}