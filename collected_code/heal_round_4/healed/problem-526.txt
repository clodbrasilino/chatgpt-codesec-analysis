#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STR_LEN 101

void capitalizeFirstAndLastLetters(char *str) {
    if (str == NULL) 
        return;

    int len = strlen(str);

    if (len >= MAX_STR_LEN) 
        return;

    for (int i=0; i < len; i++) {
        if (i == 0 || str[i - 1] == ' ') {
            str[i] = (char)toupper((unsigned char)str[i]);
        }
    }

    for (int i = 0; i < len; i++) {
        if (isalpha((unsigned char)str[i]) && (i == len - 1 || str[i + 1] == ' ')) {
            str[i] = (char)toupper((unsigned char)str[i]);
        }
    }
}

int main() {
    char str[MAX_STR_LEN] = {'\0'};

    printf("Enter a string: ");

    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        capitalizeFirstAndLastLetters(str);
        printf("Modified string: %s\n", str);
        return 0;
    }

    return -1;
}