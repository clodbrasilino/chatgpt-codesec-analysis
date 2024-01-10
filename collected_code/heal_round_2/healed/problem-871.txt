#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areRotations(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    int size1 = strlen(str1);
    int size2 = strlen(str2);

    if (size1 != size2) {
        return false;
    }

    char* temp = (char*)malloc((2*size1+1) * sizeof(char));
    if(temp == NULL) {
        return false;
    }

    strncpy(temp, str1, size1);
    temp[size1] = '\0';
    strncat(temp, str1, size1);

    bool result = (strstr(temp, str2) != NULL);

    free(temp);

    return result;
}

int main() {
    const char str1[] = "ABCD";
    const char str2[] = "CDAB";
    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other\n");
    } else {
        printf("Strings are not rotations of each other\n");
    }

    return 0;
}