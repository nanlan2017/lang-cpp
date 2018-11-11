#ifndef h_prelude_boost
#define h_prelude_boost

//! mpl
// 算术
#include <boost/mpl/int.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/equal_to.hpp>  // 值相等性
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/size_t.hpp>
//#include <boost/mpl/apply_wrap.hpp>

// 控制流程
#include <boost/mpl/if.hpp>
#include <boost/mpl/switch.hpp>
#include <boost/mpl/for_each.hpp>

// 函数式
#include <boost/mpl/fold.hpp>
#include <boost/mpl/transform.hpp>  // map,zip
#include <boost/mpl/identity.hpp>
#include <boost/mpl/unique.hpp>  
#include <boost/mpl/lower_bound.hpp>  
// view
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/zip_view.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/unpack_args.hpp>


// 静态版"STL"
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector/vector50.hpp>

#include <boost/mpl/list.hpp>

#include <boost/mpl/map.hpp>


#include <boost/mpl/pop_back.hpp>
//-------------------------------
#include <boost/mpl/equal.hpp>  // 序列相等性
#include <boost/mpl/find.hpp>
#include <boost/mpl/replace.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/copy.hpp>

//! preprocessor
//todo  其中的Macro均以 BOOST_PP_...  开头
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/arithmetic.hpp>
#include <boost/preprocessor/punctuation.hpp>
#include <boost/preprocessor/iteration.hpp>


//! type_traits
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/is_empty.hpp>

#include <boost/type_traits/add_reference.hpp>

//x-------------------------------------------------------------------------------------------------
//! fusion （融合分类）


//! other
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/iterator/iterator_traits.hpp>



namespace mpl = boost::mpl;

#endif // h_prelude_boost
