#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkPrecision(float decimal) {
    regex_t regex;
    int reti;
    size_t maxLen = 20;
    char *buffer = malloc(maxLen);
    if(buffer == NULL) {
        return -1;
    }

    reti = regcomp(&regex, "^[+-]?[0-9]+([.][0-9]{1,2})?$", REG_EXTENDED);
    if (reti) {
        free(buffer);
        return -1;
    }

    snprintf(buffer, maxLen, "%.2f", decimal);

    reti = regexec(&regex, buffer, 0, NULL, 0);
    regfree(&regex);
    free(buffer);

    return reti == 0 ? 1 : 0;
}

int main() {
    float decimal = 3.14;
    printf("%d\n", checkPrecision(decimal));
    return 0;
}