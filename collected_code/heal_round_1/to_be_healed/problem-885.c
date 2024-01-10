#include <stdio.h>
#include <stdbool.h>

bool isIsomorphic(char* str1, char* str2) {
    int map1[256] = {0};
    int map2[256] = {0};

    /* Possible weaknesses found:
     *  Cannot determine that 'str1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; str1[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'str2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (map1[str1[i]] == 0 && map2[str2[i]] == 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'str1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'str2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            map1[str1[i]] = str2[i];
            /* Possible weaknesses found:
             *  Cannot determine that 'str1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'str2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            map2[str2[i]] = str1[i];
        /* Possible weaknesses found:
         *  Cannot determine that 'str1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'str2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        } else if (map1[str1[i]] != str2[i] || map2[str2[i]] != str1[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    char str1[] = "egg";
    char str2[] = "add";

    if (isIsomorphic(str1, str2)) {
        printf("The strings are isomorphic.\n");
    } else {
        printf("The strings are not isomorphic.\n");
    }

    return 0;
}