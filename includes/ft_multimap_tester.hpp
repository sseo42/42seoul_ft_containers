#ifndef FT_MULTIMAP_TESTER_HPP
# define FT_MULTIMAP_TESTER_HPP

# include "ft_tester.hpp"
# include "ft_multimap.hpp"
# include <map>

/**
 * 
 */

template<typename Container, typename Key, typename Val>
class MultimapTestCase
{
public:
    typedef typename Container::iterator    iterator;

    MultimapTestCase() {}

    ~MultimapTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class MultimapTestCase<Container, int, int>
{
public:
    typedef typename Container::iterator    iterator;

    MultimapTestCase() {}

    ~MultimapTestCase() {}

	void insert()
	{
		typedef typename Container::value_type val_type;

		Container tmp;

		for (int i = 0; i < 1000; ++i)
		{
			val_type val(i, i + 1);
			tmp.insert(val);
		}
		for (int i = 0; i < 100; ++i)
		{
			val_type val(i, i + 1);
			tmp.insert(val);
		}

		Container tmp2(tmp.begin(), tmp.end());

		container.insert(tmp2.begin(), tmp2.end());
	}

	void erase()
	{
		container.erase(container.begin());
		container.erase(0);

		typename Container::iterator start = container.begin();
		typename Container::iterator end = container.end();

		for (int i = 0; i < 3; ++i)
		{
			++start;
			--end;
		}
		container.erase(start, end);
	}

	void swap()
	{
		Container	tmp;

		container.swap(tmp);
	}

	void clear()
	{
		container.clear();
	}

	void find()
	{
		this->ret = container.find(2)->second;
	}

	void count()
	{
		this->ret = container.count(1);
	}

	void lower_bound()
	{
		this->ret = container.lower_bound(1)->first;
	}

	void upper_bound()
	{
		this->ret = container.upper_bound(1)->second;
	}

	void equal_range()
	{
		this->ret = container.equal_range(1).first->second;
	}
    Container& get_container()
    { return container; }

	int get_ret() const
	{ return ret; }

private:
    Container container;

	int		ret;
};

template<typename Key, typename Val>
class MultimapTester : public TesterBase
{
public:
    typedef typename std::multimap<Key, Val>            			master;
    typedef typename ft::Multimap<Key, Val>             			challenger;
    typedef typename std::multimap<Key, Val>::iterator  			master_iterator;
    typedef typename ft::Multimap<Key, Val>::iterator  			challenger_iterator;
	typedef typename std::multimap<Key, Val>::reverse_iterator	master_reverse_iterator;
	typedef typename ft::Multimap<Key, Val>::reverse_iterator	challenger_reverse_iterator;

    MultimapTester() : TesterBase("Multimap")
	{ init_what_to_test(); }

    MultimapTester(bool log_flag, std::string dir = "")
        : TesterBase("Multimap", log_flag, dir)
	{ init_what_to_test(); }

    ~MultimapTester() {}
    
    void start_test()
    {
		ASSERT(master_case.insert(), challenger_case.insert());
		ASSERT(master_case.lower_bound(), challenger_case.lower_bound());
		ASSERT(master_case.upper_bound(), challenger_case.upper_bound());
		ASSERT(master_case.equal_range(), challenger_case.equal_range());
		ASSERT(master_case.swap(), challenger_case.swap());
		ASSERT(master_case.insert(), challenger_case.insert());
		ASSERT(master_case.erase(), challenger_case.erase());
		ASSERT(master_case.find(), challenger_case.find());
		ASSERT(master_case.count(), challenger_case.count());
		ASSERT(master_case.clear(), challenger_case.clear());
	}

private:
	void init_what_to_test()
	{
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

		what_to_test.insert(std::make_pair("find", "compare_ret"));

		what_to_test.insert(std::make_pair("count", "compare_ret"));

		what_to_test.insert(std::make_pair("lower_bound", "compare_ret"));

		what_to_test.insert(std::make_pair("upper_bound", "compare_ret"));

		what_to_test.insert(std::make_pair("equal_range", "compare_ret"));
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
       	    if (challenger_it->first != master_it->first || \
				challenger_it->second != master_it->second)
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
       	    if (challenger_it->first != master_it->first || \
				challenger_it->second != master_it->second)
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
       	    if (challenger_it->first != master_it->first || \
				challenger_it->second != master_it->second)
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
       	    if (challenger_it->first != master_it->first || \
				challenger_it->second != master_it->second)
				return 1;
		}
		if (challenger_it != challenger_start || master_it != master_start)
			return 1;
		return 0;
	}

	int compare_ret()
	{
		Val master_ret = master_case.get_ret();
		Val challenger_ret = challenger_case.get_ret();

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

    MultimapTestCase<master, Key, Val>     	master_case;
    MultimapTestCase<challenger, Key, Val>  	challenger_case;
};

#endif /* FT_MULTIMAP_TESTER_HPP */
