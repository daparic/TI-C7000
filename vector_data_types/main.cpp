#include <c7x.h>
#include <c7x_scalable.h>

void vector_data_type()
{
    float input1[16], input2[16], result[16];
    for (int i = 0; i < 16; i++) result[i] = input1[i] + input2[i];

    c7x::float_vec vInput1, vInput2, vResult;
    vResult = vInput1 + vInput2;

    float16 v16Input1, v16Input2, v16Result;
    v16Result = v16Input1 + v16Input2;
}

int main()
{
    return 0;
}
