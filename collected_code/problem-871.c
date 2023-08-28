#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areRotations(char* str1, char* str2) {
    int size1 = strlen(str1);
    int size2 = strlen(str2);

    if (size1 != size2) {
        return false;
    }

    char* temp = strcat(str1, str1);

    if (strstr(temp, str2) != NULL) {
        return true;
    }

    return false;
}

int main() {
    char str1[] = "ABCD";
    char str2[] = "CDAB";

    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other");
    }
    else {
        printf("Strings are not rotations of each other");
    }

    return 0;
}