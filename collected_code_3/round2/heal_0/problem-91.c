#include <stdio.h>
#include <string.h>

int checkSubstring(char *substring, char *stringList[], int listSize) {
    for(int i = 0; i < listSize; i++) {
        if(strstr(stringList[i], substring) != NULL) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char *stringList[] = {"Hello", "World", "C", "Programming"};
    char *substring = "World";
    int listSize = sizeof(stringList) / sizeof(stringList[0]);

    if(checkSubstring(substring, stringList, listSize)) {
        printf("Substring found\n");
    } else {
        printf("Substring not found\n");
    }

    return 0;
}