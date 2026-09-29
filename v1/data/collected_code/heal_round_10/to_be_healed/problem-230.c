#include <stdio.h>
#include <string.h>

#define SIZE 101
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void replaceSpaces(char *str, const char ch, size_t max_size) {
    size_t count = MIN(max_size, SIZE - 1);
    for (size_t i = 0; i < count; i++) {
        if (str[i] == ' ') {
            str[i] = ch;
        }
    }
    str[count] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[SIZE] = "";
    char ch = '\0';
    size_t len = 0;

    printf("Enter a string: ");
    if(fgets(str, sizeof(str), stdin) != NULL) {
        len = strcspn(str, "\n");
        if(len < SIZE) {
            str[len] = '\0';
        }
    }

    printf("Enter the character to replace spaces with: ");
    if(scanf(" %c", &ch) != 1) {
        printf("Error reading character.\n");
        return 1;
    }

    /* Possible weaknesses found:
     *   Check buffer boundaries if used in a loop including recursive loops  (CWE-120, CWE-20).
     */
    while(getchar() != '\n');

    size_t strLen = strnlen(str, SIZE);
    
    if(strLen) {
        replaceSpaces(str, ch, strLen);
    }

    printf("Modified string: %s\n", str);

    return 0;
}