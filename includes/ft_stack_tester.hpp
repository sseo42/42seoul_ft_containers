#ifndef FT_STACK_TESTER_HPP
# define FT_STACK_TESTER_HPP

# include "ft_tester.hpp"
# include "ft_stack.hpp"
# include <stack>

/**
 * 
 */

template<typename Container, typename Tp>
class StackTestCase
{
public:
    StackTestCase() {}

    ~StackTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class StackTestCase<Container, int>
{
public:
    StackTestCase() {}

    ~StackTestCase() {}

	void top()
	{
		this->ret = container.top();
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
class StackTestCase<Container, char>
{
public:
    StackTestCase() {}

    ~StackTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Container>
class StackTestCase<Container, bool>
{
public:
    StackTestCase() {}

    ~StackTestCase() {}

    Container& get_container()
    { return container; };

private:
    Container container;
};

template<typename Tp>
class StackTester : public TesterBase
{
public:
    typedef typename std::stack<Tp>            master;
    typedef typename ft::Stack<Tp>             challenger;

    StackTester() : TesterBase("Stack")
	{ init_what_to_test(); }

    StackTester(bool log_flag, std::string dir = "")
        : TesterBase("Stack", log_flag, dir)
	{ init_what_to_test(); }

    ~StackTester() {}
    
    void start_test()
    {
		ASSERT(master_case.push(), challenger_case.push());
		ASSERT(master_case.top(), challenger_case.top());
		ASSERT(master_case.pop(), challenger_case.pop());
	}

private:
	void init_what_to_test()
	{
		what_to_test.insert(std::make_pair("push", "compare_size"));
		what_to_test.insert(std::make_pair("push", "compare_empty"));

		what_to_test.insert(std::make_pair("top", "compare_ret"));

		what_to_test.insert(std::make_pair("pop", "compare_size"));
		what_to_test.insert(std::make_pair("pop", "compare_empty"));
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

    StackTestCase<master, Tp>      		master_case;
    StackTestCase<challenger, Tp>  		challenger_case;
};

#endif /* FT_STACK_TESTER_HPP */
