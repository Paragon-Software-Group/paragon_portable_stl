// ***************************************************************************
// * Copyright (c) 2024 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="is_scalar_v.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_IS_SCALAR_V_H
#define PSTL_IS_SCALAR_V_H

#include "is_scalar.h"

namespace portable_stl {
/**
 * @brief t_type is an scalar type.
 * @tparam t_type the type for check.
 */
template<class t_type> constexpr inline bool is_scalar_v = ::portable_stl::is_scalar<t_type>{}();

} // namespace portable_stl

#endif // PSTL_IS_SCALAR_V_H
