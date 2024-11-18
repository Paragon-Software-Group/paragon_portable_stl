// ***************************************************************************
// * Copyright (c) 2024 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="is_trivially_copyable.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_IS_TRIVIALLY_COPYABLE_H
#define PSTL_IS_TRIVIALLY_COPYABLE_H

#include "../helper/integral_constant.h"

namespace portable_stl {

namespace type_properties_helper {
  /**
   * @brief A wrapper over a build-in function to add indirectness. Necessary for msvc.
   *
   * @tparam t_type Processed type.
   */
  template<class t_type> class is_trivially_copyable_wrapper final {
  public:
    /**
     * @brief Result type.
     */
    using type = ::portable_stl::bool_constant<__is_trivially_copyable(t_type)>;
  };
} // namespace type_properties_helper

/**
 * @brief Check t_type is a Trivially-copyable . ( Can copy by memcpy like functions. )
 * @tparam t_type type for check.
 */
template<class t_type>
using is_trivially_copyable = typename type_properties_helper::is_trivially_copyable_wrapper<t_type>::type;
} // namespace portable_stl

#endif // PSTL_IS_TRIVIALLY_COPYABLE_H