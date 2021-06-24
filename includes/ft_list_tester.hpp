#ifndef FT_LIST_TESTER_HPP
# define FT_LIST_TESTER_HPP

# include "ft_tester.hpp"
# include "ft_list.hpp"
# include <list>

/**
 * 
 */

template<typename Container, typename Tp>
class ListTestCase
{
public:
    typedef typename Container::iterator    iterator;

    ListTestCase() {}

    ~ListTestCase() {}

	iterator begin()
	{ return container.begin(); }

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class ListTestCase<Container, int>
{
public:
    typedef typename Container::iterator    iterator;

    ListTestCase() {}

    ~ListTestCase() {}

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
		Container tmp;

		tmp.assign(1000, 42);
		container.assign(tmp.begin(), tmp.end());
	}

	void resize()
	{
		container.resize(10);
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
		for (int i = 100; i < 200; ++i)
		{
			container.push_front(i);
		}
	}

	void pop_front()
	{
		for (int i = 200; i < 250; ++i)
		{
			container.pop_front();
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
		container.clear();
	}

	void splice()
	{
		typename Container::iterator tmp_it;
		typename Container::iterator container_it;
		Container tmp(100);
		Container tmp2(200);
		Container tmp3(300);

		container_it = container.begin();
		++container_it;
		container.splice(container_it, tmp);

		container_it = container.begin();
		++container_it;
		++container_it;
		tmp_it = tmp2.begin();
		++tmp_it;
		++tmp_it;
		container.splice(container_it, tmp2, tmp_it);

		container_it = container.begin();
		++container_it;
		++container_it;
		++container_it;
		tmp_it = tmp3.begin();
		++tmp_it;
		++tmp_it;
		++tmp_it;
		container.splice(container_it, tmp3, tmp_it, tmp3.end());
	}

	void remove()
	{
		container.remove(0);
		container.remove(1004);
	}

	void remove_if()
	{
		for (int i = 0; i < 100; ++i)
		{
			container.remove_if(is_single_digit);
		}
		container.remove_if(is_odd());
	}

	void unique()
	{
		container.unique();
		container.unique(my_compare);
	}

	void merge()
	{
		Container tmp(100, 100);
		Container tmp2(200, 200);

		container.merge(tmp);
		container.merge(tmp2, my_compare);
	}

	void sort()
	{
		container.sort();
	}

	void reverse()
	{
		container.reverse();
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
class ListTestCase<Container, char>
{
public:
    typedef typename Container::iterator    iterator;

    ListTestCase() {}

    ~ListTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class ListTestCase<Container, bool>
{
public:
    typedef typename Container::iterator    iterator;

    ListTestCase() {}

    ~ListTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Tp>
class ListTester : public TesterBase
{
public:
    typedef typename std::list<Tp>						master;
    typedef typename ft::List<Tp>             			challenger;
    typedef typename std::list<Tp>::iterator  			master_iterator;
    typedef typename ft::List<Tp>::iterator   			challenger_iterator;
	typedef typename std::list<Tp>::reverse_iterator 	master_reverse_iterator;
	typedef typename ft::List<Tp>::reverse_iterator 	challenger_reverse_iterator;

    ListTester() : TesterBase("List")
	{ init_what_to_test(); }

    ListTester(bool log_flag, std::string dir = "")
        : TesterBase("List", log_flag, dir)
	{ init_what_to_test(); }

    ~ListTester() {}
    
    void start_test()
    {
		ASSERT(master_case.resize(), challenger_case.resize());
		ASSERT(master_case.push_back(), challenger_case.push_back());
		ASSERT(master_case.pop_back(), challenger_case.pop_back());
		ASSERT(master_case.push_front(), challenger_case.push_front());
		ASSERT(master_case.pop_front(), challenger_case.pop_front());
		ASSERT(master_case.insert(), challenger_case.insert());
		ASSERT(master_case.front(), challenger_case.front());
		ASSERT(master_case.back(), challenger_case.back());
		ASSERT(master_case.erase(), challenger_case.erase());
		ASSERT(master_case.assign(), challenger_case.assign());
		ASSERT(master_case.unique(), challenger_case.unique());
		ASSERT(master_case.splice(), challenger_case.splice());
		ASSERT(master_case.clear(), challenger_case.clear());
		ASSERT(master_case.splice(), challenger_case.splice());
		ASSERT(master_case.remove(), challenger_case.remove());
		ASSERT(master_case.remove_if(), challenger_case.remove_if());
		ASSERT(master_case.merge(), challenger_case.merge());
		ASSERT(master_case.push_front(), challenger_case.push_front());
		ASSERT(master_case.sort(), challenger_case.sort());
		ASSERT(master_case.push_front(), challenger_case.push_front());
		ASSERT(master_case.reverse(), challenger_case.reverse());
	}

private:
	void init_what_to_test()
	{
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

		what_to_test.insert(std::make_pair("push_front", "compare_size"));
		what_to_test.insert(std::make_pair("push_front", "compare_iterator"));
		what_to_test.insert(std::make_pair("push_front", "compare_reverse_iterator"));

		what_to_test.insert(std::make_pair("pop_front", "compare_size"));
		what_to_test.insert(std::make_pair("pop_front", "compare_iterator"));
		what_to_test.insert(std::make_pair("pop_front", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("pop_front", "compare_empty"));

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

		what_to_test.insert(std::make_pair("resize", "compare_size"));
		what_to_test.insert(std::make_pair("resize", "compare_iterator"));
		what_to_test.insert(std::make_pair("resize", "compare_reverse_iterator"));

		what_to_test.insert(std::make_pair("clear", "compare_size"));
		what_to_test.insert(std::make_pair("clear", "compare_iterator"));
		what_to_test.insert(std::make_pair("clear", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("clear", "compare_empty"));

		what_to_test.insert(std::make_pair("splice", "compare_size"));
		what_to_test.insert(std::make_pair("splice", "compare_iterator"));
		what_to_test.insert(std::make_pair("splice", "compare_reverse_iterator"));

		what_to_test.insert(std::make_pair("remove", "compare_size"));
		what_to_test.insert(std::make_pair("remove", "compare_iterator"));
		what_to_test.insert(std::make_pair("remove", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("remove", "compare_empty"));

		what_to_test.insert(std::make_pair("remove_if", "compare_size"));
		what_to_test.insert(std::make_pair("remove_if", "compare_iterator"));
		what_to_test.insert(std::make_pair("remove_if", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("remove_if", "compare_empty"));

		what_to_test.insert(std::make_pair("unique", "compare_size"));
		what_to_test.insert(std::make_pair("unique", "compare_iterator"));
		what_to_test.insert(std::make_pair("unique", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("unique", "compare_empty"));

		what_to_test.insert(std::make_pair("merge", "compare_size"));
		what_to_test.insert(std::make_pair("merge", "compare_iterator"));
		what_to_test.insert(std::make_pair("merge", "compare_reverse_iterator"));
		what_to_test.insert(std::make_pair("merge", "compare_empty"));

		what_to_test.insert(std::make_pair("sort", "compare_iterator"));
		what_to_test.insert(std::make_pair("sort", "compare_reverse_iterator"));

		what_to_test.insert(std::make_pair("reverse", "compare_iterator"));
		what_to_test.insert(std::make_pair("reverse", "compare_reverse_iterator"));
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

    ListTestCase<master, Tp>      		master_case;
    ListTestCase<challenger, Tp>  		challenger_case;
};

#endif /* FT_LIST_TESTER_HPP */
