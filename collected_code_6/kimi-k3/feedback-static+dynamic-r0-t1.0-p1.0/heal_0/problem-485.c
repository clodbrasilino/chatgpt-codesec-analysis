#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_palindrome(int num)
{
    if (num < 0)
        return false;
    
    int original = num;
    int reversed = 0;
    
    while (num > 0)
    {
        if (reversed > (INT_MAX - num % 10) / 10)
            return false;
        
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    
    return original == reversed;
}

int find_largest_palindrome(const int arr[], size_t size, bool *found)
{
    if (arr == NULL || size == 0 || found == NULL)
    {
        if (found != NULL)
            *found = false;
        return 0;
    }
    
    int largest = 0;
    *found = false;
    
    for (size_t i = 0; i < size; i++)
    {
        if (is_palindrome(arr[i]))
        {
            if (!(*found) || arr[i] > largest)
            {
                largest = arr[i];
                *found = true;
            }
        }
    }
    
    return largest;
}

int main(void)
{
    int arr[] = {121, 232, 545, 999, 123, 454};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    bool found = false;
    
    int result = find_largest_palindrome(arr, size, &found);
    
    if (found)
        printf("Largest palindromic number: %d\n", result);
    else
        printf("No palindromic number found\n");
    
    return 0;
}