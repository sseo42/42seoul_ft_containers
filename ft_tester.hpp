#ifndef FT_TESTER_HPP
# define FT_TESTER_HPP

# include <iostream>

template<typename Vector>
class Vector_tester
{
public:
    typedef typename Vector::iterator       iterator;

    Vector_tester() {}
    Vector_tester(const Vector& target) : vector(target) {}

    void test()
    {
        vector.push_back(1);
        vector.push_back(2);
        vector.push_back(3);
        vector.push_back(4);

        for (iterator it = vector.begin(); it != vector.end(); ++it)
            std::cout << "test ans: " << *it << std::endl;
    }

    Vector vector;
};

#endif