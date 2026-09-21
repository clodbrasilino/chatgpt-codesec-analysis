#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool areAnagrams(const char *str1, const char *str2) {
    if (!str1 || !str2) return false;
    size_t len1 = strnlen(str1, 256);
    size_t len2 = strnlen(str2, 256);
    if (len1 != len2) return false;

    int count[256] = {0};
    for (size_t i = 0; i < len1; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }
    for (size_t i = 0; i < 256; i++) {
        if (count[i] != 0) return false;
    }
    return true;
}

void findAnagrams(const char *target, const char **list, int listSize) {
    for (int i = 0; i < listSize; i++) {
        if (areAnagrams(target, list[i])) {
            printf("%s\n", list[i]);
        }
    }
}

int main() {
    const char *list[] = {"cinema", "iceman", "dog", "god", "listen", "silent"};
    int listSize = sizeof(list) / sizeof(list[0]);

    const char *target = "iceman";
    findAnagrams(target, list, listSize);

    return 0;
}