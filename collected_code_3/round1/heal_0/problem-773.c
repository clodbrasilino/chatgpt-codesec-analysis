#include <stdio.h>
#include <string.h>

void find_substring(char* str, char* sub) {
    int len = strlen(str);
    int sub_len = strlen(sub);
    for(int i = 0; i <= len - sub_len; i++) {
        int j;
        for(j = 0; j < sub_len; j++) {
            if(str[i + j] != sub[j]) {
                break;
            }
        }
        if(j == sub_len) {
            printf("Substring found at position %d\n", i + 1);
        }
    }
}

int main() {
    char str[100], sub[100];
    printf("Enter a string: ");
    gets(str);
    printf("Enter a substring to find: ");
    gets(sub);
    find_substring(str, sub);
    return 0;
}