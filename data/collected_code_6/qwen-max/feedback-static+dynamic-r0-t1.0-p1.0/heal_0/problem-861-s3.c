#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool are_anagrams(const char *s1, const char *s2) {
    int count[256] = {0};
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if (len1 != len2) {
        return false;
    }

    for (int i = 0; i < len1; ++i) {
        count[s1[i]]++;
        count[s2[i]]--;
    }

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