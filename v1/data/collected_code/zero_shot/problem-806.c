#include <stdio.h>
#include <string.h>

int maxRunOfUppercase(char *str) {
    int currRun = 0;
    int maxRun = 0;
    int i;

    for (i = 0; i < strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
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
    char str[] = "HelloWORLD";
    int maxRun = maxRunOfUppercase(str);
    
    printf("Maximum run of uppercase characters: %d\n", maxRun);

    return 0;
}