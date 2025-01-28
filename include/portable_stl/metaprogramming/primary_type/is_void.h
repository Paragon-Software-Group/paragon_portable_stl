// ***************************************************************************
// * Copyright (c) 2024-2025 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="is_void.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_IS_VOID_H
#define PSTL_IS_VOID_H

#include "../cv_modifications/remove_cv.h"
#include "../type_relations/is_same.h"

namespace portable_stl {
/**
 * @brief The t_type is void regardless cv modifications.
 *
 * @tparam t_type the type for check.
 */
template<class t_type> using is_void = ::portable_stl::is_same<::portable_stl::remove_cv_t<t_type>, void>;

} // namespace portable_stl

#endif // PSTL_IS_VOID_H
