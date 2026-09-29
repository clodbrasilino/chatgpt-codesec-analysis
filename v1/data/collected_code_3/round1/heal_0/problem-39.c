#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

int canRearrange(char *str) {
    int count[NO_OF_CHARS] = {0};
    int i;

    for (i = 0; str[i]; i++)
        count[str[i]]++;

    int odd = 0;
    for (i = 0; i < NO_OF_CHARS; i++) {
        if (count[i] & 1)
            odd++;

        if (odd > 1)
            return 0;
    }

    return 1;
}

int main() {
    char str[] = "aab";
    if (canRearrange(str))
        printf("Can be rearranged\n");
    else
        printf("Cannot be rearranged\n");

    return 0;
}