#include <stdio.h>
#include <string.h>

void convertDateFormat(char* date) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char temp[11];
    /* Possible weaknesses found:
     *  Cannot determine that 'date[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     *  Cannot determine that 'temp[0]' is initialized [premium-bughuntingUninit]
     */
    strncpy(temp, date, 2); // Extract day
    temp[2] = '-';
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(temp + 3, date + 5, 2); // Extract month
    temp[5] = '-';
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(temp + 6, date + 0, 4); // Extract year
    temp[10] = '\0';

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(date, temp); // Copy back to original string
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char date[11] = "yyyy-mm-dd";
    printf("Enter date in yyyy-mm-dd format: ");
    /* Possible weaknesses found:
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
    scanf("%s", date);

    convertDateFormat(date);
    printf("Converted date: %s\n", date);

    return 0;
}