#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void removeDigits(char *str) {
    if(str == NULL)
        return;

    char *i = str;
    char *j = str;

    while (*j != '\0') {
        if (!isdigit((unsigned char)*j)) {
            *i = *j;
            i++;
        }
        j++;
    }

    *i = '\0';
}

void removeDigitsFromList(char **list, int size) {
    if(list == NULL)
        return;

    for (int i = 0; i < size; i++) {
        if(list[i] != NULL)
            removeDigits(list[i]);
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char list[4][10] = {"abc123", "def456", "ghi789", "jkl"};
    int size = sizeof(list) / sizeof(list[0]);

    removeDigitsFromList((char **)list, size);

    for (int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}