#include <stdbool.h>

bool areElementsUnique(int list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (list[i] == list[j])
            {
                return false;
            }
        }
    }
    
    return true;
}