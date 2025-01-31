// ***************************************************************************
// * Copyright (c) 2024-2025 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="multimap_lookup.cpp"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#include <gtest/gtest.h>

#include <portable_stl/map/multimap.h>

#include "../common/test_allocator.h"

using t_map_value_type = ::portable_stl::tuple<std::int32_t const, double>;

using t_allocator2 = test_allocator_helper::test_allocator<t_map_value_type>;

// using t_compare = test_common_helper::test_less<std::int32_t>;

using t_map = ::portable_stl::multimap<std::int32_t, double>;

//       iterator find(const key_type& k);
// const_iterator find(const key_type& k) const;
TEST(multimap, find) {
  static_cast<void>(test_info_);

  t_map_value_type arr[] = {t_map_value_type(5, 1),
                            t_map_value_type(5, 2),
                            t_map_value_type(5, 3),
                            t_map_value_type(7, 1),
                            t_map_value_type(7, 2),
                            t_map_value_type(7, 3),
                            t_map_value_type(9, 1),
                            t_map_value_type(9, 2),
                            t_map_value_type(9, 3)};

  {
    t_map mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

    auto iter = mp.find(5);
    ASSERT_EQ(mp.begin(), iter);

    iter = mp.find(6);
    ASSERT_EQ(mp.end(), iter);

    iter = mp.find(7);
    ASSERT_EQ(::portable_stl::next(mp.begin(), 3), iter);

    iter = mp.find(8);
    ASSERT_EQ(mp.end(), iter);

    iter = mp.find(9);
    ASSERT_EQ(::portable_stl::next(mp.begin(), 6), iter);

    iter = mp.find(10);
    ASSERT_EQ(mp.end(), iter);
  }

  // const
  {
    t_map const mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

    auto iter = mp.find(5);
    ASSERT_EQ(mp.begin(), iter);
    ASSERT_TRUE((std::is_same<typename t_map::const_iterator, decltype(iter)>{}));

    iter = mp.find(6);
    ASSERT_EQ(mp.end(), iter);

    iter = mp.find(7);
    ASSERT_EQ(::portable_stl::next(mp.begin(), 3), iter);

    iter = mp.find(8);
    ASSERT_EQ(mp.end(), iter);

    iter = mp.find(9);
    ASSERT_EQ(::portable_stl::next(mp.begin(), 6), iter);

    iter = mp.find(10);
    ASSERT_EQ(mp.end(), iter);
  }
}

namespace test_multimap_helper {
struct FAT_key {
  std::int32_t m_int;
  std::int32_t m_data[1000]; // heavy part
};

struct Light_key {
  std::int32_t m_int;
};

// for use by comparator

static bool operator<(FAT_key const &fk, Light_key const &lk) {
  return fk.m_int < lk.m_int;
}

static bool operator<(Light_key const &lk, FAT_key const &fk) {
  return lk.m_int < fk.m_int;
}

static bool operator<(FAT_key const &fk1, FAT_key const &fk2) {
  return fk1.m_int < fk2.m_int;
}

} // namespace test_multimap_helper

//       iterator find(const t_key_like_type& key_like);
// const_iterator find(const t_key_like_type& key_like) const;
TEST(multimap, find_transparent) {
  static_cast<void>(test_info_);

  /**
   * @brief Map value alias.
   */
  using t_map_FAT_value_type = ::portable_stl::tuple<test_multimap_helper::FAT_key, std::int32_t>;

  /**
   * @brief Map alias.
   */
  using t_mapFAT = ::portable_stl::multimap<test_multimap_helper::FAT_key, std::int32_t, ::portable_stl::less<>>;

  t_map_FAT_value_type arr[] = {t_map_FAT_value_type({5, {}}, 1),
                                t_map_FAT_value_type({5, {}}, 6),
                                t_map_FAT_value_type({5, {}}, 7),
                                t_map_FAT_value_type({8, {}}, 8),
                                t_map_FAT_value_type({8, {}}, 9),
                                t_map_FAT_value_type({8, {}}, 10),
                                t_map_FAT_value_type({10, {}}, 11),
                                t_map_FAT_value_type({10, {}}, 12)};

  {
    t_mapFAT mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

    test_multimap_helper::Light_key const lkey{8};

    auto result = mp.find(lkey);
    EXPECT_EQ(::portable_stl::next(mp.begin(), 3), result);
  }

  // constant
  {
    t_mapFAT const mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

    test_multimap_helper::Light_key const lkey{10};

    auto result = mp.find(lkey);
    EXPECT_EQ(::portable_stl::next(mp.begin(), 6), result);
  }
}

// size_type count(const key_type& k) const;
TEST(multimap, count) {
  static_cast<void>(test_info_);

  t_map_value_type arr[] = {t_map_value_type(5, 1),
                            t_map_value_type(5, 2),
                            t_map_value_type(5, 3),
                            t_map_value_type(7, 1),
                            t_map_value_type(7, 2),
                            t_map_value_type(7, 3),
                            t_map_value_type(9, 1),
                            t_map_value_type(9, 2),
                            t_map_value_type(9, 3)};

  t_map const mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

  /**
   * @brief Key alias.
   */
  using t_key_type = typename t_map::key_type;

  auto result = mp.count(t_key_type(4));
  ASSERT_EQ(0, result);
  result = mp.count(t_key_type(5));
  ASSERT_EQ(3, result);
  result = mp.count(t_key_type(6));
  ASSERT_EQ(0, result);
  result = mp.count(t_key_type(7));
  ASSERT_EQ(3, result);
  result = mp.count(t_key_type(8));
  ASSERT_EQ(0, result);
  result = mp.count(t_key_type(9));
  ASSERT_EQ(3, result);
  result = mp.count(t_key_type(10));
  ASSERT_EQ(0, result);
}

namespace test_multimap_helper {
class compare_pair_trans final {
public:
  bool operator()(std::pair<std::int32_t, std::int32_t> const &lhs,
                  std::pair<std::int32_t, std::int32_t> const &rhs) const {
    return lhs < rhs;
  }

  bool operator()(std::pair<std::int32_t, std::int32_t> const &lhs, std::int32_t rhs) const {
    return lhs.first < rhs;
  }

  bool operator()(std::int32_t lhs, std::pair<std::int32_t, std::int32_t> const &rhs) const {
    return lhs < rhs.first;
  }

  using is_transparent = void;
};
} // namespace test_multimap_helper

// size_type count(const key_type& k) const;
TEST(multimap, count_transparent) {
  static_cast<void>(test_info_);

  ::portable_stl::
    multimap<std::pair<std::int32_t, std::int32_t>, std::int32_t, test_multimap_helper::compare_pair_trans>
      mp({
        {{2, 1}, 1},
        {{1, 1}, 2}, // hit
        {{1, 1}, 3}, // hit
        {{1, 1}, 4}, // hit
        {{2, 2}, 5}
  });

  ASSERT_EQ(3, mp.count(1));
}

namespace test_multimap_helper {
template<class t_map, class t_map_value_pair, class t_bad, class... t_pairs>
void test_map_contains(t_bad bad, t_pairs... args) {
  t_map            mp;
  t_map_value_pair pairs[] = {args...};

  for (auto &p : pairs) {
    mp.insert(p);
  }

  for (auto &p : pairs) {
    ASSERT_TRUE(mp.contains(::portable_stl::get<0>(p)));
  }

  ASSERT_FALSE(mp.contains(bad));
}

struct complex_value {
  int    a = 1;
  double b = 1;
  char   c = 1;
};
} // namespace test_multimap_helper

// bool contains(const key_type& x) const;
TEST(multimap, contains) {
  static_cast<void>(test_info_);

  {
    test_multimap_helper::test_map_contains<::portable_stl::multimap<char, std::int32_t>,
                                            ::portable_stl::tuple<char, std::int32_t>>(
      'e',
      ::portable_stl::make_tuple('a', 10),
      ::portable_stl::make_tuple('b', 11),
      ::portable_stl::make_tuple('c', 12),
      ::portable_stl::make_tuple('d', 13));

    test_multimap_helper::test_map_contains<::portable_stl::multimap<char, char>, ::portable_stl::tuple<char, char>>(
      'e',
      ::portable_stl::make_tuple('a', 'a'),
      ::portable_stl::make_tuple('b', 'a'),
      ::portable_stl::make_tuple('c', 'a'),
      ::portable_stl::make_tuple('d', 'b'));

    test_multimap_helper::test_map_contains<::portable_stl::multimap<std::int32_t, test_multimap_helper::complex_value>,
                                            ::portable_stl::tuple<std::int32_t, test_multimap_helper::complex_value>>(
      -1,
      ::portable_stl::make_tuple(1, test_multimap_helper::complex_value{}),
      ::portable_stl::make_tuple(2, test_multimap_helper::complex_value{}),
      ::portable_stl::make_tuple(3, test_multimap_helper::complex_value{}),
      ::portable_stl::make_tuple(4, test_multimap_helper::complex_value{}));
  }
}

// bool contains(const t_key_like_type& key_like) const;
TEST(multimap, contains_transparent) {
  static_cast<void>(test_info_);

  ::portable_stl::
    multimap<std::pair<std::int32_t, std::int32_t>, std::int32_t, test_multimap_helper::compare_pair_trans>
      mp({
        {{2, 1}, 1},
        {{1, 2}, 2}, // hit
        {{1, 3}, 3}, // hit
        {{1, 4}, 4}, // hit
        {{2, 2}, 5}
  });

  ASSERT_TRUE(mp.contains(1));
}

//       iterator lower_bound(const key_type& k);
// const_iterator lower_bound(const key_type& k) const;
TEST(multimap, lower_bound) {
  static_cast<void>(test_info_);

  t_map_value_type arr[] = {t_map_value_type(5, 1),
                            t_map_value_type(5, 2),
                            t_map_value_type(5, 3),
                            t_map_value_type(7, 1),
                            t_map_value_type(7, 2),
                            t_map_value_type(7, 3),
                            t_map_value_type(9, 1),
                            t_map_value_type(9, 2),
                            t_map_value_type(9, 3)};

  {
    t_map mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

    auto iter = mp.lower_bound(4);
    ASSERT_EQ(iter, mp.begin());

    iter = mp.lower_bound(5);
    ASSERT_EQ(iter, mp.begin());

    iter = mp.lower_bound(6);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 3));

    iter = mp.lower_bound(7);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 3));

    iter = mp.lower_bound(8);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 6));

    iter = mp.lower_bound(9);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 6));

    iter = mp.lower_bound(10);
    ASSERT_EQ(iter, mp.end());
  }

  // constant
  {
    t_map const mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

    auto iter = mp.lower_bound(4);
    ASSERT_EQ(iter, mp.begin());

    iter = mp.lower_bound(5);
    ASSERT_EQ(iter, mp.begin());

    iter = mp.lower_bound(6);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 3));

    iter = mp.lower_bound(7);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 3));

    iter = mp.lower_bound(8);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 6));

    iter = mp.lower_bound(9);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 6));

    iter = mp.lower_bound(10);
    ASSERT_EQ(iter, mp.end());
  }
}

//       iterator lower_bound(const t_key_like_type& key_like);
// const_iterator lower_bound(const t_key_like_type& key_like) const;
TEST(multimap, lower_bound_transparent) {
  static_cast<void>(test_info_);

  {
    ::portable_stl::
      multimap<std::pair<std::int32_t, std::int32_t>, std::int32_t, test_multimap_helper::compare_pair_trans>
        mp({
          {{2, 1}, 1},
          {{1, 2}, 2}, // hit
          {{1, 3}, 3}, // hit
          {{1, 4}, 4}, // hit
          {{2, 2}, 5}
    });

    ASSERT_EQ(::portable_stl::next(mp.begin(), 0), mp.lower_bound(1)) << ::portable_stl::get<1>(*mp.lower_bound(1));
    ASSERT_EQ(mp.end(), mp.lower_bound(6));
  }

  // constant
  {
    ::portable_stl::
      multimap<std::pair<std::int32_t, std::int32_t>, std::int32_t, test_multimap_helper::compare_pair_trans> const mp({
        {{2, 1}, 1},
        {{1, 2}, 2}, // hit
        {{1, 3}, 3}, // hit
        {{1, 4}, 4}, // hit
        {{2, 2}, 5}
    });

    ASSERT_EQ(::portable_stl::next(mp.begin(), 0), mp.lower_bound(1)) << ::portable_stl::get<1>(*mp.lower_bound(1));
    ASSERT_EQ(mp.end(), mp.lower_bound(6));
  }
}

//       iterator upper_bound(const key_type& k);
// const_iterator upper_bound(const key_type& k) const;
TEST(multimap, upper_bound) {
  static_cast<void>(test_info_);

  t_map_value_type arr[] = {t_map_value_type(5, 1),
                            t_map_value_type(5, 2),
                            t_map_value_type(5, 3),
                            t_map_value_type(7, 1),
                            t_map_value_type(7, 2),
                            t_map_value_type(7, 3),
                            t_map_value_type(9, 1),
                            t_map_value_type(9, 2),
                            t_map_value_type(9, 3)};
  {
    t_map mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

    auto iter = mp.upper_bound(4);
    ASSERT_EQ(iter, mp.begin());

    iter = mp.upper_bound(5);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 3));

    iter = mp.upper_bound(6);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 3));

    iter = mp.upper_bound(7);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 6));

    iter = mp.upper_bound(8);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 6));

    iter = mp.upper_bound(9);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 9));

    iter = mp.upper_bound(10);
    ASSERT_EQ(iter, mp.end());
  }

  // constant
  {
    t_map const mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

    auto iter = mp.upper_bound(4);
    ASSERT_EQ(iter, mp.begin());

    iter = mp.upper_bound(5);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 3));

    iter = mp.upper_bound(6);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 3));

    iter = mp.upper_bound(7);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 6));

    iter = mp.upper_bound(8);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 6));

    iter = mp.upper_bound(9);
    ASSERT_EQ(iter, ::portable_stl::next(mp.begin(), 9));

    iter = mp.upper_bound(10);
    ASSERT_EQ(iter, mp.end());
  }
}

//       iterator upper_bound(const t_key_like_type& key_like);
// const_iterator upper_bound(const t_key_like_type& key_like) const;
TEST(multimap, upper_bound_transparent) {
  static_cast<void>(test_info_);

  {
    ::portable_stl::
      multimap<std::pair<std::int32_t, std::int32_t>, std::int32_t, test_multimap_helper::compare_pair_trans>
        mp({
          {{2, 1}, 1},
          {{1, 2}, 2}, // hit
          {{1, 3}, 3}, // hit
          {{1, 4}, 4}, // hit
          {{2, 2}, 5}
    });

    ASSERT_EQ(::portable_stl::next(mp.begin(), 3), mp.upper_bound(1)) << ::portable_stl::get<1>(*mp.upper_bound(1));
    ASSERT_EQ(mp.end(), mp.upper_bound(6));
  }

  // constant
  {
    ::portable_stl::
      multimap<std::pair<std::int32_t, std::int32_t>, std::int32_t, test_multimap_helper::compare_pair_trans> const mp({
        {{2, 1}, 1},
        {{1, 2}, 2}, // hit
        {{1, 3}, 3}, // hit
        {{1, 4}, 4}, // hit
        {{2, 2}, 5}
    });

    ASSERT_EQ(::portable_stl::next(mp.begin(), 3), mp.upper_bound(1)) << ::portable_stl::get<1>(*mp.upper_bound(1));
    ASSERT_EQ(mp.end(), mp.upper_bound(6));
  }
}

// pair<iterator,iterator>             equal_range(const key_type& k);
// pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
TEST(multimap, equal_range) {
  static_cast<void>(test_info_);

  t_map_value_type arr[] = {t_map_value_type(5, 1),
                            t_map_value_type(5, 2),
                            t_map_value_type(5, 3),
                            t_map_value_type(7, 1),
                            t_map_value_type(7, 2),
                            t_map_value_type(7, 3),
                            t_map_value_type(9, 1),
                            t_map_value_type(9, 2),
                            t_map_value_type(9, 3)};
  {
    t_map mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

    auto result = mp.equal_range(4);
    ASSERT_EQ(::portable_stl::get<0>(result), mp.begin());
    ASSERT_EQ(::portable_stl::get<1>(result), mp.begin());

    result = mp.equal_range(5);
    ASSERT_EQ(::portable_stl::get<0>(result), mp.begin());
    ASSERT_EQ(::portable_stl::get<1>(result), ::portable_stl::next(mp.begin(), 3));

    result = mp.equal_range(6);
    ASSERT_EQ(::portable_stl::get<0>(result), ::portable_stl::next(mp.begin(), 3));
    ASSERT_EQ(::portable_stl::get<1>(result), ::portable_stl::next(mp.begin(), 3));

    result = mp.equal_range(7);
    ASSERT_EQ(::portable_stl::get<0>(result), ::portable_stl::next(mp.begin(), 3));
    ASSERT_EQ(::portable_stl::get<1>(result), ::portable_stl::next(mp.begin(), 6));

    result = mp.equal_range(8);
    ASSERT_EQ(::portable_stl::get<0>(result), ::portable_stl::next(mp.begin(), 6));
    ASSERT_EQ(::portable_stl::get<1>(result), ::portable_stl::next(mp.begin(), 6));

    result = mp.equal_range(9);
    ASSERT_EQ(::portable_stl::get<0>(result), ::portable_stl::next(mp.begin(), 6));
    ASSERT_EQ(::portable_stl::get<1>(result), ::portable_stl::next(mp.begin(), 9));

    result = mp.equal_range(10);
    ASSERT_EQ(::portable_stl::get<0>(result), mp.end());
    ASSERT_EQ(::portable_stl::get<1>(result), mp.end());
  }

  // constant
  {
    t_map const mp(arr, arr + sizeof(arr) / sizeof(arr[0]));

    auto result = mp.equal_range(4);
    ASSERT_EQ(::portable_stl::get<0>(result), mp.begin());
    ASSERT_EQ(::portable_stl::get<1>(result), mp.begin());

    result = mp.equal_range(5);
    ASSERT_EQ(::portable_stl::get<0>(result), mp.begin());
    ASSERT_EQ(::portable_stl::get<1>(result), ::portable_stl::next(mp.begin(), 3));

    result = mp.equal_range(6);
    ASSERT_EQ(::portable_stl::get<0>(result), ::portable_stl::next(mp.begin(), 3));
    ASSERT_EQ(::portable_stl::get<1>(result), ::portable_stl::next(mp.begin(), 3));

    result = mp.equal_range(7);
    ASSERT_EQ(::portable_stl::get<0>(result), ::portable_stl::next(mp.begin(), 3));
    ASSERT_EQ(::portable_stl::get<1>(result), ::portable_stl::next(mp.begin(), 6));

    result = mp.equal_range(8);
    ASSERT_EQ(::portable_stl::get<0>(result), ::portable_stl::next(mp.begin(), 6));
    ASSERT_EQ(::portable_stl::get<1>(result), ::portable_stl::next(mp.begin(), 6));

    result = mp.equal_range(9);
    ASSERT_EQ(::portable_stl::get<0>(result), ::portable_stl::next(mp.begin(), 6));
    ASSERT_EQ(::portable_stl::get<1>(result), ::portable_stl::next(mp.begin(), 9));

    result = mp.equal_range(10);
    ASSERT_EQ(::portable_stl::get<0>(result), mp.end());
    ASSERT_EQ(::portable_stl::get<1>(result), mp.end());
  }
}

// template<typename K> pair<iterator,iterator>             equal_range(const K& x);
// template<typename K> pair<const_iterator,const_iterator> equal_range(const K& x) const;
TEST(multimap, equal_range_transparent) {
  static_cast<void>(test_info_);

  {
    ::portable_stl::multimap<std::pair<std::int32_t, std::int32_t>, std::int32_t,
    test_multimap_helper::compare_pair_trans> mp({
      {{2, 1}, 1},
      {{1, 2}, 2}, // hit
      {{1, 3}, 3}, // hit
      {{1, 4}, 4}, // hit
      {{2, 2}, 5}
    });

    auto        result = mp.equal_range(1);
    std::size_t nels{0};

    for (auto it = ::portable_stl::get<0>(result); it != ::portable_stl::get<1>(result); it++) {
      ASSERT_EQ(1, ::portable_stl::get<0>(*it).first);
      ++nels;
    }

    ASSERT_EQ(3, nels);
  }

  {
    ::portable_stl::multimap<std::pair<std::int32_t, std::int32_t>, std::int32_t,
    test_multimap_helper::compare_pair_trans> const mp({
      {{2, 1}, 1},
      {{1, 2}, 2}, // hit
      {{1, 3}, 3}, // hit
      {{1, 4}, 4}, // hit
      {{2, 2}, 5}
    });

    auto        result = mp.equal_range(1);
    std::size_t nels{0};

    for (auto it = ::portable_stl::get<0>(result); it != ::portable_stl::get<1>(result); it++) {
      ASSERT_EQ(1, ::portable_stl::get<0>(*it).first);
      ++nels;
    }

    ASSERT_EQ(3, nels);
  }
}
