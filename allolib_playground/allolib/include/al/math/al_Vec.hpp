#ifndef INCLUDE_AL_VEC_HPP
#define INCLUDE_AL_VEC_HPP

/*  Allocore --
  Multimedia / virtual environment application class library

  Copyright (C) 2009. AlloSphere Research Group, Media Arts & Technology, UCSB.
  Copyright (C) 2012. The Regents of the University of California.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    Neither the name of the University of California nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.


  File description:
  Generic fixed-size n-vector

  File author(s):
  Lance Putnam, 2010, putnam.lance@gmail.com
  Graham Wakefield, 2010, grrrwaaa@gmail.com

  Synchronized to AlloSystem commit:
  0ddb8ec6594ca66d34dc18849bc2b433e5f67016
*/

#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <ostream>
#include <type_traits>

#include "al/math/al_Constants.hpp"

namespace al {

template <int N, class T> class Vec;

typedef Vec<2, float> Vec2f;  ///< float 2-vector
typedef Vec<2, double> Vec2d; ///< double 2-vector
typedef Vec<2, int> Vec2i;    ///< integer 2-vector
typedef Vec<3, float> Vec3f;  ///< float 3-vector
typedef Vec<3, double> Vec3d; ///< double 3-vector
typedef Vec<3, int> Vec3i;    ///< integer 3-vector
typedef Vec<4, float> Vec4f;  ///< float 4-vector
typedef Vec<4, double> Vec4d; ///< double 4-vector
typedef Vec<4, int> Vec4i;    ///< integer 4-vector
typedef Vec<5, float> Vec5f;  ///< float 5-vector
typedef Vec<5, double> Vec5d; ///< double 5-vector
typedef Vec<5, int> Vec5i;    ///< integer 5-vector

// Forward iterates from 0 to n-1. Current index is 'i'.
#define IT(n) for (int i = 0; i < (n); ++i)

template <int N, class T> struct VecElems {
  T x, y, z, w;

private:
  T data[N - 4];
};

template <class T> struct VecElems<0, T> {
  static T x;
};
template <class T> T VecElems<0, T>::x = 0;

template <class T> struct VecElems<1, T> {
  T x;
};
template <class T> struct VecElems<2, T> {
  T x, y;
};
template <class T> struct VecElems<3, T> {
  T x, y, z;

  /// Returns cross product of this x b
  Vec<3, T> cross(const Vec<3, T> &b) const {
    return Vec<3, T>(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
  }
};
template <class T> struct VecElems<4, T> {
  T x, y, z, w;

  Vec<4, T> cross(const Vec<4, T> &b) const {
    return Vec<3, T>(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
  }
};

/// Flag type to prevent element initialization
static struct VecNoInit {
} VEC_NO_INIT;

// Base case
template <class V> Vec<1, V> toVec(const V &v);

/// Returns new Vec filled with values
template <class V, class... Vs>
Vec<1 + sizeof...(Vs), V> toVec(const V &v, Vs... vs);

/// Fixed-size n-vector

/// This is a fixed size array to enable better loop unrolling optimizations
/// by the compiler and to avoid an extra 'size' data member for small-sized
/// arrays.
///
/// @ingroup Math
template <int N, class T> class Vec : public VecElems<N, T> {

  static constexpr int const_abs(int x) { return x >= 0 ? x : -x; }
  static constexpr int const_min(int x, int y) { return x <= y ? x : y; }

public:
  using VecElems<N, T>::x;

  typedef T value_type;

  /// @param[in] v    value to initialize all elements to
  Vec(const T &v = T()) { *this = v; }

  /// @param[in] v1    value to initialize first element
  /// @param[in] v2    value to initialize second element
  Vec(const T &v1, const T &v2) { set(v1, v2); }

  /// @param[in] v1    value to initialize first element
  /// @param[in] v2    value to initialize second element
  /// @param[in] v3    value to initialize third element
  Vec(const T &v1, const T &v2, const T &v3) { set(v1, v2, v3); }

  /// @param[in] v1    value to initialize first element
  /// @param[in] v2    value to initialize second element
  /// @param[in] v3    value to initialize third element
  /// @param[in] v4    value to initialize fourth element
  Vec(const T &v1, const T &v2, const T &v3, const T &v4) {
    set(v1, v2, v3, v4);
  }

  /// @param[in] v1    value to initialize first element
  /// @param[in] v2    value to initialize second element
  /// @param[in] v3    value to initialize third element
  /// @param[in] v4    value to initialize fourth element
  /// @param[in] v5    value to initialize fifth element
  Vec(const T &v1, const T &v2, const T &v3, const T &v4, const T &v5) {
    set(v1, v2, v3, v4, v5);
  }

  /// @param[in] v		values to initialize elements to
  /// If the initializer list has one element, then it is assigned to all
  /// vector components.
  Vec(std::initializer_list<T> v) { set(v); }

  /// @param[in] v    vector to initialize all elements to
  template <int N2, class T2> Vec(const Vec<N2, T2> &v) {
    *this = v;
    initTail<N2>();
  }

  /// @param[in] v    vector to initialize first N-1 elements to
  /// @param[in] s    value of last element
  template <class Tv, class Ts> Vec(const Vec<N - 1, Tv> &v, const Ts &s) {
    set(v, s);
  }

  /// @param[in] s		value of first element
  /// @param[in] v		vector to initialize last N-1 elements to
  template <class Ts, class Tv> Vec(const Ts &s, const Vec<N - 1, Tv> &v) {
    set(s, v);
  }

  /// @param[in] v    pointer to array to initialize all elements to
  /// @param[in] stride  stride factor through array
  template <class T2> Vec(const T2 *v, int stride = 1) { set(v, stride); }
  /// Non-initializing constructor
  Vec(VecNoInit) {}

  //--------------------------------------------------------------------------
  // Factory Methods

  /// Get axis aligned vector
  static Vec aa(int axis, T val = T(1)) { return Vec().setAA(axis, val); }
  template <int Axis> static Vec aa(T val = T(1)) {
    return Vec().setAA<Axis>(val);
  }

  /// Get vector filled with linear sequence of values

  /// @param[in] begin	start value
  /// @param[in] inc		difference between successive elements (slope)
  static Vec iota(T begin = T(0), T inc = T(1)) {
    Vec r;
    auto val = begin;
    for (auto &v : r) {
      v = val;
      val += inc;
    }
    return r;
  }

  /// Get vector filled with linear ramp

  /// @param[in] begin	start value
  /// @param[in] end		end value
  /// @tparam endInc		whether end value is inclusive
  template <bool endInc = true> static Vec line(T begin = T(0), T end = T(1)) {
    constexpr auto M = N - int(endInc);
    static_assert(M > 0, "Invalid number of steps");
    constexpr auto m = 1. / M;
    return iota(begin, (end - begin) * m);
  }

  //--------------------------------------------------------------------------
  // Memory Operations

  /// Returns number of elements
  static constexpr int size() { return N; }

  /// Returns C array type punned into a vector
  static Vec &pun(T *src) { return *(Vec *)(src); }
  static const Vec &pun(const T *src) { return *(const Vec *)(src); }

  /// Get reference to self as another type
  template <class V> V &as() {
    static_assert(sizeof(V) <= sizeof(*this),
                  "Attempt to pun vector to object of larger size");
    return *(V *)(elems());
  }

  template <class V> const V &as() const {
    static_assert(sizeof(V) <= sizeof(*this),
                  "Attempt to pun vector to object of larger size");
    return *(const V *)(elems());
  }

  /// Get read-only pointer to elements
  const T *elems() const { return &x; }

  /// Get read-write pointer to elements
  T *elems() { return &x; }

  T *begin() { return elems(); }
  const T *begin() const { return elems(); }
  T *end() { return elems() + N; }
  const T *end() const { return elems() + N; }

  /// Set element at index with no bounds checking
  T &operator[](size_t i) { return elems()[i]; }

  /// Get element at index with no bounds checking
  const T &operator[](size_t i) const { return elems()[i]; }

  /// Set element at index with compile-time bounds checking
  template <int i> T &at() {
    static_assert(0 <= i && i < N, "Index out of bounds");
    return (*this)[i];
  }

  /// Get element at index with compile-time bounds checking
  template <int i> const T &at() const {
    static_assert(0 <= i && i < N, "Index out of bounds");
    return (*this)[i];
  }

  Vec &operator=(const T &v) {
    IT(N)(*this)[i] = v;
    return *this;
  }

  template <int N2, class T2> Vec &operator=(const Vec<N2, T2> &v) {
    IT(N < N2 ? N : N2)(*this)[i] = T(v[i]);
    return *this;
  }

  /// Set element at index (a chainable version of at())
  template <int i> Vec &set(const T &v) {
    at<i>() = v;
    return *this;
  }

  /// Set elements from another vector and scalar
  template <class Tv, class Ts> Vec &set(const Vec<N - 1, Tv> &v, const Ts &s) {
    (*this)[N - 1] = s;
    return (*this = v);
  }

  template <class Ts, class Tv> Vec &set(const Ts &s, const Vec<N - 1, Tv> &v) {
    (*this)[0] = s;
    sub<N - 1, 1>() = v;
    return *this;
  }

  /// Set elements from (strided) raw C-pointer
  template <class T2> Vec &set(const T2 *const v, int stride = 1) {
    IT(N)(*this)[i] = T(v[i * stride]);
    return *this;
  }

  /// Set first 2 elements
  Vec &set(const T &v1, const T &v2) {
    static_assert(N == 2,
                  "Attempt to set vector with wrong number of elements");
    at<0>() = v1;
    at<1>() = v2;
    return *this;
  }

  /// Set first 3 elements
  Vec &set(const T &v1, const T &v2, const T &v3) {
    static_assert(N == 3,
                  "Attempt to set vector with wrong number of elements");
    at<0>() = v1;
    at<1>() = v2;
    at<2>() = v3;
    return *this;
  }

  /// Set first 4 elements
  Vec &set(const T &v1, const T &v2, const T &v3, const T &v4) {
    static_assert(N == 4,
                  "Attempt to set vector with wrong number of elements");
    at<0>() = v1;
    at<1>() = v2;
    at<2>() = v3;
    at<3>() = v4;
    return *this;
  }

  /// Set first 5 elements
  Vec &set(const T &v1, const T &v2, const T &v3, const T &v4, const T &v5) {
    static_assert(N == 5,
                  "Attempt to set vector with wrong number of elements");
    at<0>() = v1;
    at<1>() = v2;
    at<2>() = v3;
    at<3>() = v4;
    at<4>() = v5;
    return *this;
  }

  /// Set first 6 elements
  Vec &set(const T &v1, const T &v2, const T &v3, const T &v4, const T &v5,
           const T &v6) {
    static_assert(N == 6,
                  "Attempt to set vector with wrong number of elements");
    at<0>() = v1;
    at<1>() = v2;
    at<2>() = v3;
    at<3>() = v4;
    at<4>() = v5;
    at<5>() = v6;
    return *this;
  }

  /// Set elements from initializer list {a,b,...}

  /// If the initializer list has one element, then it is assigned to all
  /// vector components.
  Vec &set(std::initializer_list<T> v) {
    if (v.size() == 1) {
      (*this) = v.begin()[0];
    } else {
      const int M = N < v.size() ? N : int(v.size());
      for (int i = 0; i < M; ++i)
        (*this)[i] = v.begin()[i];
      for (int i = M; i < N; ++i)
        (*this)[i] = T();
    }
    return *this;
  }

  /// Fill subrange of elements with value
  Vec &fill(const T &v, int count, int begin = 0) {
    for (int i = begin; i < begin + count; ++i)
      (*this)[i] = v;
    return *this;
  }

  /// Fill last 'count' elements with value
  Vec &fillLast(const T &v, int count) { return fill(v, count, N - count); }

  /// Set to axis-aligned vector
  Vec &setAA(int axis, T val = T(1)) {
    (*this) = T(0);
    (*this)[axis] = val;
    return *this;
  }
  template <int Axis> Vec &setAA(T val = T(1)) {
    static_assert(0 <= Axis && Axis < N, "Axis out of range");
    return setAA(Axis, val);
  }

  /// Return true if objects are element-wise equal, false otherwise
  bool operator==(const Vec &v) const {
    IT(N) {
      if ((*this)[i] != v[i])
        return false;
    }
    return true;
  }

  /// Return true if all elements are equal to value, false otherwise
  bool operator==(const T &v) const {
    IT(N) {
      if ((*this)[i] != v)
        return false;
    }
    return true;
  }

  /// Return true if objects are not element-wise equal, false otherwise
  bool operator!=(const Vec &v) const { return !(*this == v); }

  /// Return true if all elements are not equal to value, false otherwise
  bool operator!=(const T &v) const { return !(*this == v); }

  /// Get a vector comprised of indexed elements
  Vec<2, T> get(int i0, int i1) const {
    return Vec<2, T>((*this)[i0], (*this)[i1]);
  }

  /// Get a vector comprised of indexed elements
  Vec<3, T> get(int i0, int i1, int i2) const {
    return Vec<3, T>((*this)[i0], (*this)[i1], (*this)[i2]);
  }

  /// Get a vector comprised of indexed elements
  Vec<4, T> get(int i0, int i1, int i2, int i3) const {
    return Vec<4, T>((*this)[i0], (*this)[i1], (*this)[i2], (*this)[i3]);
  }

  /// Get a vector comprised of indexed elements
  Vec<5, T> get(int i0, int i1, int i2, int i3, int i4) const {
    return Vec<5, T>((*this)[i0], (*this)[i1], (*this)[i2], (*this)[i3],
                     (*this)[i4]);
  }

  /// Get a vector comprised of indexed elements (compile-time checked)
  template <int... Indices> Vec<sizeof...(Indices), T> get() {
    return toVec(at<Indices>()...);
  }

  /// Get a subvector
  template <int M, int Begin = 0> const Vec<M, T> &sub() const {
    return const_cast<Vec *>(this)->sub<M, Begin>();
  }

  template <int M, int Begin = 0> Vec<M, T> &sub() {
    static_assert((Begin + M) <= N, "Invalid subvector range");
    return Vec<M, T>::pun(elems() + Begin);
  }

  template <int M> Vec<M, T> &sub(int begin = 0) {
    return *(Vec<M, T> *)(elems() + begin);
  }
  //  template <int M, int N, class T>
  //  inline Vec<M, T> sub(const Vec<N, T> &v, int begin = 0) {
  //    return v.template sub<M>(begin);
  //  }

  const Vec<2, T> &xy() const { return sub<2>(); }
  Vec<2, T> &xy() { return sub<2>(); }
  const Vec<2, T> &yz() const { return sub<2, 1>(); }
  Vec<2, T> &yz() { return sub<2, 1>(); }
  const Vec<2, T> &zw() const { return sub<2, 2>(); }
  Vec<2, T> &zw() { return sub<2, 2>(); }
  const Vec<3, T> &xyz() const { return sub<3>(); }
  Vec<3, T> &xyz() { return sub<3>(); }
  const Vec<3, T> &yzw() const { return sub<3, 1>(); }
  Vec<3, T> &yzw() { return sub<3, 1>(); }

  /// Remove leading or trailing elements

  /// \tparam M	Number of elements to drop from head (if positive) or
  /// tail
  ///				(if negative).
  template <int M, int L = N - const_min(const_abs(M), N)>
  Vec<L, T> drop() const {
    return sub < L, M < 0 ? 0 : N - L > ();
  }

  /// Swap elements
  Vec &swap(int i, int j) {
    std::swap((*this)[i], (*this)[j]);
    return *this;
  }

  //--------------------------------------------------------------------------
  // Basic Arithmetic Operations

  //  Vec &operator=(const Vec &v) { return set(v); }
  //  Vec &operator=(const T &v) { return set(v); }
  Vec &operator+=(const Vec &v) {
    IT(N)(*this)[i] += v[i];
    return *this;
  }
  Vec &operator+=(const T &v) {
    IT(N)(*this)[i] += v;
    return *this;
  }
  Vec &operator-=(const Vec &v) {
    IT(N)(*this)[i] -= v[i];
    return *this;
  }
  Vec &operator-=(const T &v) {
    IT(N)(*this)[i] -= v;
    return *this;
  }
  Vec &operator*=(const Vec &v) {
    IT(N)(*this)[i] *= v[i];
    return *this;
  }
  Vec &operator*=(const T &v) {
    IT(N)(*this)[i] *= v;
    return *this;
  }
  Vec &operator/=(const Vec &v) {
    IT(N)(*this)[i] /= v[i];
    return *this;
  }
  Vec &operator/=(const T &v) {
    IT(N)(*this)[i] /= v;
    return *this;
  }

  Vec operator+(const Vec &v) const { return Vec(*this) += v; }
  Vec operator+(const T &v) const { return Vec(*this) += v; }
  Vec operator-(const Vec &v) const { return Vec(*this) -= v; }
  Vec operator-(const T &v) const { return Vec(*this) -= v; }
  Vec operator*(const Vec &v) const { return Vec(*this) *= v; }
  Vec operator*(const T &v) const { return Vec(*this) *= v; }
  Vec operator/(const Vec &v) const { return Vec(*this) /= v; }
  Vec operator/(const T &v) const { return Vec(*this) /= v; }
  Vec operator-() const { return Vec(*this).negate(); }
  bool operator>(const Vec &v) const { return magSqr() > v.magSqr(); }
  bool operator<(const Vec &v) const { return magSqr() < v.magSqr(); }

  /// Set elements from another vector
  template <class T2> Vec &set(const Vec<N, T2> &v) {
    IT(N) { (*this)[i] = T(v[i]); }
    return *this;
  }

  /// Set elements from another vector
  template <int N2, class T2> Vec &set(const Vec<N2, T2> &v) {
    IT(N < N2 ? N : N2) { (*this)[i] = T(v[i]); }
    return *this;
  }

  //  /// Set elements from another vector and scalar
  //  template <class Tv, class Ts> Vec &set(const Vec<N - 1, Tv> &v, const Ts
  //  &s) {
  //    (*this)[N - 1] = s;
  //    return set(v);
  //  }

  /// Set all elements to the same value
  Vec &set(const T &v) {
    IT(N) { (*this)[i] = v; }
    return *this;
  }

  //  /// Set elements from raw C-pointer
  //  template <class T2> Vec &set(const T2 *v) {
  //    IT(N) { (*this)[i] = T(v[i]); }
  //    return *this;
  //  }

  /// Apply a function in-place on each element
  template <class Func, class... Args> Vec &apply(Func func, Args... args) {
    for (auto &v : *this)
      func(v, args...);
    return *this;
  }

  template <class V, class Func, class... Args>
  Vec<N, V> map(Func func, Args... args) const {
    Vec<N, V> r(VEC_NO_INIT);
    for (int i = 0; i < size(); ++i)
      r[i] = func((*this)[i], args...);
    return r;
  }

  /// Map elements through function into new vector

  /// @param[in] func		Function taking old value and returning new
  /// value
  /// @param[in] args		Extra function arguments
  template <class Func, class... Args> Vec map(Func func, Args... args) const {
    return map<T>(func, args...);
  }

  /// Reduce elements into scalar

  /// @param[in] prev		Initial previous value
  /// @param[in] func		Function taking previous and current values as
  /// first
  ///						two arguments and returning new
  /// value
  /// @param[in] args		Extra function arguments
  template <class Func, class... Args>
  T reduce(const T &prev, Func func, Args... args) const {
    T r = prev;
    for (auto &v : *this)
      r = func(r, v, args...);
    return r;
  }

  //--------------------------------------------------------------------------
  // Linear Operations

  /// Returns a nearby vector along some dimension

  /// @tparam   Dimension  The dimension along which to get a nearby vector
  /// @param[in]  shift    The amount to shift along specified dimension
  template <int Dimension> Vec by(T shift) const {
    static_assert(Dimension < N, "Dimension out of bounds");
    Vec res(*this);
    res[Dimension] += shift;
    return res;
  }

  /// Returns a nearby vector along x
  Vec byx(T shift) const { return by<0>(shift); }

  /// Returns a nearby vector along y
  Vec byy(T shift) const { return by<1>(shift); }

  /// Returns a nearby vector along z
  Vec byz(T shift) const { return by<2>(shift); }

  /// Returns dot (inner) product between vectors
  template <class U> T dot(const Vec<N, U> &v) const {
    T r = (*this)[0] * v[0];
    for (int i = 1; i < N; ++i) {
      r += (*this)[i] * v[i];
    }
    return r;
  }

  /// Returns magnitude
  T mag() const { return std::sqrt(magSqr()); }

  /// Returns magnitude squared
  T magSqr() const { return dot(*this); }

  /// Returns vector filled with absolute values of elements
  Vec absVec() const {
    using namespace std;
    Vec res(*this);
    for (auto &v : res)
      v = std::abs(v);
    return res;
  }

  /// Returns component-wise signum function
  Vec sgn(T mag = T(1)) const {
    Vec s;
    for (int i = 0; i < N; ++i) {
      const auto &v = (*this)[i];
      s[i] = v < T(0) ? -mag : v > T(0) ? mag : T(0);
    }
    return s;
  }

  /// Returns p-norm of elements

  /// The p-norm is pth root of the sum of the absolute value of the
  /// elements raised to the pth power, (sum |x_n|^p) ^ (1/p). See norm1 and
  /// norm2 for more efficient specializations.
  T norm(const T &p) const {
    T r = std::pow(std::abs((*this)[0]), p);
    for (int i = 1; i < N; ++i) {
      r += std::pow(std::abs((*this)[i]), p);
    }
    return std::pow(pow(absVec(), p).sum(), T(1) / p);
  }

  /// Return 1-norm of elements (sum of absolute values)
  T norm1() const { return sumAbs(); }

  /// Return 2-norm of elements
  T norm2() const { return mag(); }

  /// Returns product of elements
  T product() const {
    T r = (*this)[0];
    for (int i = 1; i < N; ++i) {
      r *= (*this)[i];
    }
    return r;
  }

  /// Returns sum of elements
  T sum() const {
    T r = (*this)[0];
    for (int i = 1; i < N; ++i) {
      r += (*this)[i];
    }
    return r;
  }

  /// Returns sum of absolute value of elements (1-norm)
  T sumAbs() const { return absVec().sum(); }

  /// Returns mean (average) of elements
  T mean() const {
    static const T invSize = 1. / size();
    return sum() * invSize;
  }

  /// Linearly interpolate towards some target
  Vec &lerp(const Vec &target, T amt) {
    return (*this) += (target - (*this)) * amt;
  }

  /// Set magnitude (preserving direction)
  Vec &mag(T v);

  /// Set 1-norm of vector (sum of absolute values)

  /// This is useful for when you need to ensure the sum of absolute values
  /// is equal to some value without changing the direction of the vector.
  Vec &norm1(T v) {
    auto n1 = sumAbs();
    if (n1 > T(0))
      (*this) *= (v / n1);
    return *this;
  }

  /// Negates all elements
  Vec &negate() {
    for (auto &v : *this) {
      v = -v;
    }
    return *this;
  }

  /// Normalize magnitude (preserving direction)

  /// @param[in] magVal	magnitude (1 is a standard normalization)
  ///
  Vec &normalize(T magVal = T(1)) { return mag(magVal); }

  /// Return closest vector lying on a sphere

  /// @param[in] magVal	magnitude (1 is a standard normalization)
  ///
  Vec normalized(T magVal = T(1)) const { return Vec(*this).normalize(magVal); }

  /// Get projection of vector onto a unit vector
  Vec projection(const Vec &u) const { return dot(u) * u; }

  /// Get rejection of vector from a unit vector

  /// This also gives the projection onto a plane defined by normal 'u'.
  ///
  Vec rejection(const Vec &u) const { return (*this) - projection(u); }

  /// Reflect vector around a unit vector
  Vec &reflect(const Vec &u) { return (*this) -= ((T(2) * dot(u)) * u); }

  /// Rotate vector on a global plane

  /// @param[in] angle  angle of right-handed rotation, in radians
  /// @param[in] dim1    dimension to rotate from
  /// @param[in] dim2    dimension to rotate towards
  Vec &rotate(double angle, int dim1 = 0, int dim2 = 1) {
    double a = cos(angle);
    double b = sin(angle);
    T t = (*this)[dim1];
    T u = (*this)[dim2];
    (*this)[dim1] = t * a - u * b;
    (*this)[dim2] = t * b + u * a;
    return *this;
  }

  /// Rotate vector 90 degrees on a global plane

  /// @param[in] dim1		dimension to rotate from
  /// @param[in] dim2		dimension to rotate towards
  /// To rotate -90 degrees, swap the two dimensions.
  Vec &rotate90(int dim1, int dim2) {
    (*this)[dim2] = -(*this)[dim2];
    return swap(dim1, dim2);
  }

  template <unsigned Dim1 = 0, unsigned Dim2 = 1> Vec &rotate90() {
    static_assert(Dim1 < N && Dim2 < N && Dim1 != Dim2, "Invalid dimension(s)");
    return rotate90(Dim1, Dim2);
  }

  //--------------------------------------------------------------------------
  // Analysis

  /// Returns index of first occurrence of value or -1 if no match
  int find(const T &v) const {
    for (int i = 0; i < N; ++i) {
      if ((*this)[i] == v)
        return i;
    }
    return -1;
  }

  /// Get index of minimum value
  int indexOfMin() const {
    int j = 0;
    for (int i = 1; i < N; ++i) {
      if ((*this)[i] < (*this)[j])
        j = i;
    }
    return j;
  }

  /// Get index of maximum value
  int indexOfMax() const {
    int j = 0;
    for (int i = 1; i < N; ++i) {
      if ((*this)[i] > (*this)[j])
        j = i;
    }
    return j;
  }

  /// Get minimum value
  const T &min() const { return (*this)[indexOfMin()]; }

  /// Get maximum value
  const T &max() const { return (*this)[indexOfMax()]; }

  /// debug printing
  void print(FILE *out = stdout, const char *append = "") const;
  void println(FILE *out = stdout) const;

private:
  // set last N-M elements to default value
  template <int M> void initTail() {
    for (int i = M; i < size(); ++i)
      (*this)[i] = T();
  }
};

// -----------------------------------------------------------------------------
// The following are functions that either cannot be defined as class
// methods (due to syntax rules or specialization) or simply are not object
// oriented.

// Non-member binary arithmetic operations
template <int N, class T>
inline Vec<N, T> operator+(const T &s, const Vec<N, T> &v) {
  return v + s;
}

template <int N, class T>
inline Vec<N, T> operator-(const T &s, const Vec<N, T> &v) {
  return -v + s;
}

template <int N, class T>
inline Vec<N, T> operator*(const T &s, const Vec<N, T> &v) {
  return v * s;
}

template <int N, class T>
inline Vec<N, T> operator/(const T &s, const Vec<N, T> &v) {
  auto r = v;
  for (auto &e : r)
    e = s / e;
  return r;
  return r;
}

// Specialized vector functions

/// Get absolute value (magnitude) of vector
template <int N, class T> inline T abs(const Vec<N, T> &v) { return v.mag(); }

/// Returns concatenation of two vectors
template <int N1, class T1, int N2, class T2>
inline Vec<N1 + N2, T1> concat(const Vec<N1, T1> &a, const Vec<N2, T2> &b) {
  Vec<N1 + N2, T1> r;
  r.set(a.elems());
  for (int i = 0; i < N2; ++i)
    r[i + N1] = T1(b[i]);
  return r;
}

template <int N, class T, class V>
inline Vec<N + 1, T> concat(const Vec<N, T> &v, const V &s) {
  return Vec<N + 1, T>(v, s);
}

template <int N, class T, class V>
inline Vec<N + 1, T> concat(const V &s, const Vec<N, T> &v) {
  return Vec<N + 1, T>(s, v);
}

template <class V> Vec<1, V> toVec(const V &v) { return {v}; }

/// Returns new Vec filled with values
template <class V, class... Vs>
Vec<1 + sizeof...(Vs), V> toVec(const V &v, Vs... vs) {
  return concat(v, toVec(vs...));
}

/// Get a subvector
template <int M, int Begin, int N, class T>
inline Vec<M, T> sub(const Vec<N, T> &v) {
  return v.template sub<M, Begin>();
}
template <int M, int Begin, int N, class T>
inline Vec<M, T> &sub(Vec<N, T> &v) {
  return v.template sub<M, Begin>();
}
// template <int M, int N, class T> inline Vec<M, T> sub(const Vec<N, T> &v) {
//  return sub<M, 0>(v);
//}

// template <int M, int N, class T> inline Vec<M, T> &sub(Vec<N, T> &v) {
//  return sub<M, 0>(v);
//}

/// Get vector with each element raised to a power
template <int N, class T>
inline Vec<N, T> pow(const Vec<N, T> &v, const T &power) {
  auto r = v;
  for (auto &e : r)
    e = std::pow(e, power);
  return r;
}

/// Get vector with each element raised to a power
template <int N, class T>
inline Vec<N, T> pow(const T &base, const Vec<N, T> &powers) {
  auto r = powers;
  for (auto &e : r)
    e = std::pow(base, e);
  return r;
}

/// Get real-valued vector rounded to nearest integer vector
template <int N, class T> inline Vec<N, int> roundi(const Vec<N, T> &v) {
  return v + v.sgn(T(0.5));
}

/// Sets r to cross product, a x b
template <class T>
inline void cross(Vec<3, T> &r, const Vec<3, T> &a, const Vec<3, T> &b) {
  //  r[0] = a[1]*b[2] - a[2]*b[1];
  //  r[1] = a[2]*b[0] - a[0]*b[2];
  //  r[2] = a[0]*b[1] - a[1]*b[0];
  r = a.cross(b);
}

/// Returns cross product, a x b
template <class T>
inline Vec<3, T> cross(const Vec<3, T> &a, const Vec<3, T> &b) {
  Vec<3, T> r;
  cross(r, a, b);
  return r;
}

template <class T>
inline void cross(Vec<3, T> &r, const Vec<4, T> &a, const Vec<4, T> &b) {
  //  r[0] = a[1]*b[2] - a[2]*b[1];
  //  r[1] = a[2]*b[0] - a[0]*b[2];
  //  r[2] = a[0]*b[1] - a[1]*b[0];
  r = a.cross(b);
}

/// Returns cross product, a x b
template <class T>
inline Vec<3, T> cross(const Vec<4, T> &a, const Vec<4, T> &b) {
  Vec<3, T> r;
  cross(r, a, b);
  return r;
}

/// Returns dot product
template <int N, class T> inline T dot(const Vec<N, T> &a, const Vec<N, T> &b) {
  return a.dot(b);
}

/// Rotate a vector around a normal vector

/// @param[in,out]  vec    The vector to rotate
/// @param[in]    normal  A normal perpendicular to the plane of rotation
/// @param[in]    cosAng  Cosine of the rotation angle
/// @param[in]    sinAng  Sine of the rotation angle
template <class T>
void rotate(Vec<3, T> &vec, const Vec<3, T> &normal, double cosAng,
            double sinAng) {
  T c = cosAng;
  T s = sinAng;

  // Rodrigues' rotation formula:
  vec = vec * c + cross(normal, vec) * s +
        normal * (normal.dot(vec) * (T(1) - c));
}

/// Rotate a vector around a normal vector

/// @param[in,out]  vec      The vector to rotate
/// @param[in]    normal    A normal perpendicular to the plane of rotation
/// @param[in]    angle    The rotation angle, in radians
template <class T>
void rotate(Vec<3, T> &vec, const Vec<3, T> &normal, double angle) {
  rotate(vec, normal, cos(angle), sin(angle));
}

/// Returns angle, in interval [0, pi], between two vectors
template <int N, class T>
inline T angle(const Vec<N, T> &a, const Vec<N, T> &b) {
  T cosAng = a.dot(b) / sqrt(a.magSqr() * b.magSqr());
  if (cosAng >= T(1)) {
    return T(0);
  } else if (cosAng <= T(-1)) {
    return T(M_PI);
  }
  return std::acos(cosAng);
}

/*! Compute centroid of a triangle defined by three points
  @param[ in] p1  Point 1
  @param[ in] p2  Point 2
  @param[ in] p3  Point 3
  @returns centroid of points
*/
template <int N, class T>
inline Vec<N, T> centroid(const Vec<N, T> &p1, const Vec<N, T> &p2,
                          const Vec<N, T> &p3) {
  return (p1 + p2 + p3) / T(3);
}

/// Get closest point on a line to a point p
template <int N, class T>
Vec<N, T> closestPointOnLine(const Vec<N, T> &linePnt, const Vec<N, T> &lineDir,
                             const Vec<N, T> &p) {
  return linePnt + (p - linePnt).projection(lineDir);
}

/// Get closest point on line segment ab to point p
template <int N, class T, class Tf>
Vec<N, T> closestPointOnLineSegment(Tf &frac, const Vec<N, T> &a,
                                    const Vec<N, T> &b, const Vec<N, T> &p) {
  auto ab = b - a;
  auto dot = (p - a).dot(ab); // projection of ap onto ab
  auto magAB = ab.magSqr();

  // normalized distance along ab from a to the closest point
  frac = magAB > T(0) ? dot / magAB : T(0);

  // check if p projection is beyond endpoints of ab
  if (frac <= T(0))
    return a;
  if (frac >= T(1))
    return b;

  return a + ab * frac;
}
/// Get closest point on line segment ab to point p
template <int N, class T>
Vec<N, T> closestPointOnLineSegment(const Vec<N, T> &a, const Vec<N, T> &b,
                                    const Vec<N, T> &p) {
  T f;
  return closestPointOnLineSegment(f, a, b, p);
}

/// Line-plane intersection test

/// @param[out] d	scalar indicating intersection on line d*l + l0
/// @param[in] l	direction of line d*l + l0
/// @param[in] l0	point on line d*l + l0
/// @param[in] n	normal of plane
/// @param[in] p0	point on plane
/// \returns 1 if single intersection, 0 if no intersection or 2 if line on
/// plane
template <int N, class T, class D>
int linePlaneIntersection(D &d, const Vec<N, T> &l, const Vec<N, T> &l0,
                          const Vec<N, T> &n, const Vec<N, T> &p0) {
  auto a = (p0 - l0).dot(n);
  auto b = l.dot(n);
  if (b == T(0)) { // line and plane parallel
    if (a == T(0))
      return 2; // line on plane
    return 0;
  }
  d = a / b;
  return 1;
}

/// Returns distance between two vectors
template <int N, class T, class U>
inline T dist(const Vec<N, T> &a, const Vec<N, U> &b) {
  return (a - b).mag();
}

/// Return magnitude of vector (for GLSL compatibility)
template <int N, class T> inline T length(const Vec<N, T> &v) {
  return v.mag();
}

/// Return normalized vector
template <int N, class T> inline Vec<N, T> normalize(const Vec<N, T> &v) {
  return v.normalized();
}

template <int N, class T>
inline Vec<N, T> lerp(const Vec<N, T> &input, const Vec<N, T> &target, T amt) {
  return Vec<N, T>(input).lerp(target, amt);
}
/// Returns element with minimum value
template <int N, class T> inline const T &min(const Vec<N, T> &v) {
  int j = 0;
  for (int i = 1; i < N; ++i) {
    if (v[i] < v[j])
      j = i;
  }
  return v[j];
}
template <int N, class T> inline T &min(Vec<N, T> &v) {
  return const_cast<T &>(min(static_cast<const Vec<N, T> &>(v)));
}

/// Returns element with maximum value
template <int N, class T> inline const T &max(const Vec<N, T> &v) {
  int j = 0;
  for (int i = 1; i < N; ++i) {
    if (v[i] > v[j])
      j = i;
  }
  return v[j];
}
template <int N, class T> inline T &max(Vec<N, T> &v) {
  return const_cast<T &>(max(static_cast<const Vec<N, T> &>(v)));
}

/*! Get the normal to a triangle defined by three points
  @param[out] n  Normal
  @param[ in] p1  Point 1
  @param[ in] p2  Point 2
  @param[ in] p3  Point 3
*/
template <class T>
inline void normal(Vec<3, T> &n, const Vec<3, T> &p1, const Vec<3, T> &p2,
                   const Vec<3, T> &p3) {
  cross(n, p2 - p1, p3 - p1);
  n.normalize();
}

/// Returns vector containing element-wise minimum between two vectors
template <int N, class T>
inline Vec<N, T> min(const Vec<N, T> &a, const Vec<N, T> &b) {
  Vec<N, T> r;
  IT(N) { r[i] = a[i] > b[i] ? b[i] : a[i]; }
  return r;
}

/// Returns vector containing element-wise maximum between two vectors
template <int N, class T>
inline Vec<N, T> max(const Vec<N, T> &a, const Vec<N, T> &b) {
  Vec<N, T> r;
  IT(N) { r[i] = a[i] < b[i] ? b[i] : a[i]; }
  return r;
}

/// Pun uniform POD into vector
template <class T, class UniformPOD>
auto punToVec(const UniformPOD &v)
    -> const Vec<sizeof(UniformPOD) / sizeof(T), T> & {
  static_assert(!std::is_polymorphic<UniformPOD>::value,
                "Punning polymorphic class disallowed");
  return std::remove_reference<decltype(punToVec<T>(v))>::type::pun(
      (const T *)&v);
}

template <class T, class UniformPOD>
auto punToVec(UniformPOD &v) -> Vec<sizeof(UniformPOD) / sizeof(T), T> & {
  static_assert(!std::is_polymorphic<UniformPOD>::value,
                "Punning polymorphic class disallowed");
  return std::remove_reference<decltype(punToVec<T>(v))>::type::pun((T *)&v);
}

// Implementation
// --------------------------------------------------------------

template <int N, class T> Vec<N, T> &Vec<N, T>::mag(T v) {
  T m = mag();
  if (m > T(1e-20)) {
    (*this) *= (v / m);
  } else {
    set(T(0));
    (*this)[0] = v;
  }
  return *this;
}

// template <typename T> const char *typeString();

// #define TypeString(A)
//   template <> inline const char *typeString<A>() { return #A; }

// TypeString(char);
// TypeString(unsigned char);
// TypeString(int);
// TypeString(unsigned int);
// TypeString(float);
// TypeString(double);
// TypeString(long double);
// #undef TypeString

template <int N, class T>
void Vec<N, T>::print(FILE *out, const char *append) const {
  fprintf(out, "{");
  if (size()) {
    fprintf(out, "%g", (double)((*this)[0]));
    for (int i = 1; i < N; ++i)
      fprintf(out, ", %g", (double)((*this)[i]));
  }
  fprintf(out, "}%s", append);
}

template <int N, class T> void Vec<N, T>::println(FILE *out) const {
  print(out, "\n");
}

template <int N, class T>
std::ostream &operator<<(std::ostream &out, const Vec<N, T> &v) {
  out << "{";
  if (v.size()) {
    out << v[0];
    for (int i = 1; i < N; ++i)
      out << ", " << v[i];
  }
  out << "}";
  return out;
}

#undef IT
} // namespace al
#endif
