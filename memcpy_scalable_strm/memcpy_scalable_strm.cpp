#include <c7x_scalable.h>
#include <iostream>

using namespace c7x;

/*
 * memcpy_scalable_strm<typename S>(const S *in, S *out, int len)
 *
 * S - A basic data type such as short or float
 * in - The input buffer
 * out - The output buffer
 * len - The number of elements to copy
 */
template<typename S>
void memcpy_scalable_strm(const S *__restrict in, S *__restrict out, int len) // g++
// void memcpy_scalable_strm(const S *restrict in, S *restrict out, int len)  // cl7x
{
    /*
     * Create scalable vector type V, where the elements are of type S
     */
    using V = typename make_full_vector<S>::type;

    /* 
     * Find the maximum number of vector loads/stores needed to copy the buffer,
     * including any remainder.
     */
    int cnt = len / element_count_of<V>::value;
    cnt += (len % element_count_of<V>::value > 0);

    /*
     * Initialize the SE for a linear read in and the SA for a linear write out
     */
    __SE_TEMPLATE_v1 in_tmplt = __gen_SE_TEMPLATE_v1();
    __SA_TEMPLATE_v1 out_tmplt = __gen_SA_TEMPLATE_v1();

    in_tmplt.VECLEN = se_veclen<V>::value;
    in_tmplt.ELETYPE = se_eletype<V>::value;
    in_tmplt.DIMFMT = __SE_DIMFMT_1D;
    in_tmplt.ICNT0 = len;

    out_tmplt.VECLEN = sa_veclen<V>::value;
    out_tmplt.DIMFMT = __SA_DIMFMT_1D;
    out_tmplt.ICNT0 = len;

    __SE0_OPEN(in, in_tmplt);
    __SA0_OPEN(out_tmplt);

    /*
     * Perform the copy. If there is remainder, the last store will be
     * predicated
     */
    int i;
    for (i = 0; i < cnt; i++)
    {
        V tmp           = strm_eng<0, V>::get_adv();
        __vpred pred    = strm_agen<0, V>::get_vpred();
        V *addr         = strm_agen<0, V>::get_adv(out);
        __vstore_pred(pred, addr, tmp);
    }

    __SE0_CLOSE();
    __SA0_CLOSE();
}

int main()
{
#if 0
    // https://gist.github.com/daparic/1d52b0d64b6d98a17cb5272836f8899a
    char src[5] = {'a','p','p','l','e'};
    char dest[5];
    memcpy_scalable_strm(src, dest, 5);
#endif

    constexpr int N = 5;

    // Test with int
    int in_int[N]  = {1, 2, 3, 4, 5};
    int out_int[N] = {0};

    memcpy_scalable_strm(in_int, out_int, N);
    for (int i = 0; i < N; i++) std::cout << out_int[i];
}
