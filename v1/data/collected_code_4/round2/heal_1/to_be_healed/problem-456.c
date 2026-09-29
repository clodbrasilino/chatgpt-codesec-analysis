#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char* str) {
    int len = strlen(str);
    int start = 0, end = len - 1;
    char temp;

    while(start < end) {
        temp = str[start];
        /* Possible weaknesses found:
         *  write to string literal [-Wanalyzer-write-to-string-literal]
         */
        str[start] = str[end];
        /* Possible weaknesses found:
         *  write to string literal [-Wanalyzer-write-to-string-literal]
         */
        str[end] = temp;
        start++;
        end--;
    }
}

void reverseStrings(char** strList, int count) {
    for(int i = 0; i < count; i++) {
        reverseString(strList[i]);
    }
}

int main() {
    char* stringlist[] = {"Hello", "World", "Example"};
    int count = sizeof(stringlist) / sizeof(stringlist[0]);

    reverseStrings(stringlist, count);

    for(int i = 0; i < count; i++) {
        printf("%s\n", stringlist[i]);
    }

    return 0;
}
