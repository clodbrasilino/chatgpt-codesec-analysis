#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areIsomorphic(const char *str1, const char *str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    const char str1[] = "egg";
    const char str2[] = "add";
    
    if (areIsomorphic(str1, str2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }
    
    return 0;
}