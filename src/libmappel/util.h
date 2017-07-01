
#ifndef _UTIL_H
#define _UTIL_H
#include <cmath>
#include <cassert>
#include <memory>
#include <utility>
#include <armadillo>
#include <stdexcept>
#include <map>

namespace mappel {
    
// Do we need this still
// extern const std::vector<std::string> model_names;

    
using BoolT = uint16_t;
using IVecT = arma::Col<int>; /**< A type to represent integer data arrays */
using UVecT = arma::Col<unsigned>; /**< A type to represent unsigned integers and boolean data arrays */
using VecT = arma::vec; /**< A type to represent floating-point data arrays */
using MatT = arma::mat; /**< A type to represent floating-point data matricies */
using IMatT = arma::Mat<int>; /**< A type to represent floating-point data matricies */
using CubeT = arma::cube; /**< A type to represent floating-point data cubes */
using VecFieldT = arma::field<VecT>;
using StatsT = std::map<std::string,double>;  /**< A convenient form for reporting dictionaries of named FP data to matlab */

void enable_all_cpus();

bool istarts_with(const char* s, const char* pattern);
const char * icontains(const char* s, const char* pattern);


/** @brief sign (signum) function: -1/0/1
 * 
 */
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


class MappelException : public std::exception
{
protected:
    std::string msg;
public:
    MappelException(const std::string brief, const std::string &message)
    {
        std::ostringstream stream;
        stream<<"Mappel:"<<brief<<":"<<message;
        msg = stream.str();
    }
    
    const char* what() const throw()
    {
        return msg.c_str();
    }
};

class BadInputException : public MappelException 
{
public:
    BadInputException(const std::string &message) : MappelException("BadInput",message) {}
};

class NumericalException : public MappelException 
{
public:
    NumericalException(const std::string &message) : MappelException("Numerical",message) {}
};


inline double restrict_value_range(double val, double minval, double maxval)
{
    if(!std::isfinite(val)) throw NumericalException("Non-finite value in restrict_value_range.");
    return (val<minval) ? minval : ((val>maxval) ? maxval : val);
}


class MaximizerNotImplementedException : public MappelException 
{
public:
    MaximizerNotImplementedException(const std::string &message) : MappelException("MaximizerNotImplemented",message) {}
};

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

int maxidx(const VecT &v);

} /* namespace mappel */

/* Statistics Functions */



#endif /* _UTIL_H */
