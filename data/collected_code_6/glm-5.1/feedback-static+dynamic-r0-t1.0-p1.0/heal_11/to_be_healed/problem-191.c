#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower[16];
    /* Possible weaknesses found:
     *  Assignment 'max_len=sizeof(lower)-1', assigned value is 15
     */
    size_t max_len = sizeof(lower) - 1;

    /* Possible weaknesses found:
     *  Assuming that condition 'i<max_len' is not redundant
     */
    for (size_t i = 0; i < max_len; i++) {
        /* Possible weaknesses found:
         *  Array 'month[1]' accessed at index 14, which is out of bounds. [arrayIndexOutOfBounds]
         *  Array index out of bounds
         *  Assuming condition is false
         */
        if (month[i] == '\0') {
            lower[i] = '\0';
            
            if (strcmp(lower, "april") == 0 || strcmp(lower, "jun") == 0 ||
                strcmp(lower, "june") == 0 || strcmp(lower, "sep") == 0 ||
                strcmp(lower, "september") == 0 || strcmp(lower, "nov") == 0 ||
                strcmp(lower, "november") == 0) {
                return 1;
            }
            
            return 0;
        }
        lower[i] = (char)tolower((unsigned char)month[i]);
    }

    lower[max_len] = '\0';
    return 0;
}

int main(void) {
    printf("%d\n", has_30_days("April"));
    printf("%d\n", has_30_days("JUN"));
    printf("%d\n", has_30_days("January"));
    printf("%d\n", has_30_days(NULL));
    printf("%d\n", has_30_days(""));
    return 0;
}