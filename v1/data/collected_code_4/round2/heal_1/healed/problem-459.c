#include <stdio.h>
#include <regex.h>
#include <string.h>

void remove_uppercase(char* str)
{
    regex_t regex;
    int ret;
    char newstr[100] = "";

    ret = regcomp(&regex, "[A-Z]+", 0);
    if (ret) {
        printf("Failed to compile regex\n");
        return;
    }
    
    int offset = 0;
    regmatch_t pmatch;
    while (1) {
        ret = regexec(&regex, str + offset, 1, &pmatch, 0);
        if (ret == REG_NOMATCH) {
            strncat(newstr, str + offset, strlen(str) - offset + 1);
            break;
        } else if (ret != 0) {
            char msgbuf[100];
            regerror(ret, &regex, msgbuf, sizeof(msgbuf));
            printf("Regex match failed: %s\n", msgbuf);
            return;
        } else {
            strncat(newstr, str + offset, pmatch.rm_so);
            offset += pmatch.rm_eo;
        }
    }

    strncpy(str, newstr, strlen(newstr) + 1);
    regfree(&regex);
}

int main() {
    char str[] = "HelloWorld";
    remove_uppercase(str);
    printf("%s\n", str);
    return 0;
}