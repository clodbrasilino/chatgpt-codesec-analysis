#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areIsomorphic(char *str1, char *str2) {
    int m = strlen(str1), n = strlen(str2);
    if (m != n) return 0;
    
    int map1[256] = {0}, map2[256] = {0};
    
    for (int i = 0; i < m; ++i) {
        if (!map1[(unsigned char)str1[i]]) map1[(unsigned char)str1[i]] = str2[i];
        if (!map2[(unsigned char)str2[i]]) map2[(unsigned char)str2[i]] = str1[i];
        
        if (map1[(unsigned char)str1[i]] != str2[i] || map2[(unsigned char)str2[i]] != str1[i])
            return 0;
    }
    
    return 1;
}

int main() {
    char str1[] = "egg";
    char str2[] = "add";
    
    if (areIsomorphic(str1, str2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }
    
    return 0;
}