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

# include <vector>
# include <list>
# include <stack>
# include <queue>
# include <map>
# include <set>

# include <iostream>
# include <algorithm>
# include <unistd.h>
# include <sys/wait.h>
# include <fstream>

static pid_t test_segv_pid;

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

# define TEST_SEGV(x) do {				\
	test_segv_pid = fork()				\
	if (test_segv_pid == -1) abort();	\
	if (test_segv_pid == 0) {			\
		do { (void)(x); } while (0);	\
		exit(EXIT_SUCCESS);				\
	}									\
	wait(&test_segv_pid);				\
} while (0)

# define ASSERT(x) do {									\
	TEST_SEGV(x);										\
	if (!WIFEXITED(test_segv_pid)) log_segfault(#x);	\
	else compare_containers_shape(#x);					\
} while (0)

class TesterBase
{
public:
	TesterBase(std::string name, bool log_flag = false, std::string dir = "")
		: name(name), strm(log_flag)
	{
		if (log_flag)
		{
			if (dir != "" && dir[dir.length() - 1] != '/')
				dir += "/";

			std::string log_path = dir + name + ".result";
		    try
			{
				strm.fd.open(log_path.c_str(), std::fstream::out | std::fstream::trunc);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				throw ;
			}
		}
	}

	~TesterBase() {}

	virtual void start_test() = 0;

protected:
	struct Strm
	{
		Strm() : connected(false) {}
		Strm(bool log_flag) : connected(log_flag) {}

		~Strm()
		{
			if (connected)
				fd.close();
		}

		const bool			connected;
		std::fstream		fd;
	};

	void log_case(const std::string &current_test)
	{
		if (strm.connected)
			strm.fd << "[" << name << "] " << current_test << "\n";
		std::cout << GREEN << "[" << name << "] " << current_test << "\n" << RESET;
	}

	void log_casefault(const std::string &current_test)
	{
		if (strm.connected)
			strm.fd << "[" << name << "] " << current_test << ": " << "Wrong case!\n";
		std::cerr << RED << "[" << name << "] " << current_test << ": " << "Wrong case!\n" << RESET;
	}

	void log_segfault(const std::string &current_test)
	{
		if (strm.connected)
			strm.fd << "[" << name << "] " << current_test << ": " << "Segfault!\n";
		std::cout << RED << "[" << name << "] " << current_test << ": " << "Segfault!\n" << RESET;
	}

	void log_fail(const std::string &current_test)
	{
		if (strm.connected)
			strm.fd << "[" << name << "] " << current_test << ": " << "diff ko :(\n";
		std::cout << RED << "[" << name << "] " << current_test << ": " << "diff ko :(\n" << RESET;
	}

	void log_success(const std::string &current_test)
	{
		if (strm.connected)
			strm.fd << "[" << name << "] " << current_test << ": " << "diff ok :)\n";
		std::cout << GREEN << "[" << name << "] " << current_test << ": " << "diff ok :)\n" << RESET;
	}

	virtual void compare_containers_shape(const std::string &) = 0;

	const std::string	name;
	Strm 				strm;

private:
	TesterBase()
	{
		/* forbidden */
	}
};

#endif /* FT_TESTER_HPP */
