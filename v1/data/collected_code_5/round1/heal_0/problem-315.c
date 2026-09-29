#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int getMaxLengthEvenWordLength(char* str) {
    int length = strlen(str);
    int max = 0;
    int counter = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] != ' ') {
            counter++;
        } else {
            if (counter % 2 == 0 && counter > max) {
                max = counter;
            }
            counter = 0;
        }
    }
    if (counter % 2 == 0 && counter > max) {
        max = counter;
    }
    return max;
}

int main() {
    char str[MAX_LEN];
    printf("Enter a string: ");
    fgets(str, MAX_LEN, stdin);
    str[strlen(str) - 1] = '\0';

    int maxLength = getMaxLengthEvenWordLength(str);

    printf("The maximum length of even word is: %d\n", maxLength);

    return 0;
}