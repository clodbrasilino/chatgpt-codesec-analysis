#include <stdio.h>
#include <string.h>
#include <ctype.h>

void to_lower_case(char *str) {
    for (char *p = str; *p; p++) {
        *p = tolower((unsigned char)*p);
    }
}

int main() {
    char str[] = "ConVeRt tO LoWeR CaSe";
    to_lower_case(str);
    printf("%s\n", str);
    return 0;
}