
#include <stdio.h>
#include <string.h>

int areAnagrams(char* str1, char* str2) {
    int count[256] = {0};
    int length1 = strlen(str1);
    int length2 = strlen(str2);

    if (length1 != length2)
        return 0;

    for (int i = 0; i < length1; i++) {
        count[str1[i]]++;
        count[str2[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] != 0)
            return 0;
    }

    return 1;
}

void findAnagrams(char* word, char** wordList, int listSize) {
    for (int i = 0; i < listSize; i++) {
        if (areAnagrams(word, wordList[i])) {
            printf("%s\n", wordList[i]);
        }
    }
}

int main() {
    char* word = "listen";
    char* wordList[] = {"enlist", "silent", "inlets", "banana"};
    int listSize = sizeof(wordList) / sizeof(wordList[0]);

    findAnagrams(word, wordList, listSize);

    return 0;
}
