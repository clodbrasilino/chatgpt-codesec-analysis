#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void removeChars(char *str1, const char *str2) {
    int str2_len = strnlen(str2, BUFFER_SIZE);
    int str1_len = strnlen(str1, BUFFER_SIZE);
    int count = 0;

    for (int i = 0; i < str1_len; i++) {
        int flag = 0;

        for (int j = 0; j < str2_len; j++) {
            if (str1[i] == str2[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            str1[count++] = str1[i];
        }
    }
    str1[count] = '\0';
}

int main() {
    char str1[BUFFER_SIZE], str2[BUFFER_SIZE];

    printf("Enter the first string: ");
    fgets(str1, BUFFER_SIZE, stdin);
    str1[strcspn(str1, "\n")] = 0;

    printf("Enter the second string: ");
    fgets(str2, BUFFER_SIZE, stdin);
    str2[strcspn(str2, "\n")] = 0;

    removeChars(str1, str2);
    printf("Modified string: %s\n", str1);
    
    return 0;
}
