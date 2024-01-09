#include <stdbool.h>

bool matchString(const char* string) {
    if (string == NULL) {
        return false;
    }

    bool foundA = false;
    int countB = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == 'a') {
            foundA = true;
        } else if (string[i] == 'b') {
            if (!foundA) {
                return false;
            }
            countB++;
        } else {
            return false;
        }
    }

    return countB > 0;
}