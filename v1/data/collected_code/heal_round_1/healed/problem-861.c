#include <stdio.h>
#include <string.h>

int areAnagrams(const char* str1, const char* str2) {
    int count[256] = {0};

    if (str1 == NULL || str2 == NULL || strlen(str1) != strlen(str2))
        return 0;

    for (int i = 0; str1[i] && str2[i]; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] != 0)
            return 0;
    }

    return 1;
}

void findAnagrams(const char* word, const char* wordList[], int listSize) {
    if (word == NULL || wordList == NULL || listSize <= 0)
        return;

    for (int i = 0; i < listSize; i++) {
        if (wordList[i] != NULL && areAnagrams(word, wordList[i])) {
            printf("%s\n", wordList[i]);
        }
    }
}

int main() {
    const char* word = "listen";
    const char* wordList[] = {"enlist", "silent", "inlets", "banana"};
    int listSize = sizeof(wordList) / sizeof(wordList[0]);

    findAnagrams(word, wordList, listSize);

    return 0;
}