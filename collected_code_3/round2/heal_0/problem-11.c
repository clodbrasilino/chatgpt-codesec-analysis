#include <stdio.h>
#include <string.h>

void removeChar(char *str, char c) {
    int len = strlen(str);
    int i, j = 0, k = len - 1;

    while (j < len && str[j] != c)
        j++;

    while (k >= 0 && str[k] != c)
        k--;

    if (j < len && k >= 0) {
        for (i = j; i < k; i++)
            str[i] = str[i + 1];

        str[i++] = str[k + 1];

        for (; i < len; i++)
            str[i] = str[i + 1];
    }
}

int main() {
    char str[100];
    char c;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    printf("Enter a character to remove: ");
    scanf("%c", &c);

    removeChar(str, c);

    printf("Result: %s\n", str);

    return 0;
}