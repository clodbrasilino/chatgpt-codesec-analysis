#include <stdio.h>
#include <string.h>

int countFlipsToAlternate(const char *str);

int main() {
    const char *testString = "0101001";
    int result = countFlipsToAlternate(testString);
    printf("Number of flips required: %d\n", result);
    return 0;
}

int countFlipsToAlternate(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int flipsStartingWith0 = 0, flipsStartingWith1 = 0;
    for (int i = 0; i < len; ++i) {
        if ((i % 2 == 0 && str[i] != '0') || (i % 2 != 0 && str[i] != '1')) {
            flipsStartingWith0++;
        } else if ((i % 2 == 0 && str[i] != '1') || (i % 2 != 0 && str[i] != '0')) {
            flipsStartingWith1++;
        }
    }
    return (flipsStartingWith0 < flipsStartingWith1) ? flipsStartingWith0 : flipsStartingWith1;
}