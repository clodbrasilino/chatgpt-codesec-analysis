#include <stdio.h>
#include <string.h>

const int ASCII_SIZE = 256;

char getMinOccurringChar(char *str){
    /* Possible weaknesses found:
     *  variable-sized object may not be initialized except with an empty initializer
     */
    int count[ASCII_SIZE] = {0};
    int n = strlen(str);
    for (int i = 0; i < n; i++)
        count[(unsigned char)str[i]]++;

    int min = n + 1;
    char c = '\0';
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (count[i] > 0 && count[i] < min) {
            min = count[i];
            c = i;
        }
    }

    return c;
}

void removeChar(char *s, char c){
    int j = 0;
    for (int i = 0; s[i]; i++)
        if (s[i] != c)
            s[j++] = s[i];

    s[j] = '\0';
}

int main(){
    char str[] = "hello world";
    char minOccChar = getMinOccurringChar(str);
    removeChar(str, minOccChar);
    printf("%s\n", str);
    return 0;
}