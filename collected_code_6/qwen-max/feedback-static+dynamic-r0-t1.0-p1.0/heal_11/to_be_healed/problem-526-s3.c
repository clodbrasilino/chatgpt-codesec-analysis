#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize(char *str) {
    if (str == NULL || *str == '\0') return;
    size_t len = strnlen(str, 256);
    for (size_t i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         *  Condition 'i>0' is always true [knownConditionTrueFalse]
         *  Assuming that condition 'i==0' is not redundant
         *  Condition 'i>0' is always true
         */
        if (i == 0 || (i > 0 && isspace((unsigned char)str[i - 1]))) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
    for (ssize_t i = len - 1; i >= 0; --i) {
        if (i + 1 == len || (i + 1 < len && isspace((unsigned char)str[i + 1]))) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        capitalize(input);
        printf("Capitalized: %s\n", input);
    } else {
        fprintf(stderr, "Input error\n");
    }
    return 0;
}