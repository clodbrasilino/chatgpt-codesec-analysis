#include <stdbool.h>
#include <string.h>

bool isMadeOfAlternatingCharacters(const char *str) {
    int i = 0;
    int length = strlen(str);

    if (length != 2) {
        return false;
    }
    
    while (i < length - 1) {
        if (str[i] == str[i + 1]) {
            return false;
        }
        i++;
    }
    
    return true;
}

int main() {
    char *testString1 = "AB";
    char *testString2 = "AA";

    printf("%d\n", isMadeOfAlternatingCharacters(testString1));
    printf("%d\n", isMadeOfAlternatingCharacters(testString2));

    return 0;
}