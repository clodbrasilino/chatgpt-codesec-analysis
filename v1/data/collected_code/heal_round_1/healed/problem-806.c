#include <stdio.h>
#include <string.h>
#include <ctype.h>

int maxRunOfUppercase(const char *str) {
    int currRun = 0;
    int maxRun = 0;
    int i;

    for (i = 0; str[i]; i++) {
        if (isupper((unsigned char)str[i])) {
            currRun++;
            if (currRun > maxRun) {
                maxRun = currRun;
            }
        } else {
            currRun = 0;
        }
    }

    return maxRun;
}

int main() {
    const char str[] = "HelloWORLD";
    int maxRun = maxRunOfUppercase(str);

    printf("Maximum run of uppercase characters: %d\n", maxRun);

    return 0;
}