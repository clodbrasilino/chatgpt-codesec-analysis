#include <stdio.h>

void removeChars(char *str1, const char *str2) {
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

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str1[101], str2[101];
    printf("Enter the first string: ");
    /* Possible weaknesses found:
     *   It's unclear if the %s limit in the format string is small enough  (CWE-120). Check that the limit is sufficiently small, or use a different  input function.
     */
    scanf("%100s", str1);
    printf("Enter the second string: ");
    /* Possible weaknesses found:
     *   It's unclear if the %s limit in the format string is small enough  (CWE-120). Check that the limit is sufficiently small, or use a different  input function.
     */
    scanf("%100s", str2);

    removeChars(str1, str2);
    printf("Modified string: %s\n", str1);

    return 0;
}