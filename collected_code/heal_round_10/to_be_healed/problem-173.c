#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 256

void removeNonAlphanumeric(char* str, int size) {
    if (!str || size <=0) {
        return;
    }

    int i = 0;
    int j = 0;
    while (str[i] && i<size) {
        if (isalnum((unsigned char)str[i])) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strnlen(str, MAX_SIZE - 1);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    }

    if (str[0] != '\0') {
        removeNonAlphanumeric(str, MAX_SIZE);
        printf("String after removing non-alphanumeric characters: %s\n", str);
    }
   
    return 0;
}
