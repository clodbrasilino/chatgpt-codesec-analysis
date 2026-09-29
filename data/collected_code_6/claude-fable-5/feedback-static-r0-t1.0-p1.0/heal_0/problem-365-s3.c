int count_digits(long long number)
{
    int count = 1;

    while (number <= -10 || number >= 10) {
        number /= 10;
        count++;
    }

    return count;
}