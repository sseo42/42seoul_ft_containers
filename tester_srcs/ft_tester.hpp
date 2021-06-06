#ifndef FT_TESTER_HPP
# define FT_TESTER_HPP

# include "ft_vector.hpp"
# include "ft_list.hpp"
# include "ft_stack.hpp"
# include "ft_queue.hpp"
# include "ft_deque.hpp"
# include "ft_map.hpp"
# include "ft_multimap.hpp"
# include "ft_set.hpp"
# include "ft_multiset.hpp"

# include <iostream>
# include <vector>
# include <list>
# include <stack>
# include <queue>
# include <map>
# include <set>

# include <fstream>

template<typename Tp>
class Vector_tester
{
public:
    typedef typename ft::Vector<Tp>::iterator       challenger_it;
    typedef typename std::vector<Tp>::iterator      master_it;

    Vector_tester() {}
    ~Vector_tester() {}
    
    void start_test(std::fstream &challenger_strm, std::fstream &master_strm)
    {
        int res;

        test_push_back(challenger_vector, challenger_strm);
        test_push_back(master_vector, master_strm);

        challenger_it = challenger_vector.begin();
        master_it = master_vector.begin();
        while (challenger_it != challenger_vector.end() && master_it != master_vector.end())
        {
            if (*challenger_it != )
        }
        if (master_result.compare(challenger_result) != 0)
        {
            /* test push_back ok */
        }
        else
        {

        }

        challenger_result = test_pop_back(challenger_vector, challenger_strm);
        master_result = test_pop_back(master_vector, master_strm);
        if (master_result.compare(challenger_result) != 0)
        {
            /* test pop_back ok */
        }
        else
        {

        }
    }

    template<typename Target>
    void test_push_back(Target target, std::fstream &fstrm)
    {
        try
        {
            vector.push_back(1);
            vector.push_back(2);
            vector.push_back(3);
            vector.push_back(4);

            for (iterator it = vector.begin(); it != vector.end(); ++it)
                fstrm << *it << " ";
        }
        catch(...)
        {
            fstrm << std::flush << "Error: push_back";
        }
        fstrm << std::endl;
    }

    void test_pop_back(std::fstream &fstrm)
    {
        try
        {
            for (int i = 0; i < 10; ++i)
                vector.push_back(i);

            for (int i = 0; i < 10; ++i)
                vector.pop_back();
            
            for (iterator it = vector.begin(); it != vector.end(); ++it)
                fstrm << *it << " ";
        }
        catch(...)
        {
            fstrm << std::flush << "Error: pop_back";
        }
        fstrm << std::endl;
    }

private:
    ft::Vector<Tp>  challenger_vector;
    std::vector<Tp> master_vector;

    Vector_tester(const Vector_tester& src)
    {
        if (*this == src)
            return ;
        /* forbidden */
    }

    Vector_tester& operator=(const Vector_tester& src)
    {
        if (*this == src)
            return ;
        /* forbidden */
    }
};

#endif /* FT_TESTER_HPP */