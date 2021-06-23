#ifndef FT_VECTOR_TESTER_HPP
# define FT_VECTOR_TESTER_HPP

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

	iterator begin()
	{ return container.begin(); }

    Container& get_container()
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

	void push_back()
	{
		for (int i = 0; i < 10; ++i)
		{
			container.push_back(i);
		}
	}

    Container& get_container()
    { return container; }

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

    Container& get_container()
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

    Container& get_container()
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
    typedef typename std::vector<Tp>::iterator  master_iterator;
    typedef typename ft::Vector<Tp>::iterator   challenger_iterator;

    VectorTester() : TesterBase("Vector")
	{
		compare_mapping["resize"] = VectorTest::compare_size;
		compare_mapping["resize"] = VectorTest::compare_iterator;
		compare_mapping["resize"] = VectorTest::compare_reverse_iterator;

		compare_mapping["reserve"] = VecterTest::compare_capacity;

		compare_mapping["operator_braket"] = VectorTest::compare_val;

		compare_mapping["at"] = VectorTest::compare_val;

		compare_mapping["front"] = VectorTest::compare_val;

		compare_mapping["back"] = VectorTest::compare_val;

		compare_mapping["assign"] = VectorTest::compare_size;
		compare_mapping["assign"] = VectorTest::compare_iterator;
		compare_mapping["assign"] = VectorTest::compare_reverse_iterator;

		compare_mapping["push_back"] = VectorTest::compare_size;
		compare_mapping["push_back"] = VectorTest::compare_iterator;
		compare_mapping["push_back"] = VectorTest::compare_reverse_iterator;

		compare_mapping["pop_back"] = VectorTest::compare_size;
		compare_mapping["pop_back"] = VectorTest::compare_iterator;
		compare_mapping["pop_back"] = VectorTest::compare_reverse_iterator;
		compare_mapping["pop_back"] = VectorTest::compare_empty;

		compare_mapping["insert"] = VectorTest::compare_size;
		compare_mapping["insert"] = VectorTest::compare_iterator;
		compare_mapping["insert"] = VectorTest::compare_reverse_iterator;

		compare_mapping["erase"] = VectorTest::compare_size;
		compare_mapping["erase"] = VectorTest::compare_iterator;
		compare_mapping["erase"] = VectorTest::compare_reverse_iterator;
		compare_mapping["erase"] = VectorTest::compare_empty;

		compare_mapping["swap"] = VectorTest::compare_size;
		compare_mapping["swap"] = VectorTest::compare_iterator;
		compare_mapping["swap"] = VectorTest::compare_reverse_iterator;

		compare_mapping["clear"] = VectorTest::compare_size;
		compare_mapping["clear"] = VectorTest::compare_iterator;
		compare_mapping["clear"] = VectorTest::compare_reverse_iterator;
		compare_mapping["clear"] = VectorTest::compare_empty;
	}

    VectorTester(bool log_flag, std::string dir = "")
        : TesterBase("Vector", log_flag, dir) {}

    ~VectorTester() {}
    
    void start_test()
    {
		ASSERT(master_case.push_back(), challenger_case.push_back());
	}

private:
	typedef int (VectorTester::*cmp_func)();
	typedef std::multimap<std::string, cmp_func> func_mapping;
	typedef std::multimap<std::string, cmp_func>::iterator func_mapping_iter;

	void compare_container_shape(const std::string& func_name)
	{
		for (func_mapping_iter = compare_mapping.begin();	\
				func_mapping_iter != compare_mapping.end();	\
				
		if (compare_iterator())
			log_fail("compare_iterator");
		else
			log_success("compare_iterator");
		if (compare_size())
			log_fail("compare_size");
		else
			log_success("compare_size");
		if (compare_front())
			log_fail("compare_front");
		else
			log_success("compare_front");
		if (compare_back())
			log_fail("compare_back");
		else
			log_success("compare_back");
	}

	int compare_iterator()
	{
		master_iterator master_start = master_case.get_container().begin();
		master_iterator master_it = master_case.get_container().begin();
		master_iterator master_end = master_case.get_container().end();
		challenger_iterator challenger_start = challenger_case.get_container().begin();
		challenger_iterator challenger_it = challenger_case.get_container().begin();
		challenger_iterator challenger_end = challenger_case.get_container().end();

       	while (challenger_it != challenger_end && master_it != master_end)
       	{
       	    if (*challenger_it != *master_it)
				return 1;
			++challenger_it;
			++master_it;
       	}
		if (challenger_it != challenger_end || master_it != master_end)
			return 1;
		while (challenger_it != challenger_start && master_it != master_start)
		{
			challenger_it--;
			master_it--;
       	    if (*challenger_it != *master_it)
				return 1;
		}
		if (challenger_it != challenger_start || master_it != master_start)
			return 1;
		return 0;
	}

	int compare_reverse_iterator()
	{
		master_iterator master_start = master_case.get_container().rbegin();
		master_iterator master_it = master_case.get_container().rbegin();
		master_iterator master_end = master_case.get_container().rend();
		challenger_iterator challenger_start = challenger_case.get_container().rbegin();
		challenger_iterator challenger_it = challenger_case.get_container().rbegin();
		challenger_iterator challenger_end = challenger_case.get_container().rend();

       	while (challenger_it != challenger_end && master_it != master_end)
       	{
       	    if (*challenger_it != *master_it)
				return 1;
			++challenger_it;
			++master_it;
       	}
		if (challenger_it != challenger_end || master_it != master_end)
			return 1;
		while (challenger_it != challenger_start && master_it != master_start)
		{
			challenger_it--;
			master_it--;
       	    if (*challenger_it != *master_it)
				return 1;
		}
		if (challenger_it != challenger_start || master_it != master_start)
			return 1;
		return 0;
	}

	int compare_size()
	{
		size_t master_size = master_case.get_container().size();
		size_t challenger_size = challenger_case.get_container().size();

		if (master_size != challenger_size)
			return 1;
		else
			return 0;
	}

	int compare_front()
	{
		Tp master_front = master_case.get_container().front();
		Tp challenger_front = challenger_case.get_container().front();

		if (master_front != challenger_front)
			return 1;
		return 0;
	}

	int compare_back()
	{
		Tp master_back = master_case.get_container().back();
		Tp challenger_back = challenger_case.get_container().back();

		if (master_back != challenger_back)
			return 1;
		return 0;
	}

	int compare_ret()
	{
		if (master_ret != challenger_ret)
			return 1;
		return 0;
	}
    
    VectorTestCase<master, Tp>      master_case;
    VectorTestCase<challenger, Tp>  challenger_case;
	Tp								master_ret;
	Tp								challegner_ret;
	std::multimap<std::string, cmp_func> compare_mapping;
};

#endif /* FT_VECTOR_TESTER_HPP */
