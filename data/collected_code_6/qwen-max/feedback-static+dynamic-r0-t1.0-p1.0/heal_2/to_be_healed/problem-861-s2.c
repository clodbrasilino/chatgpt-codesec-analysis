#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool areAnagrams(const char *str1, const char *str2) {
    if (!str1 || !str2) return false;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len2 = strlen(str2);
    if (len1 != len2) return false;

    int count[256] = {0};
    for (int i = 0; i < len1; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }
    for (int i = 0; i < 256; i++) {
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