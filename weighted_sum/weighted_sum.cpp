
int global_array[] = {1, 2, 3};

void bad_example(int *ptr)
{
    *ptr++ = global_array[0];
}

void weighted_sum(int * __restrict a, int * __restrict b, int * __restrict out,
    int weight_a, int weight_b, int n)
{
    #pragma UNROLL(1)
    #pragma MUST_ITERATE(1024, ,32)
    for (int i = 0; i < n; i++)
    {
        out[i] = a[i] * weight_a + b[i] * weight_b;
    }
}

int main()
{
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3};
    int out[3];

    weighted_sum(a, b, out, 1, 1, 3);
    
    bad_example(global_array);
} 
