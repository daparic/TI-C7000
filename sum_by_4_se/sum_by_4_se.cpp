#include <c7x.h>

int sum_by_4_se(int *ptr, int length)
{
    __int4 sum_i4 = __int4(0);
    int i;

    /* Configure SE parameters */
    __SE_TEMPLATE_v1 se_params = __gen_SE_TEMPLATE_v1();
    se_params.VECLEN = __SE_VECLEN_4ELEMS;
    se_params.ELETYPE = __SE_ELETYPE_32BIT;
    se_params.DIMFMT = __SE_DIMFMT_1D;
    se_params.ICNT0 = length;

    /* Open SE0 with base address ptr, and those parameters */
    __SE0_OPEN(ptr, se_params);

    int loop_count = length/4;
    if (length % 4)
        loop_count += 1;

    /* iterate length/4 times to sum the values from *ptr into sum_i4 */
    // for (i = 0; i < length/4; i++)
    for (i = 0; i < loop_count; i++)
        sum_i4 += __SE0ADV(int4);

#if 0
    /* Add in last (length % 4) values from *ptr */
    __vpred m_vp = __mask_int((unsigned) (length % 4));
    sum_i4 += __select(m_vp, __SE0(int4), __int4(0));
#endif
#if 0
    sum_i4 += __SE0(int4);
#endif

    /* Close SE0 */
    __SE0_CLOSE();

    /* sum the 4 values in sum_i4 and return it */
    int sum = 0;
    for (i = 0; i < 4; i++)
        sum += sum_i4.s[i];

    return sum;
} 

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    return sum_by_4_se(arr, sizeof(arr)/sizeof(arr[0]));
}
