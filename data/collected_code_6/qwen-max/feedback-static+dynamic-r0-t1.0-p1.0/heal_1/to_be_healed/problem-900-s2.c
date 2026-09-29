#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int starts_with_number(const char *str, int number) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[12];
    /* Possible weaknesses found:
     * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
     */
    sprintf(num_str, "%d", number);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return strncmp(str, num_str, strlen(num_str)) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <string> <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_string = argv[1];
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int input_number = atoi(argv[2]);

    if (starts_with_number(input_string, input_number)) {
        printf("The string '%s' starts with the number %d.\n", input_string, input_number);
    } else {
        printf("The string '%s' does not start with the number %d.\n", input_string, input_number);
    }

    return EXIT_SUCCESS;
}