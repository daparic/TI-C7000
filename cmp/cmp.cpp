#include <c7x.h>

void f1()
{
    float4 a_f4 = float4(1, -2, 3, -4);
    float4 b_f4 = float4(-1, 2, -3, 4);

    bool4 cond_lt = __cmp_lt_bool(a_f4, b_f4);
    /* cond_lt = (0, 1, 0, 1) */
    cond_lt.print();

    float4 r_f4 = __select(cond_lt, a_f4, b_f4);
    /* r_f4 = (-1, -2, -3, -4) */

    r_f4.print();
}

void f2()
{
    int4 a_i4 = int4(1, -2, 3, -4);
    int4 b_i4 = int4(-1, 2, -3, 4);

    bool4 cond_lt = __cmp_lt_bool(a_i4, b_i4);
    int4 r_i4 = __select(cond_lt, a_i4, b_i4); 

    cond_lt.print();
    r_i4.print();
}

int sum_by_4(int *ptr, int length)
{
    int4 sum_i4 = int4(0);
    int4 *ptr_i4 = (int4 *)ptr;

    /* iterate length/4 times to sum values from *ptr_i4 into sum_i4 */

    bool4 m_b4 = __mask_bool4((unsigned) (length % 4));
    sum_i4 += __select(m_b4, *ptr_i4, int4(0));

    m_b4.print();
    length = 0;

    /* sum the 4 values in sum_i4 and return it */

    return 0;
}

int main()
{
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8};
    return sum_by_4(v, sizeof(v)/sizeof(v[0]));
}

