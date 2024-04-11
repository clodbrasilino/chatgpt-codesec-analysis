#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkVowels(char str[]) {
    int i;
    bool flag[5] = {false};

    for(i = 0; str[i]; i++) {
        if(str[i] == 'a' || str[i] == 'A')
            flag[0] = true;
        else if(str[i] == 'e' || str[i] == 'E')
            flag[1] = true;
        else if(str[i] == 'i' || str[i] == 'I')
            flag[2] = true;
        else if(str[i] == 'o' || str[i] == 'O')
            flag[3] = true;
        else if(str[i] == 'u' || str[i] == 'U')
            flag[4] = true;
    }

    for(i = 0; i < 5; i++) {
        if(flag[i] == false)
            return false;
    }

    return true;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    if(checkVowels(str))
        printf("The string contains all vowels.\n");
    else
        printf("The string does not contain all vowels.\n");

    return 0;
}