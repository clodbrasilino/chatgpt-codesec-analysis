#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define MAX_IP_LENGTH 256
#define REGEX_ERRBUF_SIZE 256

static int is_valid_ipv4(const char *ip) {
    regex_t regex;
    int ret;
    int result;
    size_t ip_len;
    const char *pattern = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

    if (ip == NULL) {
        return 0;
    }

    ip_len = strnlen(ip, MAX_IP_LENGTH);
    if (ip_len >= MAX_IP_LENGTH || ip[ip_len] != '\0') {
        return 0;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[REGEX_ERRBUF_SIZE];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        regfree(&regex);
        return 0;
    }

    ret = regexec(&regex, ip, 0, NULL, 0);
    
    result = (ret == 0) ? 1 : 0;
    
    regfree(&regex);
    
    if (ret != 0 && ret != REG_NOMATCH) {
        return 0;
    }
    
    return result;
}

int main(void) {
    char *ip = NULL;
    size_t bufsize = 0;
    ssize_t nread;
    size_t ip_len;
    
    printf("Enter an IP address: ");
    
    nread = getline(&ip, &bufsize, stdin);
    if (nread == -1) {
        free(ip);
        if (errno == ENOMEM) {
            fprintf(stderr, "Memory allocation failed\n");
        } else {
            printf("Error reading input\n");
        }
        return EXIT_FAILURE;
    }
    
    if (nread > 0 && ip[nread - 1] == '\n') {
        ip[nread - 1] = '\0';
    }
    
    ip_len = strnlen(ip, MAX_IP_LENGTH);
    if (ip_len == 0) {
        printf("Empty input\n");
        free(ip);
        return EXIT_FAILURE;
    }
    
    if (ip_len >= MAX_IP_LENGTH) {
        printf("Input too long\n");
        free(ip);
        return EXIT_FAILURE;
    }
    
    if (is_valid_ipv4(ip)) {
        printf("%s is a valid IPv4 address\n", ip);
    } else {
        printf("%s is not a valid IPv4 address\n", ip);
    }
    
    free(ip);
    return EXIT_SUCCESS;
}