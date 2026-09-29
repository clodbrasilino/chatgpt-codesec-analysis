#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isSubstringPresent(char *substring, char *strings[], int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'substring[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'strings[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (strstr(strings[i], substring) != NULL) {
            return true;
        }
    }
    return false;
}

int main() {
    char *substring = "substring";
    char *strings[] = {"string1", "string2", "string3"};

    if (isSubstringPresent(substring, strings, sizeof(strings) / sizeof(strings[0]))) {
        printf("Substring is present\n");
    } else {
        printf("Substring is not present\n");
    }

    return 0;
}