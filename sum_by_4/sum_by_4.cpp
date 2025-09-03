#include <c7x.h>

#pragma FUNCTION_OPTIONS(problem_function, "--opt_level=1")
int problem_function(int arg)
{
    /* code here ... */
    return 0;
}

int sum_by_4(int *ptr, int length)
{
    __int4 sum_i4 = __int4(0);
    __int4 *ptr_i4 = (__int4 *)ptr;
    int i;

    /* iterate length/4 times to sum the values from *ptr_i4 into sum_i4 */
    for (i = 0; i < length/4; i++)
        sum_i4 += *ptr_i4++;

    /* add in last (length % 4) values from *ptr_sv */
    __vpred m_vp = __mask_int((unsigned) (length % 4));
    sum_i4 += __select(m_vp, *ptr_i4, __int4(0));

    /* sum the 4 values in sum_i4 and return it */
    int sum = 0;
    for (i = 0; i < 4; i++)
        sum += sum_i4.s[i];

    return sum;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#ifdef __C7X_HOSTEM_
#endif
    return sum_by_4(arr, sizeof(arr)/sizeof(arr[0]));
}
