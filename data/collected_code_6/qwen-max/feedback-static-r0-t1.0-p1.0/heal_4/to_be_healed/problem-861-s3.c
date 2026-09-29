#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool are_anagrams(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return false;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);
    if (len1 != len2) return false;

    int count[256] = {0};
    for (size_t i = 0; i < len1; ++i) {
        count[(unsigned char)s1[i]]++;
        count[(unsigned char)s2[i]]--;
    }
    
    for (int i = 0; i < 256; ++i) {
        if (count[i] != 0) {
            return false;
        }
    }
    return true;
}

void find_anagrams(const char *target, char **list, int list_size) {
    if (target == NULL || list == NULL) return;
    for (int i = 0; i < list_size; ++i) {
        if (are_anagrams(target, list[i])) {
            printf("%s\n", list[i]);
        }
    }
}

int main() {
    char *words[] = {"listen", "silent", "enlist", "hello", "olleh", "test"};
    int list_size = sizeof(words) / sizeof(words[0]);
    const char *target = "silent";

    find_anagrams(target, words, list_size);

    return 0;
}