#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longestCommonPrefix(char** strs, int size) {
    if (size == 0) {
        return strdup("");
    }
  
    char* prefix = strdup(strs[0]);
    if (prefix == NULL){
        return NULL;
    }

    int i, j;
  
    for (i = 1; i < size; i++) {
        j = 0;
        while (prefix[j] != '\0' && strs[i][j] != '\0' && prefix[j] == strs[i][j]) {
            j++;
        }
      
        prefix[j] = '\0';
    }
  
    return prefix;
}

int main() {
    char* strings[] = {"apple", "application", "app", "aptitude"};
    int size = sizeof(strings) / sizeof(strings[0]);

    char* commonPrefix = longestCommonPrefix(strings, size);

    if (commonPrefix != NULL) {
        printf("Longest common prefix: %s\n", commonPrefix);
        free(commonPrefix);
    }
  
    return 0;
}