#include <stdio.h>
#include <string.h>

int getMin(int x, int y) {
    return (x < y) ? x : y;
}

int getShortestCommonSupersequence(char* str1, char* str2, int len1, int len2) {
    int matrix[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++)
        for (int j = 0; j <= len2; j++)

            if (!i)
                matrix[i][j] = j;
            else if (!j)
                matrix[i][j] = i;
            else if (str1[i - 1] == str2[j - 1])
                matrix[i][j] = 1 + matrix[i - 1][j - 1];
            else
                matrix[i][j] = 1 + getMin(matrix[i - 1][j], matrix[i][j - 1]);

    return matrix[len1][len2];
}

int main() {
    char str1[100];
    char str2[100];

    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    str1[strlen(str1) - 1] = '\0';

    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);
    str2[strlen(str2) - 1] = '\0';

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    printf("Length of the shortest supersequence is %d\n",
           getShortestCommonSupersequence(str1, str2, len1, len2));
    return 0;
}