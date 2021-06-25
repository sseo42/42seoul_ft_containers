#ifndef FT_DEQUE_TESTER_HPP
# define FT_DEQUE_TESTER_HPP

# include "ft_tester.hpp"
# include "ft_deque.hpp"
# include <deque>

/**
 * 
 */

template<typename Container, typename Tp>
class DequeTestCase
{
public:
    typedef typename Container::iterator    iterator;

    DequeTestCase() {}

    ~DequeTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class DequeTestCase<Container, int>
{
public:
    typedef typename Container::iterator    iterator;

    DequeTestCase() {}

    ~DequeTestCase() {}

	void resize()
	{
		container.resize(10);
	}

	void operator_braket()
	{
		container[3] = 1004;
		this->ret = container[3];
	}

	void at()
	{
		container.at(0) = 42;
		this->ret = container.at(0);
	}

	void front()
	{
		this->ret = container.front();
	}

	void back()
	{
		this->ret = container.back();
	}

	void assign()
	{
		container.assign(100, 52);
	}

	void push_back()
	{
		for (int i = 1; i < 10; ++i)
		{
			container.push_back(i);
		}
	}

	void pop_back()
	{
		for (int i = 0; i < 5; ++i)
		{
			container.pop_back();
		}
	}

	void push_front()
	{
		for (int i = -300; i < 300; ++i)
		{
			container.push_back(i);
		}
	}

	void pop_front()
	{
		for (int i = 0; i < 50; ++i)
		{
			container.pop_back();
		}
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
		Container tmp(400);

		tmp.clear();
		container = tmp;
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
class DequeTestCase<Container, char>
{
public:
    typedef typename Container::iterator    iterator;

    DequeTestCase() {}

    ~DequeTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class DequeTestCase<Container, bool>
{
public:
    typedef typename Container::iterator    iterator;

    DequeTestCase() {}

    ~DequeTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Tp>
class DequeTester : public TesterBase
{
public:
    typedef typename std::deque<Tp>            master;
    typedef typename ft::Deque<Tp>             challenger;
    typedef typename std::deque<Tp>::iterator  master_iterator;
    typedef typename ft::Deque<Tp>::iterator   challenger_iterator;
	typedef typename std::deque<Tp>::reverse_iterator master_reverse_iterator;
	typedef typename ft::Deque<Tp>::reverse_iterator challenger_reverse_iterator;

    DequeTester() : TesterBase("Deque")
	{ init_what_to_test(); }

    DequeTester(bool log_flag, std::string dir = "")
        : TesterBase("Deque", log_flag, dir)
	{ init_what_to_test(); }

    ~DequeTester() {}
    
    void start_test()
    {
		ASSERT(master_case.resize(), challenger_case.resize());
		ASSERT(master_case.push_back(), challenger_case.push_back());
		ASSERT(master_case.pop_back(), challenger_case.pop_back());
		ASSERT(master_case.operator_braket(), challenger_case.operator_braket());
		ASSERT(master_case.insert(), challenger_case.insert());
		ASSERT(master_case.at(), challenger_case.at());
		ASSERT(master_case.front(), challenger_case.front());
		ASSERT(master_case.back(), challenger_case.back());
		ASSERT(master_case.erase(), challenger_case.erase());
		ASSERT(master_case.assign(), challenger_case.assign());
		ASSERT(master_case.swap(), challenger_case.swap());
		ASSERT(master_case.push_front(), challenger_case.push_front());
		ASSERT(master_case.pop_front(), challenger_case.pop_front());
		ASSERT(master_case.clear(), challenger_case.clear());
	}

private:
	void init_what_to_test()
	{
		what_to_test.insert(std::make_pair("resize", "compare_size"));
		what_to_test.insert(std::make_pair("resize", "compare_iterator"));
		what_to_test.insert(std::make_pair("resize", "compare_reverse_iterator"));

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

		/*
		what_to_test.insert(std::make_pair("clear", "compare_size"));
		what_to_test.insert(std::make_pair("clear", "compare_iterator"));
		what_to_test.insert(std::make_pair("clear", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("clear", "compare_empty"));
	*/

		what_to_test.insert(std::make_pair("push_front", "compare_size"));
		what_to_test.insert(std::make_pair("push_front", "compare_iterator"));
		what_to_test.insert(std::make_pair("push_front", "compare_reverse_iterator"));

		what_to_test.insert(std::make_pair("pop_front", "compare_size"));
		what_to_test.insert(std::make_pair("pop_front", "compare_iterator"));
		what_to_test.insert(std::make_pair("pop_front", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("pop_front", "compare_empty"));
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

    DequeTestCase<master, Tp>      		master_case;
    DequeTestCase<challenger, Tp>  		challenger_case;
};

#endif /* FT_DEQUE_TESTER_HPP */
