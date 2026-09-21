#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower_month[32];
    size_t len = 0;
    
    while (month[len] != '\0') {
        len++;
        if (len >= sizeof(lower_month)) {
            break;
        }
    }

    size_t i;
    for (i = 0; i < len && i < sizeof(lower_month) - 1; i++) {
        lower_month[i] = tolower((unsigned char)month[i]);
    }
    lower_month[i] = '\0';

    if (strcmp(lower_month, "february") == 0) {
        return 1;
    }

    return 0;
}

int main(void) {
    const char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December",
        "february", "FEBRUARY", "Feb", "", NULL
    };

    for (int i = 0; months[i] != NULL; i++) {
        printf("%s: %s\n", months[i], has_28_days(months[i]) ? "has 28 days" : "does not have 28 days");
    }

    return 0;
}