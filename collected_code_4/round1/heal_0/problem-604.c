#include <stdio.h>
#include <string.h>

void reverse(char* str, int start, int end) {
    char temp;
    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void reverseWords(char* str) {
    int i, start = 0, length = strlen(str);
    for (i = 0; i <= length; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            reverse(str, start, i - 1);
            start = i + 1;
        }
    }
    reverse(str, 0, length - 1);
}

int main() {
    char str[] = "Hello World From C";
    reverseWords(str);
    printf("Reversed string is: %s\n", str);
    return 0;
}