#include <stdio.h>
#include <regex.h>

int isIpAddressValid(char *ipAddress) {
    regex_t regex;
    int result;
    
    char *pattern = "^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'ipAddress[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    result = regexec(&regex, ipAddress, 0, NULL, 0);
    regfree(&regex);
    
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char ipAddress[20];
    
    printf("Enter an IP address: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'ipAddress[0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
    scanf("%s", ipAddress);
    
    if (isIpAddressValid(ipAddress)) {
        printf("Valid IP address\n");
    } else {
        printf("Invalid IP address\n");
    }
    
    return 0;
}