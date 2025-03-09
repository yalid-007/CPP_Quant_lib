/** 
@file  sptr.hpp
@brief Aliases of common std::shared_ptr<T> types
*/

#ifndef QF_SPTR_HPP
#define QF_SPTR_HPP

#include <orflib/defines.hpp>
#include <memory>
#include <string>

BEGIN_NAMESPACE(qf)

using SPtrInt = std::shared_ptr<int>;
using SPtrLong = std::shared_ptr<long>;
using SPtrDouble = std::shared_ptr<double>;
using SPtrString = std::shared_ptr<std::string>;

END_NAMESPACE(qf)

#endif // QF_SPTR_HPP
