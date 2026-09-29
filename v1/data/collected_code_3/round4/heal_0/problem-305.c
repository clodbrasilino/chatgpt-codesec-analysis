#include <stdio.h>
#include <string.h>

int match_words(char* word1, char* word2, char** list, int size) {
    int i;
    int match1 = 0, match2 = 0;
    for(i = 0; i < size; i++) {
        if(list[i][0] == 'p' || list[i][0] == 'P') {
            if(strcmp(list[i], word1) == 0) {
                match1 = 1;
            }
            if(strcmp(list[i], word2) == 0) {
                match2 = 1;
            }
        }
    }
    return match1 && match2;
}

int main() {
    char* list[] = {"pear", "apple", "peach", "grape", "pineapple"};
    int size = sizeof(list) / sizeof(list[0]);
    if(match_words("pear", "peach", list, size)) {
        printf("Both words are in the list and start with 'p'\n");
    } else {
        printf("Both words are not in the list or do not start with 'p'\n");
    }
    return 0;
}