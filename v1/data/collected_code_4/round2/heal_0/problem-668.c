#include <stdio.h>
#include <string.h>

void replaceMultipleOccurence(char str[]) {
    int n = strlen(str);
    int j = 0;

    for (int i = 1; i < n; i++) {
        if (str[i] != str[j]) {
            j++;
            str[j] = str[i];
        }
    }
    str[j+1] = '\0';
}

int main() {
    char str[] = "helloooooooodddoo";
    replaceMultipleOccurence(str);
    printf("%s\n", str);
    return 0;
}