// ***************************************************************************
// * Copyright (c) 2024 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="is_trivially_copy_constructible.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_H
#define PSTL_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_H

#include "../cv_modifications/add_const.h"
#include "../reference_modifications/add_lvalue_reference.h"
#include "is_trivially_constructible.h"

namespace portable_stl {

/**
 * @brief Check t_type is a copy Trivially-constructible . ( Can copy construct with trivial function. )
 * @tparam t_type type for check.
 */
template<class t_type>
using is_trivially_copy_constructible = ::portable_stl::
  is_trivially_constructible<t_type, ::portable_stl::add_lvalue_reference_t<::portable_stl::add_const_t<t_type>>>;
} // namespace portable_stl

#endif // PSTL_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_H