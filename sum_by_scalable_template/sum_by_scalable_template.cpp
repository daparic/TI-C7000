#include <c7x_scalable.h>

/* Change from int to type T deduced when the function is called: float, short
 * Cannot use int_vec
 * Instead use make_full_vector to create the scalable vector type T_vec
 */

template <typename T>
T sum_by_scalable_template(T *ptr, int length)
{
    using T_vec = typename c7x::make_full_vector<T>::type;
    T_vec sum_tv = T_vec(0);
    T_vec *ptr_tv = (T_vec *)ptr;
    const int vec_len = c7x::element_count_of<T_vec>::value;
    // todo
}

int main()
{

}
