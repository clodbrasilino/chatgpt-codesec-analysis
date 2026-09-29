#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

void remove_whitespace(char *str, size_t max_len)
{
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    size_t read;
    size_t write;

    if (str == NULL || max_len == 0) {
        return;
    }

    read = 0;
    write = 0;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < max_len && str[read] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (!isspace((unsigned char)str[read])) {
            if (write < max_len - 1) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                str[write] = str[read];
                write++;
            } else {
                break;
            }
        }
        read++;
    }

    if (write < max_len) {
        str[write] = '\0';
    } else {
        str[max_len - 1] = '\0';
    }
}

int main(void)
{
    char text[] = "  Hello,   World! \t This is a\ntest.  ";

    printf("Before: \"%s\"\n", text);
    remove_whitespace(text, sizeof(text));
    printf("After:  \"%s\"\n", text);

    return 0;
}