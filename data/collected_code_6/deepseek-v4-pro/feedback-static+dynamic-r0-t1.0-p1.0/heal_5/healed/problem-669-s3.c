#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define MAX_IP_LENGTH 256

static int is_valid_ipv4(const char *ip) {
    regex_t regex;
    int ret;
    int result;
    const char *pattern = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

    if (ip == NULL) {
        return 0;
    }

    if (strlen(ip) >= MAX_IP_LENGTH) {
        return 0;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
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
        nread--;
    }
    
    if (nread == 0) {
        printf("Empty input\n");
        free(ip);
        return EXIT_FAILURE;
    }
    
    if ((size_t)nread >= MAX_IP_LENGTH) {
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