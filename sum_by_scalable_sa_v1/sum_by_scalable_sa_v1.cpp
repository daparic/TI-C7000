#include <c7x.h>
#include <c7x_scalable.h>

int sum_by_scalable_sa_v1(int *ptr, int length)
{
    using iv_t = c7x::int_vec;
    iv_t sum_sv = iv_t(0);
    const int vec_len = c7x::element_count_of<iv_t>::value;
    int i;

    /* Configure SA parameters */
    __SA_TEMPLATE_v1 sa_params = __gen_SA_TEMPLATE_v1();
    sa_params.VECLEN = c7x::sa_veclen<iv_t>::value;
    sa_params.DIMFMT = __SA_DIMFMT_1D;
    sa_params.ICNT0 = length;

    /* Open SA0 with tohse parameters */
    __SA0_OPEN(sa_params);

    /* iterate length/vec_len times to sum values from *ptr */
    for (i = 0; i < length/vec_len; i++)
        sum_sv += *c7x::strm_agen<0, iv_t>::get_adv(ptr);

    /* Add in last few values from *ptr */
    __vpred sa0_vp = c7x::strm_agen<0, iv_t>::get_vpred();
    iv_t last_value_sv = *c7x::strm_agen<0, iv_t>::get(ptr);
    sum_sv += __select(sa0_vp, last_value_sv, iv_t(0));

    /* Close SA0 */
    __SA0_CLOSE();

    /* sum the 4 values in sum_i4 and return it */
    int sum = 0;
    for (i = 0; i < vec_len; i++)
        sum += sum_sv.s[i];

    return sum;
} 

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    return sum_by_scalable_sa_v1(arr, sizeof(arr)/sizeof(arr[0]));
}
