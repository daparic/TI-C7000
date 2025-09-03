#include <c7x.h>
#include <c7x_scalable.h>

int sum_by_scalable_se(int *ptr, int length)
{
    using iv_t = c7x::int_vec;
    iv_t sum_sv = iv_t(0);
    const int vec_len = c7x::element_count_of<iv_t>::value;
    int i;

    /* Configure SE parameters */
    __SE_TEMPLATE_v1 se_params = __gen_SE_TEMPLATE_v1();
    se_params.VECLEN = c7x::se_veclen<iv_t>::value;
    se_params.ELETYPE = c7x::se_eletype<iv_t>::value;
    se_params.DIMFMT = __SE_DIMFMT_1D;
    se_params.ICNT0 = length;

    /* Open SE0 with base address ptr, and those parameters */
    __SE0_OPEN(ptr, se_params);

    /* Compute loop_count */
    int loop_count = length/vec_len;
    if (length % vec_len)
        loop_count += 1;

    /* Iterate loop_count times to sum values from *ptr into */
    for (i = 0; i < loop_count; i++)
        sum_sv += c7x::strm_eng<0, iv_t>::get_adv();

    /* Close SE0 */
    __SE0_CLOSE();

    /* sum all the values in sum_sv and return it */
    int sum = 0;
    for (i = 0; i < vec_len; i++)
        sum += sum_sv.s[i];

    return sum;
} 

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    return sum_by_scalable_se(arr, sizeof(arr)/sizeof(arr[0]));
}
