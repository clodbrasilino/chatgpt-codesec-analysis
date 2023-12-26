#include <stdio.h>

void toggleCase(char str[]) {
    int i = 0;

    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (str[i] != '\0') {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (str[i] >= 'a' && str[i] <= 'z') {
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            str[i] = str[i] - 32; // Convert lowercase to uppercase
        }
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        else if (str[i] >= 'A' && str[i] <= 'Z') {
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            str[i] = str[i] + 32; // Convert uppercase to lowercase
        }
        i++;
    }
}

int main() {
    char str[] = "Hello, World!";
  
    printf("Before toggling: %s\n", str);
  
    toggleCase(str);
  
    printf("After toggling: %s\n", str);
  
    return 0;
}