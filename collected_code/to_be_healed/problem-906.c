#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memcpy'
  */

#define MAX_MATCHES 10
#define MAX_YEAR_LENGTH 4
#define MAX_MONTH_LENGTH 2
#define MAX_DATE_LENGTH 2

int extract_date_from_url(const char *url, char *year, char *month, char *date) {
    regex_t regex;
    regmatch_t match[MAX_MATCHES];
    /* Possible weaknesses found:
     *  initializer-string for array of 'char' is too long
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char year_regex[MAX_YEAR_LENGTH + 1] = "[0-9]{4}";
    /* Possible weaknesses found:
     *  initializer-string for array of 'char' is too long
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char month_regex[MAX_MONTH_LENGTH + 1] = "[0-9]{2}";
    /* Possible weaknesses found:
     *  initializer-string for array of 'char' is too long
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char date_regex[MAX_DATE_LENGTH + 1] = "[0-9]{2}";

    int status = regcomp(&regex, "/([0-9]{4})/([0-9]{2})/([0-9]{2})/", REG_EXTENDED);

    if (status != 0) {
        printf("Failed to compile regex\n");
        return -1;
    }

    status = regexec(&regex, url, MAX_MATCHES, match, 0);

    if (status == 0) {
        /* Possible weaknesses found:
         *  Cannot determine that 'match[1]' is initialized [premium-bughuntingUninit]
         */
        int year_length = match[1].rm_eo - match[1].rm_so;
        /* Possible weaknesses found:
         *  Cannot determine that 'match[2]' is initialized [premium-bughuntingUninit]
         */
        int month_length = match[2].rm_eo - match[2].rm_so;
        /* Possible weaknesses found:
         *  Cannot determine that 'match[3]' is initialized [premium-bughuntingUninit]
         */
        int date_length = match[3].rm_eo - match[3].rm_so;
        
        if (year_length > MAX_YEAR_LENGTH || month_length > MAX_MONTH_LENGTH || date_length > MAX_DATE_LENGTH) {
            printf("Invalid date format\n");
            return -1;
        }
        
        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
         *  incompatible implicit declaration of built-in function 'memcpy' [-Wbuiltin-declaration-mismatch]
         *  include '<string.h>' or provide a declaration of 'memcpy'
         *  implicit declaration of function 'memcpy' [-Wimplicit-function-declaration]
         *  Cannot determine that 'match[1]' is initialized [premium-bughuntingUninit]
         *  Cannot determine that 'year[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        memcpy(year, url + match[1].rm_so, year_length);
        year[year_length] = '\0';
        
        /* Possible weaknesses found:
         *  Cannot determine that 'month[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'match[2]' is initialized [premium-bughuntingUninit]
         *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
         */
        memcpy(month, url + match[2].rm_so, month_length);
        month[month_length] = '\0';
        
        /* Possible weaknesses found:
         *  Cannot determine that 'date[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'match[3]' is initialized [premium-bughuntingUninit]
         *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
         */
        memcpy(date, url + match[3].rm_so, date_length);
        date[date_length] = '\0';
    } else if (status == REG_NOMATCH) {
        printf("No date found in URL\n");
        return -1;
    } else {
        printf("Regex match failed\n");
        return -1;
    }
    
    regfree(&regex);
    return 0;
}

int main() {
    const char *url = "https://example.com/2022/03/15/some-page.html";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char year[MAX_YEAR_LENGTH + 1];
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char month[MAX_MONTH_LENGTH + 1];
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char date[MAX_DATE_LENGTH + 1];
    
    int result = extract_date_from_url(url, year, month, date);
    
    if (result == 0) {
        /* Possible weaknesses found:
         *  Cannot determine that 'year[0]' is initialized [premium-bughuntingUninit]
         */
        printf("Year: %s\n", year);
        /* Possible weaknesses found:
         *  Cannot determine that 'month[0]' is initialized [premium-bughuntingUninit]
         */
        printf("Month: %s\n", month);
        /* Possible weaknesses found:
         *  Cannot determine that 'date[0]' is initialized [premium-bughuntingUninit]
         */
        printf("Date: %s\n", date);
    }
    
    return 0;
}