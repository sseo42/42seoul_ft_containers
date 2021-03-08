#include "ft_vector.hpp"
#include "ft_list.hpp"
#include <iostream>
#include <vector>
#include <list>



int     main(void)
{
    ft::Vector<int>*    v_origin = new ft::Vector<int>(5, 3);
    
    ft::Vector<int>::iterator v_test = v_origin->begin();
   
    ft::Vector<int>  V_test(*v_origin);
    
    delete v_origin;

    V_test.clear();
    for (int i = 0; i < 10; i++)
        V_test.push_back(i);
    
    ft::Vector<int>::iterator v_it_test;
    //ft::Vector<int>::iterator v_it_test2 = V_test.end();

    for (v_it_test = V_test.begin(); v_it_test != V_test.end(); v_it_test++)
    {
        std::cout << "test: " << *v_it_test << std::endl;
        v_it_test++;
    }
    std::cout << "hello\n";
    std::cout << "size: " << V_test.size();

    ft::Vector<ft::Vector<int> > d_test;

    d_test.push_back(V_test);
    
    ft::Vector<ft::Vector<int> >::iterator vv_it;

    for (vv_it = d_test.begin(); vv_it != d_test.end(); vv_it++)
    {
        for (v_it_test = vv_it->begin(); v_it_test != vv_it->end(); v_it_test++)
        {
            std::cout << "test: " << *v_it_test << std::endl;
        }
    }
    return 0;
}
