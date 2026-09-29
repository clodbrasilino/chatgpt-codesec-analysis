#include <stdio.h>
#include <stddef.h>

int remove_negatives(int list[], size_t *size)
{
    if (list == NULL || size == NULL)
        return -1;

    size_t write = 0;
    size_t total = *size;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (size_t read = 0; read < total; read++)
    {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (list[read] >= 0)
        {
            if (write < total)
            {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                list[write] = list[read];
            }
            write++;
        }
    }

    *size = write;
    return 0;
}

int main(void)
{
    int numbers[] = {1, -2, 3, -4, 5, -6};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    if (remove_negatives(numbers, &count) != 0)
        return 1;

    for (size_t i = 0; i < count; i++)
        printf("%d ", numbers[i]);
    printf("\n");

    return 0;
}