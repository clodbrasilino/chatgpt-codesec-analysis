#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

void remove_whitespace(char *str)
{
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    size_t read;
    size_t write;

    if (str == NULL) {
        return;
    }

    read = 0;
    write = 0;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (str[read] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (!isspace((unsigned char)str[read])) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            str[write] = str[read];
            write++;
        }
        read++;
    }
    str[write] = '\0';
}

int main(void)
{
    char text[] = "  Hello,   World! \t This is a\ntest.  ";

    printf("Before: \"%s\"\n", text);
    remove_whitespace(text);
    printf("After:  \"%s\"\n", text);

    return 0;
}