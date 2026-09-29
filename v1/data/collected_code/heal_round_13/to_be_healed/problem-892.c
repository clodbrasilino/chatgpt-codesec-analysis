#include <stdio.h>
#include <string.h>

#define MAX_STR_SIZE 100

void removeMultipleSpaces(char *str) {
    int i, j = 0;
    int flag = 0;
    size_t length = strnlen(str, MAX_STR_SIZE);

    if (length >= MAX_STR_SIZE) {
        length = MAX_STR_SIZE - 1;
	}

    for (i = 0; i < length; i++) {
        if (str[i] == ' ' && i + 1 < length && str[i + 1] == ' ') {
            flag = 1;
        } else {
            if (flag == 1) {
                str[j++] = ' ';
                flag = 0;
            }
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_STR_SIZE + 1] = {0};

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    removeMultipleSpaces(str);

    printf("String after removing multiple spaces: %s\n", str);

    return 0;
}