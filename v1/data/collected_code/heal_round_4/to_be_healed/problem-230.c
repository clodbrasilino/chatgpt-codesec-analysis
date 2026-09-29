#include <stdio.h>
#include <string.h>

#define SIZE 101

void replaceSpaces(char *str, const char ch, size_t max_size) {
    for (size_t i = 0; i < max_size && str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = ch;
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[SIZE] = "";
    char ch = '\0';
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    
    printf("Enter the character to replace spaces with: ");
    /* Possible weaknesses found:
     *   Check buffer boundaries if used in a loop including recursive loops  (CWE-120, CWE-20).
     */
    while ((getchar()) != '\n');
    scanf("%c", &ch);
    replaceSpaces(str, ch, sizeof(str));
    printf("Modified string: %s\n", str);
    return 0;
}