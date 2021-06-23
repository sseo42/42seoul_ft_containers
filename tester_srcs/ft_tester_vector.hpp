#ifndef FT_TESTER_VECTOR_HPP
# define FT_TESTER_VECTOR_HPP

# include "ft_tester.hpp"
# include "ft_vector.hpp"
# include <vector>

/**
 * 
 */

template<typename Container, typename Tp>
class VectorTestCase
{
public:
    typedef typename Container::iterator    iterator;

    VectorTestCase() {}

    ~VectorTestCase() {}

    Container& get_container() const
    { return container; };

private:
    Container container;
};

template<typename Container>
class VectorTestCase<Container, int>
{
public:
    typedef typename Container::iterator    iterator;

    VectorTestCase() {}

    ~VectorTestCase() {}

    Container& get_container() const
    { return container; };

private:
    Container container;
};

template<typename Container>
class VectorTestCase<Container, char>
{
public:
    typedef typename Container::iterator    iterator;

    VectorTestCase() {}

    ~VectorTestCase() {}

    Container& get_container() const
    { return container; };

private:
    Container container;
};

template<typename Container>
class VectorTestCase<Container, bool>
{
public:
    typedef typename Container::iterator    iterator;

    VectorTestCase() {}

    ~VectorTestCase() {}

    Container& get_container() const
    { return container; };

private:
    Container container;
};

template<typename Tp>
class VectorTester : public TesterBase
{
public:
    typedef typename std::vector<Tp>            master;
    typedef typename ft::Vector<Tp>             challenger;
    
    typedef typename ft::Vector<Tp>::iterator   challenger_iterator;
    typedef typename std::vector<Tp>::iterator  master_iterator;

    Vector_tester() : TesterBase("Vector") {}
    Vector_tester(bool log_flag, std::string dir = "")
        : TesterBase("Vector", log_flag, dir) {}

    ~Vector_tester() {}
    
    void start_test()
    {
		compare_push_back();
    }

	int compare_push_back()
	{
        VectorTestCase<master, Tp>      master;
        VectorTestCase<challenger, Tp>  test;

        log_case("***** PUSH BACK *****");
        TEST_SEGV(master.push_back());
        if (WIFEXITED(test_segv_pid))
        {
            ASSERT(test.push_back());

        }
            if (!test.push_back());
                compare_containers_shape()
		return 0;
	}

    /* test functions */
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
    
    ft::Vector<Tp>  challenger_vector;
    std::vector<Tp> master_vector;
};

#endif /* FT_TESTER_VECTOR_HPP */