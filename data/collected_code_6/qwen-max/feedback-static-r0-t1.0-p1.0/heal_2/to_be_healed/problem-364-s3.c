#include <stdio.h>
#include <string.h>

int minFlipsToAlternate(const char *s) {
    int flipStartWith0 = 0, flipStartWith1 = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (i % 2 == 0) {
            if (s[i] != '0') flipStartWith0++;
            if (s[i] != '1') flipStartWith1++;
        } else {
            if (s[i] != '1') flipStartWith0++;
            if (s[i] != '0') flipStartWith1++;
        }
    }
    return flipStartWith0 < flipStartWith1 ? flipStartWith0 : flipStartWith1;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 's1' can be declared as const array [constVariable]
     */
    char s1[] = "001";
    /* Possible weaknesses found:
     *  Variable 's2' can be declared as const array [constVariable]
     */
    char s2[] = "010101";
    /* Possible weaknesses found:
     *  Variable 's3' can be declared as const array [constVariable]
     */
    char s3[] = "000111";

    printf("%d\n", minFlipsToAlternate(s1));
    printf("%d\n", minFlipsToAlternate(s2));
    printf("%d\n", minFlipsToAlternate(s3));

    return 0;
}