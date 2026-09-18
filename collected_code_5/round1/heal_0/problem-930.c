#include<stdio.h>
#include<regex.h>

int match(const char *str) {
    regex_t re;
    if(regcomp(&re, "a[b]*", REG_EXTENDED|REG_NOSUB) != 0) {
        return 0; 
    }
    int status = regexec(&re, str, (size_t) 0, NULL, 0);
    regfree(&re); 
    if(status != 0) {
        return 0; 
    } 
    return 1; 
}

int main() {
    const char* str = "abbb";
    if(match(str)) {
        printf("The string %s matches the pattern!\n",str);
    } else {
        printf("The string %s does not match the pattern.\n",str);
    }
    return 0;
}