#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool are_anagrams(const char *s1, const char *s2) {
    int count[256] = {0};
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; ++i) {
        count[(unsigned char)s1[i]]++;
        count[(unsigned char)s2[i]]--;
    }
    if (s1[strlen(s1)] != '\0' || s2[strlen(s2)] != '\0') return false;
    for (int i = 0; i < 256; ++i) {
        if (count[i] != 0) {
            return false;
        }
    }
    return true;
}

void find_anagrams(const char *target, char **list, int list_size) {
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