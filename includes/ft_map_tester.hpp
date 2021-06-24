#ifndef FT_MAP_TESTER_HPP
# define FT_MAP_TESTER_HPP

# include "ft_tester.hpp"
# include "ft_map.hpp"
# include <map>

/**
 * 
 */

template<typename Container, typename Tp>
class MapTestCase
{
public:
    typedef typename Container::iterator    iterator;

    MapTestCase() {}

    ~MapTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class MapTestCase<Container, int>
{
public:
    typedef typename Container::iterator    iterator;

    MapTestCase() {}

    ~MapTestCase() {}

	void operator_braket()
	{
		container[3] = 1004;
		this->ret = container[3];
	}

	void insert()
	{
		Container	tmp;

		tmp.insert(tmp.end(), 200);
		tmp.insert(tmp.begin(), 3, 5);
		container.insert(container.begin(), tmp.begin(), tmp.end());
	}

	void erase()
	{
		typename Container::iterator start = container.begin();
		typename Container::iterator end = container.end();

		container.erase(container.begin());
		for (int i = 0; i < 3; ++i)
		{
			++start;
			--end;
		}
		container.erase(start, end);
	}

	void swap()
	{
		Container	tmp(1000);

		container.swap(tmp);
	}

	void clear()
	{
		container.clear();
	}

    Container& get_container()
    { return container; }

	int get_ret() const
	{ return ret; }

private:
    Container container;

	int		ret;
};

template<typename Container>
class MapTestCase<Container, char>
{
public:
    typedef typename Container::iterator    iterator;

    MapTestCase() {}

    ~MapTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class MapTestCase<Container, bool>
{
public:
    typedef typename Container::iterator    iterator;

    MapTestCase() {}

    ~MapTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Tp>
class MapTester : public TesterBase
{
public:
    typedef typename std::map<Tp>            master;
    typedef typename ft::Map<Tp>             challenger;
    typedef typename std::map<Tp>::iterator  master_iterator;
    typedef typename ft::Map<Tp>::iterator   challenger_iterator;
	typedef typename std::map<Tp>::reverse_iterator master_reverse_iterator;
	typedef typename ft::Map<Tp>::reverse_iterator challenger_reverse_iterator;

    MapTester() : TesterBase("Map")
	{ init_what_to_test(); }

    MapTester(bool log_flag, std::string dir = "")
        : TesterBase("Map", log_flag, dir)
	{ init_what_to_test(); }

    ~MapTester() {}
    
    void start_test()
    {
		ASSERT(master_case.resize(), challenger_case.resize());
		ASSERT(master_case.reserve(), challenger_case.reserve());
		ASSERT(master_case.operator_braket(), challenger_case.operator_braket());
		ASSERT(master_case.push_back(), challenger_case.push_back());
		ASSERT(master_case.pop_back(), challenger_case.pop_back());
		ASSERT(master_case.insert(), challenger_case.insert());
		ASSERT(master_case.at(), challenger_case.at());
		ASSERT(master_case.front(), challenger_case.front());
		ASSERT(master_case.back(), challenger_case.back());
		ASSERT(master_case.erase(), challenger_case.erase());
		ASSERT(master_case.assign(), challenger_case.assign());
		ASSERT(master_case.swap(), challenger_case.swap());
		ASSERT(master_case.clear(), challenger_case.clear());
	}

private:
	void init_what_to_test()
	{
		what_to_test.insert(std::make_pair("resize", "compare_size"));
		what_to_test.insert(std::make_pair("resize", "compare_iterator"));
		what_to_test.insert(std::make_pair("resize", "compare_reverse_iterator"));

		what_to_test.insert(std::make_pair("reserve", "compare_capacity"));

		what_to_test.insert(std::make_pair("operator_braket", "compare_ret"));

		what_to_test.insert(std::make_pair("at", "compare_ret"));

		what_to_test.insert(std::make_pair("front", "compare_ret"));

		what_to_test.insert(std::make_pair("back", "compare_ret"));

		what_to_test.insert(std::make_pair("assign", "compare_size"));
		what_to_test.insert(std::make_pair("assign", "compare_iterator"));
		what_to_test.insert(std::make_pair("assign", "compare_reverse_iterator"));

		what_to_test.insert(std::make_pair("push_back", "compare_size"));
		what_to_test.insert(std::make_pair("push_back", "compare_iterator"));
		what_to_test.insert(std::make_pair("push_back", "compare_reverse_iterator"));

		what_to_test.insert(std::make_pair("pop_back", "compare_size"));
		what_to_test.insert(std::make_pair("pop_back", "compare_iterator"));
		what_to_test.insert(std::make_pair("pop_back", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("pop_back", "compare_empty"));

		what_to_test.insert(std::make_pair("insert", "compare_size"));
		what_to_test.insert(std::make_pair("insert", "compare_iterator"));
		what_to_test.insert(std::make_pair("insert", "compare_reverse_iterator"));

		what_to_test.insert(std::make_pair("erase", "compare_size"));
		what_to_test.insert(std::make_pair("erase", "compare_iterator"));
		what_to_test.insert(std::make_pair("erase", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("erase", "compare_empty"));

		what_to_test.insert(std::make_pair("swap", "compare_size"));
		what_to_test.insert(std::make_pair("swap", "compare_iterator"));
		what_to_test.insert(std::make_pair("swap", "compare_reverse_iterator"));

		what_to_test.insert(std::make_pair("clear", "compare_size"));
		what_to_test.insert(std::make_pair("clear", "compare_iterator"));
		what_to_test.insert(std::make_pair("clear", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("clear", "compare_empty"));
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

	int compare_capacity()
	{
		size_t master_capacity = master_case.get_container().capacity();
		size_t challenger_capacity = challenger_case.get_container().capacity();
		if (master_capacity != challenger_capacity)
			return 1;
		return 0;
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
		master_reverse_iterator master_start = master_case.get_container().rbegin();
		master_reverse_iterator master_it = master_case.get_container().rbegin();
		master_reverse_iterator master_end = master_case.get_container().rend();
		challenger_reverse_iterator challenger_start = challenger_case.get_container().rbegin();
		challenger_reverse_iterator challenger_it = challenger_case.get_container().rbegin();
		challenger_reverse_iterator challenger_end = challenger_case.get_container().rend();

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

	int compare_ret()
	{
		Tp master_ret = master_case.get_ret();
		Tp challenger_ret = challenger_case.get_ret();

		if (master_ret != challenger_ret)
			return 1;
		return 0;
	}
    
	int compare_empty()
	{
		bool master_empty = master_case.get_container().empty();
		bool challenger_empty = challenger_case.get_container().empty();

		if (master_empty != challenger_empty)
			return 1;
		return 0;
	}

    MapTestCase<master, Tp>      		master_case;
    MapTestCase<challenger, Tp>  		challenger_case;
};

#endif /* FT_map_TESTER_HPP */
