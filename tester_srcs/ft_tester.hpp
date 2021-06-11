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
# include <algorithm>
# include <vector>
# include <list>
# include <stack>
# include <queue>
# include <map>
# include <set>

# include <fstream>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

template<typename Tp>
class Vector_tester
{
public:
    typedef typename ft::Vector<Tp>::iterator       challenger_iterator;
    typedef typename std::vector<Tp>::iterator      master_iterator;

    Vector_tester() {}
    ~Vector_tester() {}
    
    void start_test(std::fstream &challenger_strm, std::fstream &master_strm)
    {
		if (compare_push_back(challenger_strm, master_strm))
			std::cout << RED << "Push_back: diff ko\n" << RESET;
		else
			std::cout << GREEN << "Push_back: diff ok\n" << RESET;

    }

	int compare_push_back(std::fstream &challenger_strm, std::fstream &master_strm)
	{
		typedef typename ft::is_integer<Tp>::type Integral;

		try
		{
			test_push_back(master_vector, master_strm);
		}
		catch (...)
		{
			std::cerr << YELLOW << "Push_back: Wrong case\n" << RESET;
			throw ;
		}
		try
		{
			test_push_back(challenger_vector, challenger_strm, Integral);
			if (compare_containers_shape())
				return 1;
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			return 2;
		}
		return 0;
	}

    template<typename Target>
    void test_push_back(Target target, std::fstream &fstrm, ft::TrueType)
    {
        try
        {
			for (int i = 0; i < 10; ++i)
				target.push_back(i);
            for (iterator it = vector.begin(); it != vector.end(); ++it)
                fstrm << *it << " ";
        }
        catch(...)
        {
            fstrm << std::flush << "Error: push_back\n";
			throw ;
        }
        fstrm << std::endl;
    }

	template<typename Target>
	void test_push_back(Target target, std::fstream &fstrm, ft::FalseType)
	{
		typedef typename is_same<Tp, std::vector<int> > Tf;

		if (Tf::value)
		{
			try
			{
				int val = 0;

				for (int i = 0; i < 100; ++i)
				{
					std::vector<int> elem;
					for (int j = 0; j < 100; ++j)
						elem.push_back(++val);
					target.push_back(elem);
				}
				fstrm << "push_back vector elems: ok\n";
			}
			catch (...)
			{
				fstrm << "push back vector elems: failed\n";
				throw ;
			}
		}
		else
		{
			fstrm << "Not prepared case...\n";
		}
	}

private:
    ft::Vector<Tp>  challenger_vector;
    std::vector<Tp> master_vector;

	int compare_containers_shape(void)
	{
		challenger_iterator challenger_it;
		master_iterator master_it;

       	challenger_it = challenger_vector.begin();
       	master_it = master_vector.begin();
       	while (challenger_it != challenger_vector.end() && master_it != master_vector.end())
       	{
       	    if (*challenger_it != *master_it)
				return 1;
       	}
		if (challenger_it != challenger_vector.end() || master_it != master_vector.end())
			return 1;
		return 0;
	}

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
