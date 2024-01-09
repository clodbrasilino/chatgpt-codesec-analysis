#include <stdio.h>

void removeChars(char *str1, char *str2) {
    int count = 0;
    for (int i = 0; str1[i] != '\0'; i++) {
        int flag = 0;
        for (int j = 0; str2[j] != '\0'; j++) {
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
    char str1[100], str2[100];
    printf("Enter the first string: ");
    scanf("%s", str1);
    printf("Enter the second string: ");
    scanf("%s", str2);

    removeChars(str1, str2);
    printf("Modified string: %s\n", str1);

    return 0;
}