#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_ipv4(const char *ip) {
    regex_t regex;
    int ret;
    int result;
    const char *pattern = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return 0;
    }

    ret = regexec(&regex, ip, 0, NULL, 0);
    
    result = (ret == 0) ? 1 : 0;
    
    regfree(&regex);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip[256];
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    
    printf("Enter an IP address: ");
    if (fgets(ip, sizeof(ip), stdin) != NULL) {
        len = 0;
        for (i = 0; i < sizeof(ip); i++) {
            if (ip[i] == '\0') {
                len = i;
                break;
            }
        }
        
        if (i == sizeof(ip) && ip[sizeof(ip) - 1] != '\0') {
            ip[sizeof(ip) - 1] = '\0';
            len = sizeof(ip) - 1;
        }
        
        if (len > 0 && ip[len - 1] == '\n') {
            ip[len - 1] = '\0';
            len--;
        }
        
        if (len == 0) {
            printf("Empty input\n");
            return EXIT_FAILURE;
        }
        
        if (is_valid_ipv4(ip)) {
            printf("%s is a valid IPv4 address\n", ip);
        } else {
            printf("%s is not a valid IPv4 address\n", ip);
        }
    }
    
    return EXIT_SUCCESS;
}