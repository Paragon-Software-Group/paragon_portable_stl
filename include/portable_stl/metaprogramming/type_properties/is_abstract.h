// ***************************************************************************
// * Copyright (c) 2024 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="is_abstract.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_IS_ABSTRACT_H
#define PSTL_IS_ABSTRACT_H

#include "../helper/integral_constant.h"

namespace portable_stl {

namespace type_properties_helper {
  /**
   * @brief A wrapper over a build-in function to add indirectness. Necessary for msvc.
   *
   * @tparam t_type Processed type.
   */
  template<class t_type> class is_abstract_wrapper final {
  public:
    /**
     * @brief Result type.
     */
    using type = ::portable_stl::bool_constant<__is_abstract(t_type)>;
  };
} // namespace type_properties_helper

/**
 * @brief t_type is a abstract class type.
 *
 * @tparam t_type type for check.
 */
template<class t_type> using is_abstract = typename type_properties_helper::is_abstract_wrapper<t_type>::type;
} // namespace portable_stl

#endif // PSTL_IS_ABSTRACT_H
