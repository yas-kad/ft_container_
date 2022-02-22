#include <iostream>
#include <iterator>
#include <vector>

template <typename myIter> // myIter = iterator
void    dosome(myIter f) // iterator
{
    typedef typename std::iterator_traits<myIter>::value_type value_type;
    value_type test = *f; // value_type => int
    std::cout << test << std::endl;
}


int main()
{
    std::vector<int> vec(3, 1337);
    std::vector<int> vec2;
   // std::operator==(vec, vec2);
   // if (vec != vec2)
    
    std::vector<int>::iterator it;
    std::vector<int>::iterator();

    int arr[] = {42, 19};
    dosome(&arr[0]);


    return 0;
}