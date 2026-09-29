#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void replaceWithColon(char *str) {
    const char *pattern = "[ ,.]";
    regex_t reg;

    if (regcomp(&reg, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation error.\n");
        return;
    }

    int index = 0;
    while(index < strlen(str)) {
        if(regexec(&reg, str+index, 0, NULL, 0) == 0) {
            str[index] = ':';
        }
        index++;
    }

    regfree(&reg);
}

int main() {
    char str[100] = "Hello, how are you. I am fine.";

    printf("Before replace: %s\n", str);
    replaceWithColon(str);
    printf("After replace: %s\n", str);

    return 0;
}