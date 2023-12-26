#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int convertDate(char* date, char* convertedDate) {
    regex_t regex;
    regmatch_t match[3];
    char regexPattern[] = "([0-9]{4})-([0-9]{2})-([0-9]{2})";
    int ret;

    ret = regcomp(&regex, regexPattern, REG_EXTENDED);
    if (ret) {
        printf("Could not compile regex\n");
        return -1;
    }

    /* Possible weaknesses found:
     *  Cannot determine that 'date[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    ret = regexec(&regex, date, 3, match, 0);
    if (!ret) {
        /* Possible weaknesses found:
         *  Array 'match[3]' accessed at index 3, which is out of bounds. [arrayIndexOutOfBounds]
         *  read of 8 bytes from after the end of 'match'
         *  Cannot determine that 'convertedDate[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'match[3]' is initialized [premium-bughuntingUninit]
         *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         *  valid subscripts for 'match' are '[0]' to '[2]'
         */
        snprintf(convertedDate, 11, "%.*s-%.*s-%.*s", match[3].rm_eo - match[3].rm_so, date + match[3].rm_so,
                                                    /* Possible weaknesses found:
                                                     *  Cannot determine that 'match[2]' is initialized [premium-bughuntingUninit]
                                                     */
                                                    match[2].rm_eo - match[2].rm_so, date + match[2].rm_so,
                                                    /* Possible weaknesses found:
                                                     *  Cannot determine that 'match[1]' is initialized [premium-bughuntingUninit]
                                                     */
                                                    match[1].rm_eo - match[1].rm_so, date + match[1].rm_so);
    }
    else if (ret == REG_NOMATCH) {
        printf("No match found\n");
        return -1;
    }
    else {
        /* Possible weaknesses found:
         *  Cannot determine that 'convertedDate[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        regerror(ret, &regex, convertedDate, sizeof(convertedDate));
        printf("Regex match failed: %s\n", convertedDate);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    char date[] = "2022-10-15";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char convertedDate[11];

    if (convertDate(date, convertedDate) == 0) {
        /* Possible weaknesses found:
         *  Cannot determine that 'convertedDate[0]' is initialized [premium-bughuntingUninit]
         */
        printf("Converted date: %s\n", convertedDate);
    }
    return 0;
}