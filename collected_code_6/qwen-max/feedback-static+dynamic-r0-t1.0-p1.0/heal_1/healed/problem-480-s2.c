#include <stdio.h>
#include <string.h>

char findMaxOccurringChar(const char *str) {
    int count[256] = {0};
    int max = 0;
    int result = 0;

    if (str[0] == '\0') return result;

    for (int i = 0; str[i]; ++i) {
        unsigned char c = (unsigned char)str[i];
        count[c]++;
        if (max < count[c]) {
            max = count[c];
            result = c;
        }
    }

    return (char)result;
}

int main() {
    const char *str = "example string with characters";
    printf("Max occurring character is: %c\n", findMaxOccurringChar(str));
    return 0;
}