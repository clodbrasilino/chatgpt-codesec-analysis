#include <stdio.h>
#include <stdbool.h>

bool is_first_last_equal(char str[]) {
    int len = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[len]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (str[len] != '\0') {
        len++;
    }
    if (len <= 1) {
        return true;
    }
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'str[len-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    return (str[0] == str[len - 1]);
}