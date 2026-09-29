#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* replaceSpaces(const char *str) {
    int spaceCount = 0, i = 0, newLength;
    char *newStr;

    if (str == NULL) {
        return NULL;
    }

    while (str[i] != '\0') {
        if (str[i] == ' ') {
            spaceCount++;
        }
        i++;
    }

    newLength = i + (spaceCount * 2);
    newStr = (char *)malloc(newLength + 1);
    if (newStr == NULL) {
        return NULL;
    }

    i = 0;
    int j = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            newStr[j++] = '%';
            newStr[j++] = '2';
            newStr[j++] = '0';
        } else {
            newStr[j++] = str[i];
        }
        i++;
    }
    newStr[j] = '\0';

    return newStr;
}

int main() {
    const char input1[] = "My Name is Dawood";
    const char input2[] = "I am a Programmer";
    const char input3[] = "I love Coding";
    const char* inputs[] = {input1, input2, input3};
    
    for (int k = 0; k < 3; k++) {
        char *result = replaceSpaces(inputs[k]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            printf("Failed to allocate memory.\n");
        }
    }
    return 0;
}