#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isConcatenation(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if(len1 % len2 != 0) {
        return false;
    }

    for(int i = 0; i < len1; i += len2) {
        if(strncmp(str1 + i, str2, len2) != 0) {
            return false;
        }
    }

    return true;
}


int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("\nUsage: prog string1 string2\n");
        return 1;
    }
    
    if(isConcatenation(argv[1], argv[2])) {
        printf("%s is a concatenation of %s\n", argv[1], argv[2]);
    } else {
        printf("%s is not a concatenation of %s\n", argv[1], argv[2]);
    }

    return 0;
}