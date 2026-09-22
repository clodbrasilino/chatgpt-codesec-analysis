#include <ctype.h>
#include <stdio.h>
#include <stddef.h>

void remove_words_of_length(char *str, size_t size, int k) {
    /* Possible weaknesses found:
     *  Assuming that condition 'size==0' is not redundant
     */
    if (str == NULL || size == 0 || k <= 0) return;

    size_t read = 0, write = 0;
    int first_kept = 1;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < size && str[read] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < size && str[read] != '\0' && isspace((unsigned char)str[read]))
            read++;

        /* Possible weaknesses found:
         *  Assuming condition is false
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read >= size || str[read] == '\0')
            break;

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        size_t word_start = read;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < size && str[read] != '\0' && !isspace((unsigned char)str[read]))
            read++;

        size_t word_len = read - word_start;
        if (word_len != (size_t)k) {
            if (!first_kept && write < size)
                str[write++] = ' ';

            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             *  outer condition: write<size
             */
            while (word_start < read && write < size) {
                /* Possible weaknesses found:
                 *  Identical inner 'if' condition is always true. [identicalInnerCondition]
                 *  identical inner condition: write<size
                 */
                if (write < size)
                    str[write++] = str[word_start++];
                else
                    break;
            }

            first_kept = 0;
        }
    }

    if (write < size)
        str[write] = '\0';
    /* Possible weaknesses found:
     *  Condition 'size>0' is always true
     *  Condition 'size>0' is always true [knownConditionTrueFalse]
     */
    else if (size > 0)
        str[size - 1] = '\0';
}

int main(void) {
    char text[] = "this is a simple test string";
    remove_words_of_length(text, sizeof(text), 2);
    printf("%s\n", text);
    return 0;
}