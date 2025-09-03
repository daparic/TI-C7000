#include <c7x_scalable.h>

int sum_by_scalable(int *ptr, int length)
{
    c7x::int_vec sum_sv = c7x::int_vec(0);
    c7x::int_vec *ptr_sv = (c7x::int_vec *)ptr;
    const int vec_len = c7x::element_count_of<c7x::int_vec>::value;
    int i;

    /* iterate length/vec_len times to sum values from *ptr_sv into sum_sv */
    for (i = 0; i < length/vec_len; i++)
        sum_sv += *ptr_sv++;

    /* add in last (length % vec_len) values from *ptr_sv */
    __vpred m_vp = __mask_int((unsigned) length % vec_len);
    sum_sv += __select(m_vp, *ptr_sv, c7x::int_vec(0));

    /* sum all the values in sum_sv and return it */
    int sum = 0;
    for (i = 0; i < vec_len; i++)
        sum += sum_sv.s[i];

    return sum;
}

int main()
{
    int v[] = {1, 2, 3, 4, 5};
    return sum_by_scalable(v, 5);
}
