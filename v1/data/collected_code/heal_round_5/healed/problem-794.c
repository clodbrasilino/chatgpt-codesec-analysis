#include <stdio.h>
#include <string.h>

#define MAX_LEN 102

int matchString(const char* str, size_t len) {
    int i = 0;

    while (i < len - 2) {
        if (str[i]== 'a' && str[i + 2] == 'b') {
            return 1;
        }
        i++;
    }
    return 0;
}

int main() {
    char str[MAX_LEN];
    printf("Enter a string: ");
    if(fgets(str, MAX_LEN, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        size_t len = strnlen(str, MAX_LEN);
        int result = matchString(str, len);
        if (result == 1) {
            printf("String matches the pattern.\n");
        } else {
            printf("String does not match the pattern.\n");
        }
    }

    return 0;
}
