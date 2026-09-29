#include <stdio.h>
#define MAX_SIZE 100

int getLengthOfLongestWord(char str[]) {
    int maxLength = 0;
    int length = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            length++;
        } else {
            if (length > maxLength) {
                maxLength = length;
            }
            length = 0;
        }
    }

    if (length > maxLength) {
        maxLength = length;
    }

    return maxLength;
}

int main() {
    char str[MAX_SIZE];
    printf("Enter a sentence: ");
    fgets(str, MAX_SIZE, stdin);

    int length = getLengthOfLongestWord(str);

    printf("Length of the longest word is %d\n", length);

    return 0;
}