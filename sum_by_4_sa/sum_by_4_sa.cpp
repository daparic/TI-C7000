#include <c7x.h>

int sum_by_4_sa(int *ptr, int length)
{
    __int4 sum_i4 = __int4(0);
    int i;

    /* Configure SA parameters */
    __SA_TEMPLATE_v1 sa_params = __gen_SA_TEMPLATE_v1();
    sa_params.VECLEN = __SA_VECLEN_4ELEMS;
    sa_params.DIMFMT = __SA_DIMFMT_1D;
    sa_params.ICNT0 = length;

    /* Open SA0 with those parameters */
    __SA0_OPEN(sa_params);

    /* iterate length/4 times to sum the values from *ptr into sum_i4 */
    for (i = 0; i < length/4; i++)
        sum_i4 += *__SA0ADV(__int4, ptr);

    /* Add in last few values from *ptr */
    __vpred sa0_vp = __SA0_VPRED(__int4);
    __int4 last_value_i4 = *__SA0(__int4, ptr);
    sum_i4 += __select(sa0_vp, last_value_i4, __int4(0));

    /* Close SA0 */
    __SA0_CLOSE();

    /* sum the 4 values in sum_i4 and return it */
    int sum = 0;
    for (i = 0; i < 4; i++)
        sum += sum_i4.s[i];

    return sum;
} 

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    return sum_by_4_sa(arr, sizeof(arr)/sizeof(arr[0]));
}
