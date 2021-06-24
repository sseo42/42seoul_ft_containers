#ifndef FT_QUEUE_TESTER_HPP
# define FT_QUEUE_TESTER_HPP

# include "ft_tester.hpp"
# include "ft_queue.hpp"
# include <queue>

/**
 * 
 */

template<typename Container, typename Tp>
class QueueTestCase
{
public:
    QueueTestCase() {}

    ~QueueTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class QueueTestCase<Container, int>
{
public:
    QueueTestCase() {}

    ~QueueTestCase() {}

	void front()
	{
		this->ret = container.front();
	}

	void back()
	{
		this->ret = container.back();
	}

	void push()
	{
		for (int i = 2; i < 5152; i+=2)
			container.push(i);
	}

	void pop()
	{
		for (int i = 0; i < 100; ++i)
			container.pop();
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
class QueueTestCase<Container, char>
{
public:
    QueueTestCase() {}

    ~QueueTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class QueueTestCase<Container, bool>
{
public:
    QueueTestCase() {}

    ~QueueTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Tp>
class QueueTester : public TesterBase
{
public:
    typedef typename std::queue<Tp>            master;
    typedef typename ft::Queue<Tp>             challenger;

    QueueTester() : TesterBase("Queue")
	{ init_what_to_test(); }

    QueueTester(bool log_flag, std::string dir = "")
        : TesterBase("Queue", log_flag, dir)
	{ init_what_to_test(); }

    ~QueueTester() {}
    
    void start_test()
    {
		ASSERT(master_case.push(), challenger_case.push());
		ASSERT(master_case.pop(), challenger_case.pop());
		ASSERT(master_case.front(), challenger_case.front());
		ASSERT(master_case.back(), challenger_case.back());
	}

private:
	void init_what_to_test()
	{
		what_to_test.insert(std::make_pair("push", "compare_size"));
		what_to_test.insert(std::make_pair("push", "compare_empty"));

		what_to_test.insert(std::make_pair("pop", "compare_size"));
		what_to_test.insert(std::make_pair("pop", "compare_empty"));

		what_to_test.insert(std::make_pair("front", "compare_ret"));
		what_to_test.insert(std::make_pair("back", "compare_ret"));
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
		return 0;
	}

	int compare_reverse_iterator()
	{
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

    QueueTestCase<master, Tp>      		master_case;
    QueueTestCase<challenger, Tp>  		challenger_case;
};

#endif /* FT_QUEUE_TESTER_HPP */
