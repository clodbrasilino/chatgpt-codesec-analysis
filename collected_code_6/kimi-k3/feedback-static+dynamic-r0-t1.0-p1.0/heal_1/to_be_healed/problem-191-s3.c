#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_30_days(const char *month) {
    if (month == NULL || *month == '\0') {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[16];
    size_t i = 0;
    
    /* Possible weaknesses found:
     *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
     */
    while (month[i] != '\0' && i < sizeof(normalized) - 1) {
        normalized[i] = (char)tolower((unsigned char)month[i]);
        i++;
    }
    normalized[i] = '\0';
    
    if (strcmp(normalized, "april") == 0 ||
        strcmp(normalized, "june") == 0 ||
        strcmp(normalized, "september") == 0 ||
        strcmp(normalized, "november") == 0) {
        return 1;
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[32];
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    if (has_30_days(input)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}