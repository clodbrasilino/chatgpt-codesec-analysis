#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0 || *strs == NULL) 
        return strdup("");

    char *prefix = strdup(strs[0]);
    int i, j;
    for (i = 0; i < strlen(prefix); i++) {
        for (j = 1; j < strsSize; j++) {
            if (prefix[i] != strs[j][i]) {
                prefix[i] = 0;
                return prefix;
            }
        }
    }
    return prefix;
}

int main(){
    int strsSize = 3;
    char* strs[] = { "flower","flow","flight"};
    char* prefix = longestCommonPrefix(strs, strsSize);
    printf("%s", prefix);
    free(prefix); 
    return 0;
}