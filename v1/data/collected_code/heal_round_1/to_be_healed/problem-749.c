#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    const char **str1 = (const char **)a;
    const char **str2 = (const char **)b;
    /* Possible weaknesses found:
     *  Cannot determine that 'str1' is initialized [premium-bughuntingUninit]
     *   Unless checked, the resulting number can exceed the expected range  (CWE-190). If source untrusted, check both minimum and maximum, even if the  input had no minus sign (large numbers can roll over into negative number;  consider saving to an unsigned value if that is intended).
     *  Cannot determine that 'str2' is initialized [premium-bughuntingUninit]
     */
    return atoi(*str1) - atoi(*str2);
}

void sortStrings(char *strings[], int numStrings) {
    /* Possible weaknesses found:
     *  Cannot determine that 'strings[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    qsort(strings, numStrings, sizeof(char *), compare);
}

int main() {
    char *strings[] = {"10", "2", "5", "1", "7"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);

    sortStrings(strings, numStrings);

    for (int i = 0; i < numStrings; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}