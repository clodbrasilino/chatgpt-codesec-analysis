#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATE_SIZE 11
#define DATE_INPUT_FORMAT "%10s"

void convertDateFormat(char* date) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char temp[DATE_SIZE];
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if(!date || strlen(date) != DATE_SIZE - 1) {
        return;
    }
    memset(temp, 0, DATE_SIZE);

    date[DATE_SIZE - 1] = '\0';

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(temp, date + 8, 2);
    temp[2] = '-';

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(temp + 3, date + 5, 2);
    temp[5] = '-';

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(temp + 6, date, 4);
    temp[DATE_SIZE - 1] = '\0';

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(date, temp, DATE_SIZE);
    date[DATE_SIZE - 1] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char date[DATE_SIZE];

    printf("Enter date in yyyy-mm-dd format: ");

    /* Possible weaknesses found:
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function. If the scanf format is influenceable by an  attacker, it's exploitable.
     */
    if(scanf(DATE_INPUT_FORMAT, date) != 1) {
        return 1;
    }

    date[DATE_SIZE - 1] = '\0';

    convertDateFormat(date);

    printf("Converted date: %s\n", date);

    return 0;
}