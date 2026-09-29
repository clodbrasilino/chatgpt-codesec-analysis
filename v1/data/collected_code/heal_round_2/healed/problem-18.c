#include <stdio.h>
#include <string.h>

void removeChars(char *str1, const char *str2) {
    int count = 0;

    for (int i = 0; i < strlen(str1); i++) {
        int flag = 0;

        for (int j = 0; j < strlen(str2); j++) {
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
    char str1[101], str2[101];
    printf("Enter the first string: ");
    fgets(str1, 101, stdin);
    str1[strcspn(str1, "\n")] = 0;
    printf("Enter the second string: ");
    fgets(str2, 101, stdin);
    str2[strcspn(str2, "\n")] = 0;

    removeChars(str1, str2);
    printf("Modified string: %s\n", str1);

    return 0;
}