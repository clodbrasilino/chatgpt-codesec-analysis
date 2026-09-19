#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_anagram(const char *s1, const char *s2) {
    int count[256] = {0};
    int len1 = strlen(s1), len2 = strlen(s2);
    
    if (len1 != len2) return 0;
    
    for (int i = 0; i < len1; ++i) {
        count[tolower(s1[i])]++;
        count[tolower(s2[i])]--;
    }
    
    for (int i = 0; i < 256; ++i) {
        if (count[i] != 0) return 0;
    }
    
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as const array [constParameter]
 */
void find_anagrams(const char *target, char *list[], int list_size) {
    for (int i = 0; i < list_size; ++i) {
        if (is_anagram(target, list[i])) {
            printf("%s\n", list[i]);
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'target' can be declared as const array [constVariable]
     */
    char target[] = "listen";
    char *words[] = {"enlists", "google", "inlets", "banana"};
    int list_size = sizeof(words)/sizeof(words[0]);
    
    find_anagrams(target, words, list_size);
    
    return 0;
}