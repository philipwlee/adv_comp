#include<iostream>


int len(int** arr)
{
    int len{ static_cast<int>(*(arr + 1) - *arr) };

    std::cout << *(&arr + 1) << '\n' << arr << '\n' << len << '\n';
    std::cout << sizeof(*arr) << sizeof(**arr) << '\n';
    return len;
}

void print(int (*arr))
{
    int l{ len(&arr) };

    std::cout << l << '[';
    for (int i {0}; i < l; ++i)
    {
        std::cout << arr[i] << ", ";
    }
    std::cout << ']' << '\n';
}

void pointers()
{
    std::cout << "pointers()" << '\n';
    int a{ 100 };
    int* ptr_a{ &a };
    std::cout << "Variable a=" << a << ", Pointer to a=" << ptr_a << '\n';
    std::cout << "Dereferenced pointer to a=" << *ptr_a << '\n';

    int demo_arr[4] {0,1,2,3};
    std::cout << sizeof(demo_arr) << ',' << sizeof(demo_arr[0]) << '\n';
    int (*arr_ptr) {demo_arr};

    print(arr_ptr);
}

void display_matrix(int (*mat_ptr)[2])
{
    for (int i{0}; i<2; ++i)
    {
        for (int j{0}; j<2; ++j)
        {
            std::cout << mat_ptr[i][j] << ", ";
        }
        std::cout << '\n';
    }
}

void two_d_matrix()
{
    std::cout << "two_d_matrix()" << '\n';
    int mat[1][2];
    int (*mat_ptr)[2] {mat};

    // Allocates memory to the heap;
    int (*c)[2] {new int[2][2]}; // allocates 2*2=4 -> 4ints*4bytes=16bytes total
    // <==> these two are the same^v
    int (*d)[2] {(int (*)[2]) new int[4]}; // 4ints*4bytes=16bytes total
    // new int[4] returns (int*). Therefore we must cast it to (int(*)[2])

    for (int i{0}; i<2; ++i)
    {
        for (int j{0}; j<2; ++j)
        {
            mat[i][j] = 2*i+j;
            std::cout << mat[i][j] << '\n';
        }
    }
    display_matrix(mat_ptr);
}

void modify_value_variable(int* int_ptr)
{
    *int_ptr = 100;
}

void modify_var_func_demo()
{
    std::cout << "modify_var_func_demo()" << '\n';
    int a {4};
    int* a_ptr{&a};

    std::cout << a << '\n';
    modify_value_variable(a_ptr);

    std::cout << a << '\n';
}

void allocate_matrix_heap(int** param)
{
    *param = new int[4];
}

void allocate_array_by_func()
{
    std::cout << "allocate_array_by_func()" << '\n';
    int* unalloc{ nullptr }; // arrays are simply pointers.
    std::cout << sizeof(unalloc) << '\n';
    allocate_matrix_heap(&unalloc); // address of the unallocated array (pointer to an int pointer)
    std::cout << sizeof(unalloc) << '\n';
}

int modify_variable(int &alias)
{
    alias=1111; // alias is a reference of b, so assignment to alias affects b.
}

void modify_by_reference()
{
    std::cout << "modify_by_reference()\n";
    int b{200};
    std::cout << "Before, b=" << b << '\n';
    modify_variable(b);
    std::cout << "After, b=" << b << '\n';
}

int lec_2()
{
    pointers(); // messing around with pointers
    two_d_matrix(); // initialize and print a 2d matrix
    modify_var_func_demo(); // changes the value of a variable using pointers
    allocate_array_by_func(); // use a function to allocate an array initialized as nullptr

    modify_by_reference(); // modify_var_func_demo() but using a reference (alias)

    return 0;
}