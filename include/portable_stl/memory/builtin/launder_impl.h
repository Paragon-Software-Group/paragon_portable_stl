// ***************************************************************************
// * Copyright (c) 2024 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="launder_impl.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_LAUNDER_IMPL_H
#define PSTL_LAUNDER_IMPL_H

namespace portable_stl {
namespace memory_helper {

  /**
   * @brief Devirtualization fence with respect to p. Returns a pointer to the same memory that ptr points to, but where
   * the referent object is assumed to have a distinct lifetime and dynamic type.
   *
   * @tparam t_type
   * @param ptr
   * @return t_type*
   */
  template<class t_type> constexpr t_type *launder_impl(t_type *ptr) noexcept {
    return __builtin_launder(ptr);
  }
} // namespace memory_helper
} // namespace portable_stl

#endif // PSTL_LAUNDER_IMPL_H