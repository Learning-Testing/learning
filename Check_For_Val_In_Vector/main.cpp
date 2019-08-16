#include <iostream>
#include <algorithm>
#include <vector>
# include "library.cpp"


int main()
{
    std::vector<int> hello = {1,2,3};
    if (check_in_vector(3, hello) != 0); // does not equal false
        std::cout << "3 in hello" << std::endl;
}
