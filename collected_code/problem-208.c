#include <regex.h>

int checkPrecision(float decimal) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[+-]?[0-9]+([.][0-9]{1,2})?$", REG_EXTENDED);
    if (reti) {
        return -1;
    }

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%.2f", decimal);

    reti = regexec(&regex, buffer, 0, NULL, 0);
    regfree(&regex);

    return reti == 0 ? 1 : 0;
}