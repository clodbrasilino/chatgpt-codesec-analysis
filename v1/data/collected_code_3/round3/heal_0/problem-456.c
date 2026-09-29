#include <stdio.h>
#include <string.h>

void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverseStringList(char** list, int size) {
    for (int i = 0; i < size; i++) {
        reverseString(list[i]);
    }
}

int main() {
    char* list[] = {"Hello", "World", "C", "Programming"};
    int size = sizeof(list) / sizeof(list[0]);

    reverseStringList(list, size);

    for (int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}