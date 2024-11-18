// ***************************************************************************
// * Copyright (c) 2024 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="is_unbounded_array_v.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_IS_UNBOUNDED_ARRAY_V_H
#define PSTL_IS_UNBOUNDED_ARRAY_V_H

#include "is_unbounded_array.h"

namespace portable_stl {
/**
 * @brief t_type is an array type of unknown bound.
 *
 * @tparam t_type type for check.
 */
template<class t_type> constexpr inline bool is_unbounded_array_v = ::portable_stl::is_unbounded_array<t_type>{}();
} // namespace portable_stl

#endif // PSTL_IS_UNBOUNDED_ARRAY_V_H
