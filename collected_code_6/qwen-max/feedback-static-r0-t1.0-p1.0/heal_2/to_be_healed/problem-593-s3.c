#include <stdio.h>
#include <string.h>

void remove_leading_zeros(char *ip) {
    char *part = strtok(ip, ".");
    while (part) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(part) > 1 && part[0] == '0') {
            /* Possible weaknesses found:
             *  Variable 'end' can be declared as pointer to const [constVariablePointer]
             */
            char *end = strchr(part, '\0');
            memmove(part, part + 1, end - (part + 1) + 1);
        }
        part = strtok(NULL, ".");
    }
}

int main() {
    char ip_address[] = "0192.0168.01.01";
    remove_leading_zeros(ip_address);
    printf("%s\n", ip_address);
    return 0;
}