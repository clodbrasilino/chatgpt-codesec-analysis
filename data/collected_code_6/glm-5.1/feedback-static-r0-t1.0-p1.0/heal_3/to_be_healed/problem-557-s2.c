#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toggle_case(char *str, size_t max_len) {
    if (str == NULL) {
        return;
    }
    size_t i = 0;
    while (i < max_len && str[i] != '\0') {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
        i++;
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
    size_t len = strcspn(buffer, "\n");
    if (len < sizeof(buffer)) {
        buffer[len] = '\0';
    }
    toggle_case(buffer, len);
    printf("%s\n", buffer);
    return 0;
}