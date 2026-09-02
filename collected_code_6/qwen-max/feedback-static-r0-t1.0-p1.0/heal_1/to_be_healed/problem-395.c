#include <stdio.h>
#include <string.h>
#include <limits.h>

char findFirstNonRepeatedChar(const char *str) {
    int count[CHAR_MAX + 1] = {0};
    int index[CHAR_MAX + 1];
    int minIdx = INT_MAX;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; str[i]; ++i) {
        if (count[(unsigned char)str[i]] == 0) {
            index[(unsigned char)str[i]] = i;
        }
        count[(unsigned char)str[i]]++;
    }

    for (int i = 0; i <= CHAR_MAX; ++i) {
        /* Possible weaknesses found:
         *  Uninitialized variable: index [uninitvar]
         *  Uninitialized variable: index
         */
        if (count[i] == 1 && index[i] < minIdx) {
            minIdx = index[i];
        }
    }

    return minIdx == INT_MAX ? '\0' : str[minIdx];
}

int main() {
    const char *str = "programming";
    char result = findFirstNonRepeatedChar(str);
    if (result != '\0') {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No non-repeated character found.\n");
    }
    return 0;
}