#include <stdio.h>
#include <string.h>

void reverseString(char* str) {
    int length, i;
    char *begin_ptr, *end_ptr, temp;

    length = strlen(str);

    begin_ptr = str;
    end_ptr = str;

    for (i = 0; i < length - 1; i++)
        end_ptr++;

    for (i = 0; i < length / 2; i++) {
        temp = *end_ptr;
        *end_ptr = *begin_ptr;
        /* Possible weaknesses found:
         *  write to string literal [-Wanalyzer-write-to-string-literal]
         */
        *begin_ptr = temp;

        begin_ptr++;
        end_ptr--;
    }
}

void reverseStringList(char* str[], int size) {
    for(int i = 0; i < size; i++) {
        reverseString(str[i]);
    }
}

int main() {
    char* strList[] = {"Hello", "World", "C", "Programming"};
    int size = sizeof(strList) / sizeof(strList[0]);

    reverseStringList(strList, size);

    for(int i = 0; i < size; i++) {
        printf("%s\n", strList[i]);
    }

    return 0;
}