
int sum_by_scalar(int *ptr, int length)
{
    int sum = 0;
    int i;

    for (i = 0; i < length; i++)
        sum += *ptr++;

    return sum;
}
