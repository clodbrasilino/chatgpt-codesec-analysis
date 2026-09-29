#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toggle_case(char *str, size_t len) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; i < len && str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    toggle_case(buffer, strlen(buffer));
    printf("%s\n", buffer);
    return 0;
}