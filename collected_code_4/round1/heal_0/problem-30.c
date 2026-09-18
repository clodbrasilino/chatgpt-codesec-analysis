#include<stdio.h>
#include<string.h>

int countSubstr(char str[], int len) {
    int count = 0;
    for (int i = 0; i < len; i++)
        for (int j = i+1; j < len; j++)
            if (str[i] == str[j])
                count++;
    return count;
}

int main() {
    char str[] = "hello";
    int len = strlen(str);
    printf("Number of substrings starting and ending with same character is %d\n", countSubstr(str, len));
    return 0;
}