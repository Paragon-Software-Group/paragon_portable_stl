// ***************************************************************************
// * Copyright (c) 2024 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="metaprogramming_type_relations.cpp"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#include <gtest/gtest.h>

#include "portable_stl/metaprogramming/type_relations/is_base_of.h"
#include "portable_stl/metaprogramming/type_relations/is_convertible.h"
#include "portable_stl/metaprogramming/type_relations/is_same.h"

#if defined(__cpp_inline_variables)
#  include "metaprogramming_type_relations_inline_variables.h"
#else
#  include "metaprogramming_type_relations.h"
#endif

#include "metaprogramming_type_relations_helper.h"

TEST(metaprogramming_type_relations, is_same) {
  static_cast<void>(test_info_);
  ASSERT_TRUE((::portable_stl::is_same<std::uint32_t, std::uint32_t>{}()));
  ASSERT_FALSE((::portable_stl::is_same<std::uint32_t, std::uint32_t const>{}()));
  ASSERT_FALSE((::portable_stl::is_same<std::uint32_t, std::uint32_t volatile>{}()));
  ASSERT_FALSE((::portable_stl::is_same<std::uint32_t, std::uint32_t const volatile>{}()));

  test_metaprogramming_type_relations::metaprogramming_type_relations_is_same_inline_variables();
}

TEST(metaprogramming_type_relations, is_convertible) {
  static_cast<void>(test_info_);

  /**
   * @brief Helper class for check impilicit conversion.
   *
   */
  class implicit_check final {
  public:
    /**
     * @brief Construct a new implicit check object = deleted.
     *
     */
    constexpr implicit_check() noexcept = delete;

    /**
     * @brief Construct a new implicit check object from void pointer.
     *
     */
    constexpr implicit_check(void *) noexcept {
    }

    /**
     * @brief Convert implicit check object to void pointer.
     *
     * @return void *
     */
    constexpr operator void *() const noexcept {
      return nullptr;
    }
  };

  /**
   * @brief Helper class for check explicit conversion.
   *
   */
  class explicit_check final {
  public:
    /**
     * @brief Construct a new explicit check object = deleted.
     *
     */
    constexpr explicit_check() noexcept = delete;

    /**
     * @brief Construct a new explicit check object from void pointer.
     *
     */
    constexpr explicit explicit_check(void *) noexcept {
    }

    /**
     * @brief Convert from explicit check object to void pointer.
     *
     * @return void *
     */
    constexpr explicit operator void *() const noexcept {
      return nullptr;
    }
  };

  {
    constexpr implicit_check checker{nullptr};
    ASSERT_EQ(nullptr, checker);
  }

  {
    constexpr explicit_check checker{nullptr};
    ASSERT_EQ(nullptr, static_cast<void *>(checker));
  }

  ASSERT_TRUE((::portable_stl::is_convertible<void, void>{}()));
  ASSERT_FALSE((::portable_stl::is_convertible<void, std::uint8_t>{}()));
  ASSERT_FALSE((::portable_stl::is_convertible<std::uint8_t, void>{}()));

  ASSERT_TRUE((::portable_stl::is_convertible<std::uint8_t, std::uint32_t>{}()));
  ASSERT_TRUE((::portable_stl::is_convertible<std::uint32_t, std::uint8_t>{}()));
  ASSERT_FALSE((::portable_stl::is_convertible<void *, std::uint8_t *>{}()));
  ASSERT_TRUE((::portable_stl::is_convertible<std::uint8_t *, void *>{}()));
  ASSERT_TRUE((::portable_stl::is_convertible<std::uint8_t *, void const *>{}()));
  ASSERT_TRUE((::portable_stl::is_convertible<std::uint8_t const *, void const *>{}()));

  ASSERT_FALSE((::portable_stl::is_convertible<std::uint8_t const *, void *>{}()));
  ASSERT_FALSE((::portable_stl::is_convertible<void const *, explicit_check>{}()));
  ASSERT_FALSE((::portable_stl::is_convertible<void *, explicit_check>{}()));
  ASSERT_FALSE((::portable_stl::is_convertible<explicit_check, void const *>{}()));
  ASSERT_FALSE((::portable_stl::is_convertible<explicit_check, void *>{}()));

  ASSERT_FALSE((::portable_stl::is_convertible<void const *, implicit_check>{}()));
  ASSERT_TRUE((::portable_stl::is_convertible<void *, implicit_check>{}()));
  ASSERT_TRUE((::portable_stl::is_convertible<implicit_check, void const *>{}()));
  ASSERT_TRUE((::portable_stl::is_convertible<implicit_check, void *>{}()));

  {
    constexpr ::portable_stl::is_convertible<void, void> checker{};
    ASSERT_TRUE((checker()));
    static_cast<void>(checker);
  }
  {
    constexpr ::portable_stl::is_convertible<std::uint8_t *, void *> checker{};
    ASSERT_TRUE((checker()));
    static_cast<void>(checker);
  }
  {
    constexpr ::portable_stl::is_convertible<void *, std::uint8_t *> checker{};
    ASSERT_FALSE((checker()));
    static_cast<void>(checker);
  }
}

TEST(metaprogramming_type_relations, is_base_of) {
  static_cast<void>(test_info_);

  {
    /**
     * @brief Helper type
     */
    using test_value_t = ::portable_stl::is_base_of<metaprogramming_type_relations_helper::Base1,
                                                    metaprogramming_type_relations_helper::Derived1>;

    ASSERT_TRUE((std::is_same<::portable_stl::true_type, test_value_t>{}()));
  }

  ASSERT_TRUE((::portable_stl::is_base_of<metaprogramming_type_relations_helper::Base1,
                                          metaprogramming_type_relations_helper::Derived1>{}()));
  ASSERT_TRUE((::portable_stl::is_base_of<metaprogramming_type_relations_helper::Derived1,
                                          metaprogramming_type_relations_helper::Derived2>{}()));
  ASSERT_TRUE((::portable_stl::is_base_of<metaprogramming_type_relations_helper::Base2,
                                          metaprogramming_type_relations_helper::Derived3>{}()));

  ASSERT_FALSE((::portable_stl::is_base_of<metaprogramming_type_relations_helper::Base2,
                                           metaprogramming_type_relations_helper::Derived1>{}()));
  ASSERT_FALSE((::portable_stl::is_base_of<metaprogramming_type_relations_helper::Base2,
                                           metaprogramming_type_relations_helper::Derived2>{}()));

  ASSERT_FALSE((::portable_stl::is_base_of<metaprogramming_type_relations_helper::Base1,
                                           metaprogramming_type_relations_helper::Derived3>{}()));

  ASSERT_FALSE((::portable_stl::is_base_of<std::uint32_t, std::uint32_t>{}()));

  // private base
  ASSERT_TRUE((::portable_stl::is_base_of<metaprogramming_type_relations_helper::Base1,
                                          metaprogramming_type_relations_helper::Derived2>{}()));
  // but still
  ASSERT_FALSE((::std::is_convertible<metaprogramming_type_relations_helper::Derived2 *,
                                      metaprogramming_type_relations_helper::Base1 *>{}()));

  test_metaprogramming_type_relations::metaprogramming_type_relations_is_base_of_inline_variables();
}
