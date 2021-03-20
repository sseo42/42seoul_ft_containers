#include "ft_vector.hpp"
#include "ft_list.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>


int     main(void)
{
    ft::Vector<int> v_origin;
    
    ft::Vector<int>::iterator v_it;

    std::cout << "============================resize test=============================\n";
    v_origin.resize(10);
    std::cout << "size of vector: " << v_origin.size() << std::endl;
    for (v_it = v_origin.begin(); v_it != v_origin.end(); v_it++)
    {
        std::cout << *v_it << " ";
    }
    std::cout << std::endl;
    std::cout << "===========================pop back test=============================\n";
    v_origin.pop_back();
    std::cout << "size after pop_back: " << v_origin.size() << std::endl;
    
    std::cout << "============================insert test=============================\n";
    ft::Vector<int> v_target;

    v_target.push_back(1004);
    v_target.insert(v_target.begin(), v_origin.begin(), v_origin.end());
    for (v_it = v_target.begin(); v_it != v_target.end(); v_it++)
    {
        std::cout << *v_it << " ";
    }
    std::cout << std::endl;
    
    v_target.insert(v_target.end(), 3, 5);
    for (v_it = v_target.begin(); v_it != v_target.end(); v_it++)
    {
        std::cout << *v_it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "============================erase test=============================\n";
    v_target.erase(v_target.begin() + 9);
    for (v_it = v_target.begin(); v_it != v_target.end(); v_it++)
    {
        std::cout << *v_it << " ";
    }
    std::cout << std::endl;
    v_target.erase(v_target.begin() + 4, v_target.end());
    for (v_it = v_target.begin(); v_it != v_target.end(); v_it++)
    {
        std::cout << *v_it << " ";
    }
    std::cout << std::endl;

    std::cout << "============================swap test=============================\n";
    std::cout << "--------------------before swap-------------------\n";
    std::cout << "origin\n";
    for (v_it = v_origin.begin(); v_it != v_origin.end(); v_it++)
        std::cout << *v_it << " ";
    std::cout << std::endl;std::list<int> a;

    ft::List<int> test;
    ft::List<int> test2;

    std::cout << "-------------------list push_back----------------------\n";
    
    for (int i = 0; i < 10; i++)
        test.push_back(i);
    for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    {
        std::cout << *l_it << " ";
    }
    std::cout << std::endl;

    for (int i = 10; i < 20; i++)
        test2.push_back(i);
    for (ft::List<int>::iterator l_it = test2.begin(); l_it != test2.end(); l_it++)
    {
        std::cout << *l_it << " ";
    }
    std::cout << std::endl;

    std::cout << "-------------------list copy----------------------\n";
    
    test = test2;
    for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    {
        std::cout << *l_it << " ";
    }
    std::cout << std::endl;

    ft::List<int> test3;
    for (int i = 0; i < 10; i++)
        test3.push_back(i);
    test.splice(test.end(), test);
    std::cout << "-------------------list splice----------------------\n";
    
    for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    {
        std::cout << *l_it << " ";
    }
    std::cout << std::endl;

    std::cout << "-------------------list swap----------------------\n";
    test.swap(test3);
    for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    {
        std::cout << *l_it << " ";
    }
    std::cout << std::endl;

    std::cout << "-------------------list reverse----------------------\n";
    test.reverse();
    for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    {
        std::cout << *l_it << " ";
    }
    std::cout << std::endl;
    std::list<int> a;
    return 0;
}
