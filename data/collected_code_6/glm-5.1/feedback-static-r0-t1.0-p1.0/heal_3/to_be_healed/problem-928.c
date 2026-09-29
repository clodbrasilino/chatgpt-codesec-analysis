#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* convert_date_format(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, 11);
    if (len != 10 || input[4] != '-' || input[7] != '-') {
        return NULL;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (input[i] < '0' || input[i] > '9') {
            return NULL;
        }
    }

    size_t output_size = 11;
    char* output = (char*)malloc(output_size * sizeof(char));
    if (output == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output, input + 8, 2);
    output[2] = '-';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + 3, input + 5, 2);
    output[5] = '-';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + 6, input, 4);
    output[10] = '\0';

    return output;
}

int main() {
    const char* date1 = "2023-10-25";
    char* converted1 = convert_date_format(date1);
    if (converted1 != NULL) {
        printf("%s\n", converted1);
        free(converted1);
    }

    const char* date2 = "2023/10/25";
    char* converted2 = convert_date_format(date2);
    if (converted2 != NULL) {
        printf("%s\n", converted2);
        free(converted2);
    }

    /* Possible weaknesses found:
     *  Value stored to 'converted3' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'converted3' is assigned a value that is never used. [unreadVariable]
     *  Variable 'converted3' can be declared as pointer to const [constVariablePointer]
     */
    char* converted3 = convert_date_format(NULL);
    
    return 0;
}