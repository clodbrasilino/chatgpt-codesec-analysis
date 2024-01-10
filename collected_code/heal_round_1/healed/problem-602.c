#include <stdio.h>

char findFirstRepeatedChar(const char *string) {
    int count[256] = {0};

    for (int i = 0; string[i] != '\0'; i++) {
        if (count[(unsigned char)string[i]] == 1)
            return string[i];

        count[(unsigned char)string[i]]++;
    }

    return '\0'; 
}

int main() {
    char string[] = "example";
    char result = findFirstRepeatedChar(string);

    printf("The first repeated character is: %c\n", result);

    return 0;
}
