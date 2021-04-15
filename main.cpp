#include "ft_vector.hpp"
#include "ft_list.hpp"
#include "ft_stack.hpp"
#include "ft_queue.hpp"
#include "ft_map.hpp"
#include "ft_deque.hpp"
#include "ft_multimap.hpp"
#include "ft_set.hpp"
#include "ft_multiset.hpp"

#include "ft_tester.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>

bool my_compare(int a, int b)
{
    return a > b;
}

int     main(void)
{
    // ft::Vector<int> v_origin;
    
    // ft::Vector<int>::iterator v_it;

    // std::cout << "============================resize test=============================\n";
    // v_origin.resize(10);
    // std::cout << "size of vector: " << v_origin.size() << std::endl;
    // for (v_it = v_origin.begin(); v_it != v_origin.end(); v_it++)
    // {
    //     std::cout << *v_it << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "===========================pop back test=============================\n";
    // v_origin.pop_back();
    // std::cout << "size after pop_back: " << v_origin.size() << std::endl;
    
    // std::cout << "============================insert test=============================\n";
    // ft::Vector<int> v_target;

    // v_target.push_back(1004);
    // v_target.insert(v_target.begin(), v_origin.begin(), v_origin.end());
    // for (v_it = v_target.begin(); v_it != v_target.end(); v_it++)
    // {
    //     std::cout << *v_it << " ";
    // }
    // std::cout << std::endl;
    
    // v_target.insert(v_target.end(), 3, 5);
    // for (v_it = v_target.begin(); v_it != v_target.end(); v_it++)
    // {
    //     std::cout << *v_it << " ";
    // }
    // std::cout << std::endl;
    
    // std::cout << "============================erase test=============================\n";
    // v_target.erase(v_target.begin() + 9);
    // for (v_it = v_target.begin(); v_it != v_target.end(); v_it++)
    // {
    //     std::cout << *v_it << " ";
    // }
    // std::cout << std::endl;
    // v_target.erase(v_target.begin() + 4, v_target.end());
    // for (v_it = v_target.begin(); v_it != v_target.end(); v_it++)
    // {
    //     std::cout << *v_it << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "============================swap test=============================\n";
    // std::cout << "--------------------before swap-------------------\n";
    // std::cout << "origin\n";
    // for (v_it = v_origin.begin(); v_it != v_origin.end(); v_it++)
    //     std::cout << *v_it << " ";
    // std::cout << std::endl;std::list<int> a;

    // ft::List<int> test;
    // ft::List<int> test2;

    // std::cout << "-------------------list push_back----------------------\n";
    
    // for (int i = 0; i < 10; i++)
    //     test.push_back(i);
    // for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;

    // for (int i = 10; i < 20; i++)
    //     test2.push_back(i);
    // for (ft::List<int>::iterator l_it = test2.begin(); l_it != test2.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "-------------------list copy----------------------\n";
    
    // test = test2;
    // for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "-------------------list splice----------------------\n";
    // test.splice(test.end(), test);
    // for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "-------------------list swap----------------------\n";
    // ft::List<int> test3;
    // for (int i = 0; i < 10; i++)
    //     test3.push_back(i);
    // test.clear();
    // // test.push_back(100);
    // test.swap(test3);
    // for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;

    // for (ft::List<int>::iterator l_it = test3.begin(); l_it != test3.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "-------------------list reverse----------------------\n";
    // test.reverse();
    // for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "-------------------list merge----------------------\n";


    // for (ft::List<int>::iterator l_it = test2.begin(); l_it != test2.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;
    
    // test.merge(test2);
    // for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "-------------------list sort----------------------\n";
    // for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;

    // test.sort(my_compare);
    // for (ft::List<int>::iterator l_it = test.begin(); l_it != test.end(); l_it++)
    // {
    //     std::cout << *l_it << " ";
    // }
    // std::cout << std::endl;

    // std::queue<int> teacher_queue;
    // std::map<int, int> teacher_map;
    // std::set<int> teacher_set;
    // std::multimap<int, int> teacher_mlmap;

    // ft::Vector<int> tmp;
    // for (int i = 0; i < 10; ++i)
    //     tmp.push_back(i);

    // ft::Deque<int> dq;

    // std::cout << "-------------------dq size----------------------\n";
    // std::cout << "test zero size: " << dq.size() << std::endl;

    // std::cout << "-------------------dq max size----------------------\n";
    // std::cout << "test zero size: " << dq.max_size() << std::endl;

    // std::cout << "-------------------dq resize----------------------\n";
    // dq.resize(5);
    // std::cout << "test resize: " << dq.size() << std::endl;

    // std::cout << "-------------------dq assign----------------------\n";
    // dq.assign(tmp.begin(), tmp.end());
    // for (ft::Deque<int>::iterator dq_it = dq.begin(); dq_it != dq.end(); ++dq_it)
    // {
    //     std::cout << "test assign: " << *dq_it << std::endl;
    // }
    // std::cout << "test size after assign: " << dq.size() << std::endl;

    // std::cout << "-------------------dq pop----------------------\n";
    // dq.pop_front();
    // dq.pop_back();
    // for (ft::Deque<int>::iterator dq_it = dq.begin(); dq_it != dq.end(); ++dq_it)
    // {
    //     std::cout << "test pop: " << *dq_it << std::endl;
    // }
    // std::cout << "test size after pop: " << dq.size() << std::endl;

    // std::cout << "-------------------dq insert----------------------\n";
    // dq.insert(++dq.begin(), 10);
    // dq.insert(++dq.begin(), tmp.begin(), tmp.end());
    // dq.insert(dq.end(), 10, 200);
    // dq.insert(dq.begin(), 10, 300);
    // for (ft::Deque<int>::iterator dq_it = dq.begin(); dq_it != dq.end(); ++dq_it)
    // {
    //     std::cout << "test insert: " << *dq_it << std::endl;
    // }
    // std::cout << "test size after insert: " << dq.size() << std::endl;


    // std::cout << "-------------------dq erase----------------------\n";
    // dq.erase(dq.begin());
    // dq.erase(dq.end());
    // dq.erase(dq.begin(), dq.begin() + 10);
    // for (ft::Deque<int>::iterator dq_it = dq.begin(); dq_it != dq.end(); ++dq_it)
    // {
    //     std::cout << "test erase: " << *dq_it << std::endl;
    // }
    // std::cout << "test size after erase: " << dq.size() << std::endl;

    // ft::Deque<int> empty_dq;
    // dq.swap(empty_dq);
    // std::cout << "-------------------dq swap ---------------------\n";
    // for (ft::Deque<int>::iterator dq_it = empty_dq.begin(); dq_it != empty_dq.end(); ++dq_it)
    // {
    //     std::cout << "test swap: " << *dq_it << std::endl;
    // }
    // std::cout << "test size after swap: " << dq.size() << std::endl;
    
    // ft::Stack<int> test_stk;
    // ft::Queue<int> test_q;



    // std::cout << "===============================Map=============================\n";

    // ft::Map<int, int> test_map;
    // std::cout << "-------------------map empty ---------------------\n";
    // std::cout << "test map: is empty ? -> " << test_map.empty() << std::endl;
    // std::cout << std::endl;

    // std::cout << "-------------------map insert --------------------\n";
    // test_map.insert(ft::make_pair(10, 4));
    // test_map.insert(ft::make_pair(1, 2));
    // test_map.insert(ft::make_pair(5, 3));
    // for (ft::Map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
    // {
    //     std::cout << "test map: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "-------------------map init with iter---------------------\n";

    // ft::Map<int, int> test_map2(test_map.begin(), test_map.end());
    // for (ft::Map<int, int>::iterator it = test_map2.begin(); it != test_map2.end(); ++it)
    // {
    //     std::cout << "test map: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "-----------------------map size--------------------------\n";
    // std::cout << "test map size: " << test_map.size() << std::endl;
    // std::cout << std::endl;

    // std::cout << "-----------------------map max_size----------------------\n";
    // std::cout << "test map max_size: " << test_map.max_size() << std::endl;
    // std::cout << std::endl;

    // std::cout << "-----------------------map operator[]--------------------\n";
    // std::cout << "test map[5]: " << test_map[5] << std::endl;
    // test_map[20] = 1;
    // std::cout << "test map after [20] = 1\n";
    // for (ft::Map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
    // {
    //     std::cout << "test map: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "-----------------------map erase--------------------\n";
    
    // test_map.erase(10);
    // std::cout << "after erase 10\n";
    // for (ft::Map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
    // {
    //     std::cout << "test map: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "after erase begin to end - 1\n";
    // ft::Map<int, int>::iterator map_it = test_map.end();
    // test_map.erase(test_map.begin(), --map_it);
    // for (ft::Map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
    // {
    //     std::cout << "test map: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "-----------------------map swap --------------------\n";
    // for (ft::Map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
    // {
    //     std::cout << "test map: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;
    // for (ft::Map<int, int>::iterator it = test_map2.begin(); it != test_map2.end(); ++it)
    // {
    //     std::cout << "test map2: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;

    // ft::swap(test_map, test_map2);
    // std::cout << "****after swap****\n";
    // for (ft::Map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
    // {
    //     std::cout << "test map: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;
    // for (ft::Map<int, int>::iterator it = test_map2.begin(); it != test_map2.end(); ++it)
    // {
    //     std::cout << "test map2: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "-----------------------map clear--------------------\n";
    // for (ft::Map<int, int>::iterator it = test_map2.begin(); it != test_map2.end(); ++it)
    // {
    //     std::cout << "test map2: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;
    // std::cout << "****after clear test map2****\n";
    // test_map2.clear();
    // for (ft::Map<int, int>::iterator it = test_map2.begin(); it != test_map2.end(); ++it)
    // {
    //     std::cout << "test map2: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "-----------------------map key_comp--------------------\n";
    // ft::Map<int, std::string> test_map3;
    // test_map3.insert(ft::make_pair(1, "hello"));
    // test_map3.insert(ft::make_pair(2, "allo"));

    // std::cout << "target map\n";
    // for (ft::Map<int, std::string>::iterator it = test_map3.begin(); it != test_map3.end(); ++it)
    // {
    //     std::cout << "test map3: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;

    // ft::Map<int, std::string>::key_compare k_comp = test_map3.key_comp();
    // std::cout << "key compare between begin and begin + 1\n";
    // std::cout << k_comp(test_map3.begin()->first, (++test_map3.begin())->first) << std::endl;

    // std::cout << "-----------------------map value_comp------------------\n";
    // ft::Map<int, std::string>::value_compare v_comp = test_map3.value_comp();
    // std::cout << "value compare between begin and begin + 1\n";
    // std::cout << v_comp(*test_map3.begin(), *(++test_map3.begin())) << std::endl;

    // std::cout << "-------------------------map find ---------------------\n";
    // std::cout << "find a value of key 1\n";
    // std::cout << test_map3.find(1)->second << std::endl;

    // std::cout << "-------------------------map count---------------------\n";
    // std::cout << "count a key 1\n";
    // std::cout << test_map3.count(1) << std::endl;
    // std::cout << "count a key 3\n";
    // std::cout << test_map3.count(3) << std::endl;

    // std::cout << "-----------------------map lower bound-----------------\n";
    // std::cout << "lower bound of 5 -> " << test_map.lower_bound(5)->first << std::endl;
    // std::cout << std::endl;

    // std::cout << "-----------------------map upper bound-----------------\n";
    // std::cout << "upper bound of 5 -> " << test_map.upper_bound(5)->first << std::endl;
    // std::cout << std::endl;

    // std::cout << "-----------------------map equal range-----------------\n";
    // std::cout << "equal range of key 5 -> " << test_map.equal_range(5).first->first << " to " <<
    //     test_map.equal_range(5).second->first << std::endl;
    // std::cout << std::endl;

    // std::cout << "-------------------------map comparision---------------------\n";
    // test_map2 = test_map;
    // test_map2.erase(10);
    // for (ft::Map<int, int>::iterator it = test_map.begin(); it != test_map.end(); ++it)
    // {
    //     std::cout << "test map: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;
    // for (ft::Map<int, int>::const_iterator it = test_map2.begin(); it != test_map2.end(); ++it)
    // {
    //     std::cout << "test map2: " << it->first << " " << it->second << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "test_map == test_map2 ? -> " << (test_map == test_map2) << std::endl;
    // std::cout << "test_map > test_map2 ? -> " << (test_map > test_map2) << std::endl;
    // return 0;


    // ft::Multimap<int, std::string> test_multimap;
    // ft::Set<int> test_set;
    // ft::Multiset<int> test_mlset;

    // std::map<int, int> mp;
    // std::deque<int> test;

    std::cout << "test mine\n";
    Vector_tester<ft::Vector<int> > tester1;
    tester1.test();

    std::cout << "test origin\n";
    Vector_tester<std::vector<int> > tester2;
    tester2.test();
}
