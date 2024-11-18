// ***************************************************************************
// * Copyright (c) 2024 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="is_reference_wrapper.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_IS_REFERENCE_WRAPPER_H
#define PSTL_IS_REFERENCE_WRAPPER_H

#include "../../utility/general/functional/reference_wrapper.h"
#include "../helper/integral_constant.h"

namespace portable_stl {
namespace type_properties_helpers {
  /**
   * @brief t_type is reference wrapper type.
   * t_type is not reference wrapper implementation.
   * @tparam t_type the type for check.
   */
  template<class t_type> class is_reference_wrapper final {
  public:
    /**
     * @brief Result getter.
     *
     * @return false.
     */
    using type = ::portable_stl::false_type;
  };

  /**
   * @brief t_type is reference wrapper type.
   * t_type is reference wrapper implementation.
   * @tparam t_type the type for check.
   */
  template<class t_type> class is_reference_wrapper<::portable_stl::reference_wrapper<t_type>> final {
  public:
    /**
     * @brief Result getter.
     *
     * @return true.
     */
    using type = ::portable_stl::true_type;
  };
} // namespace type_properties_helpers

/**
 * @brief t_type is reference wrapper type.
 * @tparam t_type the type for check.
 */
template<class t_type>
using is_reference_wrapper = typename ::portable_stl::type_properties_helpers::is_reference_wrapper<t_type>::type;
} // namespace portable_stl

#endif // PSTL_IS_REFERENCE_WRAPPER_H
