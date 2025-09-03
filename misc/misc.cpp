#include <c7x_scalable.h>
#include <c7x.h>

/* https://chatgpt.com/s/t_68b181f4f9dc81918a939197b97949bb */

void reinterpret()
{
    short4 vec_s4 = short4(1, 2, 3, 4);
    // int2 vec_i2 = as_int2(vec_s4); // TBD
    // char4 vec_c4 = as_char4(vec_s4); // TBD
}

void type_cast()
{
    int a, b;
    // short2 vec_s2 = convert_short2(int2(a, b)); // TBD
}

void access()
{
    int4 vec_i4 = int4(1, 2, 3, 4);
    int var = vec_i4.x();
    vec_i4.s3() = 8; /* var = 1 */
#ifdef __C7X_HOSTEM_
    vec_i4.print(); /* vec_i4 = (1, 2, 3, 8) */
#endif
    vec_i4.x() = 69; /* var = 1 */
#ifdef __C7X_HOSTEM_
    vec_i4.print(); /* vec_i4 = (1, 2, 3, 8) */
#endif
    ushort8 vec_u8 = ushort8(1, 2, 3, 4, 5, 6, 7, 8);
    ushort4 vec_hi_u4 = vec_u8.hi(); /* 5, 6, 7, 8 */
    ushort4 vec_lo_u4 = vec_u8.lo(); /* 1, 2, 3, 4 */
}

void ext4()
{
    int16 input1, input2, result;
    result = input1 + input2; /* 16 independent 32-bit additions */

    int4 pos_i4 = int4(1, 2, 3, 4);
    int4 neg_i4 = -pos_i4; /* neg_i4 = (-1, -2, -3, -4) */
#ifdef __C7X_HOSTEM_
    neg_i4.print();
#endif

    int4 a_i4 = int4(1, 2, 3, 4);
    int4 b_i4 = a_i4++; /* b_i4 = (1, 2, 3, 4), a_i4 = (2, 3, 4, 5) */
#ifdef __C7X_HOSTEM_
    b_i4.print();
    a_i4.print();
#endif
}

void ext3(int4 a)
{
#ifdef __C7X_HOSTEM_
    a.print();
#endif
}


void ex1(int a, int b)
{
    int2 myvec = int2(a, b); /* init with C variables */
}

void ex2(int a, int b)
{
    int2 myv2_a = int2(a, 1); /* init with var and constant */
    int2 myv2_b = int2(b, 2);
    int4 myv4 = int4(myv2_a, myv2_b); /* init with shorter vectors */
    ext3(myv4);
}

int f(int len) 
{
    int cnt = 100;
    cnt += (len % 4 > 0);
    return cnt;
}

int main()
{
    short4 vec_a = short4(1, 2, 3, 4);    
    float2 vec_b = float2(3.2, -2.3);
    ushort4 myushort4a = ushort4(1); /* all 4 elements set to 1 */

    ex2(6, 9);
    ext4();
    access();

    return f(8);
}
