#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int isEndingWithAlnum(const char* str) {
    regex_t regex;
    const char *pattern = "[A-Za-z0-9]$";
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    result = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        exit(1);
    }
    int result = isEndingWithAlnum(argv[1]);
    printf("Output: %s\n", result ? "TRUE" : "FALSE");
    
    return 0;
}