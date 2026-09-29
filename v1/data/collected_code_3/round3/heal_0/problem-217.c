#include <stdio.h>
#include <string.h>

char firstRepeatedChar(char* str) {
    int count[256] = {0};
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (count[str[i]] == 1)
            return str[i];
        else
            count[str[i]]++;
    }
    return '\0';
}

int main() {
    char str[] = "interview";
    char result = firstRepeatedChar(str);
    if (result != '\0')
        printf("The first repeated character is %c", result);
    else
        printf("No repeated characters");
    return 0;
}