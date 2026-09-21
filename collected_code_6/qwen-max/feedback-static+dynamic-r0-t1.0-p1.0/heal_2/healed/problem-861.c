#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int is_anagram(const char *s1, const char *s2) {
    int count[256] = {0};
    size_t len1 = 0, len2 = 0;
    
    while (s1[len1] != '\0') {
        if (!isascii(s1[len1])) break;
        len1++;
    }
    while (s2[len2] != '\0') {
        if (!isascii(s2[len2])) break;
        len2++;
    }

    if (len1 != len2) return 0;

    for (size_t i = 0; i < len1; ++i) {
        count[tolower((unsigned char)s1[i])]++;
        count[tolower((unsigned char)s2[i])]--;
    }

    for (int i = 0; i < 256; ++i) {
        if (count[i] != 0) return 0;
    }

    return 1;
}

void find_anagrams(const char *target, const char *list[], int list_size) {
    for (int i = 0; i < list_size; ++i) {
        if (is_anagram(target, list[i])) {
            printf("%s\n", list[i]);
        }
    }
}

int main() {
    const char target[] = "listen";
    const char *words[] = {"enlists", "google", "inlets", "banana"};
    int list_size = sizeof(words)/sizeof(words[0]);

    find_anagrams(target, words, list_size);

    return 0;
}