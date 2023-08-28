#include <stdbool.h>

bool areAllCharactersUnique(char* str) {
    int charCount[256] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        if (charCount[str[i]] > 0) {
            return false;
        }
        charCount[str[i]]++;
    }

    return true;
}