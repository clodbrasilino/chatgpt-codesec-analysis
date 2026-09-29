#include <stdio.h>
#include <limits.h>

#define SEEN_SIZE ((UCHAR_MAX + 1 + CHAR_BIT - 1) / CHAR_BIT)

int all_unique(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[SEEN_SIZE] = {0};
    const unsigned char *p;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    unsigned char c;
    /* Possible weaknesses found:
     *  The scope of the variable 'index' can be reduced. [variableScope]
     */
    int index;
    /* Possible weaknesses found:
     *  The scope of the variable 'bit' can be reduced. [variableScope]
     */
    unsigned int bit;
    unsigned char mask;

    if (str == NULL) {
        return 0;
    }

    p = (const unsigned char *)str;

    while (*p != '\0') {
        c = *p;
        index = c / CHAR_BIT;
        if (index < 0 || index >= SEEN_SIZE) {
            return 0;
        }
        bit = (unsigned int)c % CHAR_BIT;
        mask = (unsigned char)(1u << bit);
        if ((seen[index] & mask) != 0) {
            return 0;
        }
        seen[index] |= mask;
        p++;
    }

    return 1;
}

int main(void) {
    const char *test1 = "abc";
    const char *test2 = "aba";
    const char *test3 = "";
    const char *test4 = NULL;

    printf("%d\n", all_unique(test1));
    printf("%d\n", all_unique(test2));
    printf("%d\n", all_unique(test3));
    printf("%d\n", all_unique(test4));

    return 0;
}