#include <stdio.h>
#include <string.h>
#include <limits.h>

char findMaxOccurringChar(const char *str) {
    int count[256] = {0};
    int i, max = 0;
    char result;

    for (i = 0; str[i]; ++i)
        ++count[str[i]];

    for (i = 0; i < 256; ++i) {
        if (count[i] > max) {
            max = count[i];
            result = (char)i;
        }
    }

    return result;
}

int main() {
    const char *input = "test string";
    char max_char = findMaxOccurringChar(input);
    printf("The maximum occurring character is: %c\n", max_char);
    return 0;
}