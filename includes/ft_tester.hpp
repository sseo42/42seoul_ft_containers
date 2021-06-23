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
	test_segv_pid = fork();				\
	if (test_segv_pid == -1) abort();	\
	if (test_segv_pid == 0) {			\
		do { (void)(x); } while (0);	\
		exit(EXIT_SUCCESS);				\
	}									\
	wait(&test_segv_pid);				\
} while (0)

# define ASSERT(x, y) do {						\
	TEST_SEGV(x);								\
	if (!WIFEXITED(test_segv_pid)) {			\
		log_casefault(#x);						\
	}											\
	else {										\
		TEST_SEGV(y);							\
		if (!WIFEXITED(test_segv_pid)) {		\
			log_segfault(#y);					\
		}										\
		else {									\
			(void)(x); (void)(y);				\
			evaluate_function(#y);				\
		}										\
	}											\
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

	void log(const std::string &msg)
	{
		std::string out = trim_msg(msg);

		if (strm.connected)
			strm.fd << "[" << name << "] " << out << "\n";
		std::cout << GREEN << "[" << name << "] " << out << "\n" << RESET;
	}

	virtual void start_test() = 0;

protected:
	void log_casefault(const std::string &msg)
	{
		std::string out = trim_msg(msg);

		if (strm.connected)
			strm.fd << "[" << name << "] " << out << std::setw(5) << "Wrong case!\n";
		std::cerr << RED << "[" << name << "] " << out << std::setw(5) << "Wrong case!\n" << RESET;
	}

	void log_segfault(const std::string &msg)
	{
		std::string out = trim_msg(msg);

		if (strm.connected)
			strm.fd << "[" << name << "] " << out << "-> " << "Segfault!\n";
		std::cout << RED << "[" << name << "] " << out << "-> " << "Segfault!\n" << RESET;
	}

	void log_fail(const std::string &msg)
	{
		std::string out = trim_msg(msg);

		if (strm.connected)
			strm.fd << "[" << name << "] " << std::setw(30) << std::left << out << std::right << "ko :(\n";
		std::cout << RED << "[" << name << "] " << std::setw(30) << std::left << out << std::right << "ko :(\n" << RESET;
	}

	void log_success(const std::string &msg)
	{
		std::string out = trim_msg(msg);

		if (strm.connected)
			strm.fd << "[" << name << "] " << std::setw(30) << std::left << out << std::right << "ok :)\n";
		std::cout << GREEN << "[" << name << "] " << std::setw(30) << std::left << out << std::right << "ok :)\n" << RESET;
	}

	void evaluate_function(const std::string &msg)
	{
		log_success(msg);
		compare_container_shape();
	}

private:
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

	TesterBase()
	{
		/* forbidden */
	}

	TesterBase(const TesterBase& src)
	{
		(void)(src);
		/* forbidden */
	}

	TesterBase& operator=(const TesterBase& src)
	{
		(void)(src);
		return *this;
		/* forbidden */
	}

	std::string trim_msg(const std::string& msg)
	{
		std::string out;

		std::size_t dot_found = msg.find(".");
		std::size_t parenthesis_found = msg.find("(");
		if (dot_found != std::string::npos)
			out = msg.substr(dot_found + 1, parenthesis_found - dot_found - 1);
		else
			out = msg.substr(0, parenthesis_found - 1);
		return out;
	}

	virtual void compare_container_shape() = 0;

	const std::string	name;
	Strm 				strm;
};

#endif /* FT_TESTER_HPP */
