#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool contains_all_vowels(const char *str) {
    bool vowels[5] = {false, false, false, false, false};
    const char *p = str;
    while (*p) {
        switch (*p) {
            case 'a': case 'A':
                vowels[0] = true;
                break;
            case 'e': case 'E':
                vowels[1] = true;
                break;
            case 'i': case 'I':
                vowels[2] = true;
                break;
            case 'o': case 'O':
                vowels[3] = true;
                break;
            case 'u': case 'U':
                vowels[4] = true;
                break;
        }
        p++;
    }
    for (int i = 0; i < 5; i++) {
        if (!vowels[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    const char *test_string = "A quick brown fox jumps over the lazy dog";
    if (contains_all_vowels(test_string)) {
        printf("The string contains all vowels.\n");
    } else {
        printf("The string does not contain all vowels.\n");
    }
    return 0;
}