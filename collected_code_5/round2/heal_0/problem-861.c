#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_SIZE 4

int compare(const void* a, const void* b) { 
    return *(char*)a - *(char*)b; 
}

int isAnagram(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if(len1 != len2)
        return 0;

    qsort(str1, len1, sizeof(char), compare);
    qsort(str2, len2, sizeof(char), compare);

    if(!memcmp(str1, str2, len1 * sizeof(char)))
        return 1;

    return 0;
}

void findAnagrams(char* str, char** list, int size) {
    for(int i = 0; i < size; i++) {
        if(isAnagram(str, list[i]))
            printf("%s ", list[i]);
    }
    printf("\n");
}

int main() {
    char* list[LIST_SIZE] = {"cat", "dog", "act", "god"};
    char str[] = "tac";

    findAnagrams(str, list, LIST_SIZE);

    return 0;
}