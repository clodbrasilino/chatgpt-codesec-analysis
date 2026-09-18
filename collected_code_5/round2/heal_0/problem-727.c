#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

char* remove_special_characters(char* src) {
    regex_t regex;
    int reti;
    char* dst = malloc(strlen(src) + 1);
    char* pos = dst;

    reti = regcomp(&regex, "[A-Za-z0-9]", 0);
    if (reti) {
        fprintf(stderr, "Cannot compile regex\n");
        free(dst);
        return NULL;
    }

    while(*src) {
        reti = regexec(&regex, src, 0, NULL, 0);
        if(!reti) {
            *dst = *src;
            dst++;
        }
        src++;
    }

    *dst = '\0';
    regfree(&regex);
    return pos;
}

int main() {
    char str[] = "H#e@l$l%o^2345Wo^^&rld";
    char* res = remove_special_characters(str);
    if(res) {
        printf("Output: %s\n", res);
        free(res);
    }

    return 0;
}