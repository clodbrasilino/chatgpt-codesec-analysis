
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0 || *strs == NULL) 
        return "";

    int i, j;
    for (i = 0; i < strlen(strs[0]); i++) {
        for (j = 1; j < strsSize; j++) {
            if (strs[0][i] != strs[j][i]) {
                strs[0][i] = 0;
                return strs[0];
            }
        }
    }
    return strs[0];
}

int main(){
    int strsSize = 3;
    char* strs[] = { "flower","flow","flight"};
    char* prefix = longestCommonPrefix(strs, strsSize);
    printf("%s", prefix);
    return 0;
}