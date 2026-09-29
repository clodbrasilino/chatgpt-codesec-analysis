#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseString(char* str) {
    int length, i;
    char temp;
    char *begin_ptr, *end_ptr;

    length = strlen(str);

    begin_ptr = str;
    end_ptr = str + length - 1;

    for (i = 0; i < length / 2; i++) {
        temp = *end_ptr;
        *end_ptr = *begin_ptr;
        *begin_ptr = temp;

        begin_ptr++;
        end_ptr--;
    }
}

void reverseStringList(char** str, int size) {
    for(int i = 0; i < size; i++) {
        char* temp = malloc(strlen(str[i]) + 1);
        strcpy(temp, str[i]);
        reverseString(temp);
        str[i] = temp;
    }
}

int main() {
    char *strList[] = {"Hello", "World", "C", "Programming"};
    int size = sizeof(strList) / sizeof(strList[0]);

    reverseStringList(strList, size);

    for(int i = 0; i < size; i++) {
        printf("%s\n", strList[i]);
        free(strList[i]);
    }

    return 0;
}