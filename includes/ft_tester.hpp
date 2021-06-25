#ifndef FT_TESTER_HPP
# define FT_TESTER_HPP

# include <iostream>
# include <algorithm>
# include <unistd.h>
# include <sys/wait.h>
# include <fstream>
# include <map>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define CYN "\033[36m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

static pid_t test_segv_pid;

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
		TEST_SEGV(y);							\
		if (!WIFEXITED(test_segv_pid)) {		\
			log_casefault(#y);					\
		}										\
		else {									\
			log_fail(#x);						\
		}										\
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

bool is_single_digit(const int& val)
{ return (val < 10); }

struct is_odd {
	bool operator()(const int& val)
	{ return (val % 2 == 1); }
};

bool my_compare(const int& a, const int& b)
{
	return (a < b);
}

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

		function_mapping["compare_size"] = &TesterBase::compare_size;
		function_mapping["compare_capacity"] = &TesterBase::compare_capacity;
		function_mapping["compare_iterator"] = &TesterBase::compare_iterator;
		function_mapping["compare_reverse_iterator"] = &TesterBase::compare_reverse_iterator;
		function_mapping["compare_ret"] = &TesterBase::compare_ret;
		function_mapping["compare_empty"] = &TesterBase::compare_empty;
	}

	~TesterBase() {}

	void log(const std::string &msg)
	{
		std::string out = trim_msg(msg);

		if (strm.connected)
			strm.fd << "[" << name << "] " << out << "\n";
		std::cout << CYN << "[" << name << "] " << out << "\n" << RESET;
	}

	virtual void start_test() = 0;

protected:
	typedef int (TesterBase::*cmp_func)();
	typedef std::multimap<std::string, std::string>	cmp_mapping;
	typedef std::map<std::string, cmp_func> 		func_mapping;

	void log_casefault(const std::string &msg)
	{
		std::string out = trim_msg(msg);

		if (strm.connected)
			strm.fd << "[" << name << "] " << std::setw(30) << std::left << out << std::right << "Wrong case!\n";
		std::cout << RED << "[" << name << "] " << std::setw(30) << std::left << out << std::right << "Wrong case!\n" << RESET;
	}

	void log_segfault(const std::string &msg)
	{
		std::string out = trim_msg(msg);

		if (strm.connected)
			strm.fd << "[" << name << "] " << std::setw(30) << std::left << out << std::right << "Segfault!\n";
		std::cout << RED << "[" << name << "] " << std::setw(30) << std::left << out << std::right << "Segfault!\n" << RESET;
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
		compare_container_shape(trim_msg(msg));
	}

	virtual int compare_size() = 0;
	virtual int compare_capacity() = 0;
	virtual int compare_iterator() = 0;
	virtual int compare_reverse_iterator() = 0;
	virtual int compare_ret() = 0;
	virtual int compare_empty() = 0;

	cmp_mapping			what_to_test;

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

	void compare_container_shape(const std::string& func_name)
	{
		typedef std::multimap<std::string, std::string>::iterator cmp_it;

		for (cmp_it it = what_to_test.begin(); it != what_to_test.end(); ++it)
		{
			if (it->first == func_name)
			{
				if ((this->*function_mapping[it->second])())
					log_fail("- " + it->second);
				else
					log_success("- " + it->second);
			}
		}
	}

	const std::string	name;
	Strm 				strm;
	func_mapping		function_mapping;
};

#endif /* FT_TESTER_HPP */
