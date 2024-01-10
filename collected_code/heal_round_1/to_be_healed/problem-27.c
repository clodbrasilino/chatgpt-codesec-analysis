#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void removeDigits(char *str) {
    char *i = str;
    char *j = str;
    
    /* Possible weaknesses found:
     *  Cannot determine that '*j' is initialized [premium-bughuntingUninit]
     */
    while (*j != '\0') {
        if (!isdigit(*j)) {
            /* Possible weaknesses found:
             *  write to string literal [-Wanalyzer-write-to-string-literal]
             */
            *i = *j;
            i++;
        }
        j++;
    }
    
    /* Possible weaknesses found:
     *  write to string literal [-Wanalyzer-write-to-string-literal]
     */
    *i = '\0';
}

void removeDigitsFromList(char **list, int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        removeDigits(list[i]);
    }
}

int main() {
    char *list[] = {"abc123", "def456", "ghi789", "jkl"};
    int size = sizeof(list) / sizeof(list[0]);
    
    removeDigitsFromList(list, size);
    
    for (int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }
    
    return 0;
}