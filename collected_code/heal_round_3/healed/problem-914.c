#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool isMadeOfAlternatingCharacters(const char *str, size_t size) {
    size_t i = 0;

    if (size < 1) {
        return false;
    }
    
    while (i < size - 1) {
        if (str[i] == str[i + 1]) {
            return false;
        }
        i++;
    }
    
    return true;
}

int main() {
    char testString1[] = "AB";
    char testString2[] = "AA";

    printf("%d\n", isMadeOfAlternatingCharacters(testString1, sizeof(testString1) - 1));
    printf("%d\n", isMadeOfAlternatingCharacters(testString2, sizeof(testString2) - 1));

    return 0;
}