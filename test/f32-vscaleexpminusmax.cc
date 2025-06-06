// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.
//
//   Specification: f32-vscaleexpminusmax

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <random>
#include <vector>

#include <gtest/gtest.h>
#include "include/xnnpack.h"
#include "src/xnnpack/buffer.h"
#include "src/xnnpack/common.h"
#include "src/xnnpack/isa-checks.h"
#include "src/xnnpack/microfnptr.h"
#include "src/xnnpack/vscaleexpminusmax.h"
#include "test/replicable_random_device.h"

class VScaleExpMinusMaxMicrokernelTester {
 public:
  VScaleExpMinusMaxMicrokernelTester& elements(size_t elements) {
    assert(elements != 0);
    this->elements_ = elements;
    return *this;
  }

  size_t elements() const { return this->elements_; }

  VScaleExpMinusMaxMicrokernelTester& scale(float scale) {
    assert(std::isfinite(scale));
    assert(scale > 0);
    this->scale_ = scale;
    return *this;
  }

  float scale() const { return this->scale_; }

  VScaleExpMinusMaxMicrokernelTester& iterations(size_t iterations) {
    this->iterations_ = iterations;
    return *this;
  }

  size_t iterations() const { return this->iterations_; }

  void Test(xnn_f32_vscaleexpminusmax_ukernel_fn vscaleexpminusmax) const {
    xnnpack::ReplicableRandomDevice rng;
    // Choose such range that expf(x[i]) overflows, but expf(x[i] - x_max)
    // doesn't. However, the range is still narrow enough that double-precision
    // exp doesn't overflow.
    auto f32rng = [&rng]() {
      return std::uniform_real_distribution<float>(90.0f, 100.0f)(rng);
    };

    xnnpack::Buffer<float> x(elements(), xnnpack::XnnExtraBytes);
    xnnpack::Buffer<float> y(elements());
    xnnpack::Buffer<double> y_ref(elements());
    for (size_t iteration = 0; iteration < iterations(); iteration++) {
      std::generate(x.begin(), x.end(), std::ref(f32rng));

      // Compute reference results.
      const float x_max = *std::max_element(x.begin(), x.begin() + elements());
      for (size_t i = 0; i < elements(); i++) {
        y_ref[i] = double(scale()) * exp(double(x[i]) - double(x_max));
      }

      // Call optimized micro-kernel.
      vscaleexpminusmax(elements() * sizeof(float), x.data(), y.data(), scale(),
                        x_max);

      // Verify results.
      for (size_t i = 0; i < elements(); i++) {
        ASSERT_NEAR(y_ref[i], y[i], std::abs(y_ref[i]) * 1.0e-6)
            << "elements = " << elements() << ", scale = " << scale()
            << ", x_max = " << x_max;
      }
    }
  }

 private:
  size_t elements_{1};
  float scale_{1.0f};
  size_t iterations_{15};
};

#define XNN_TEST_VSCALEEXPMINUSMAX_ELEMENT_EQ(ukernel, arch_flags,             \
                                              element_tile, ...)               \
  TEST(ukernel, element_eq) {                                                  \
    TEST_REQUIRES_ARCH_FLAGS(arch_flags);                                      \
    VScaleExpMinusMaxMicrokernelTester().elements(element_tile).Test(ukernel); \
  }
#define XNN_TEST_VSCALEEXPMINUSMAX_ELEMENT_GT(ukernel, arch_flags,     \
                                              element_tile, ...)       \
  TEST(ukernel, element_gt) {                                          \
    TEST_REQUIRES_ARCH_FLAGS(arch_flags);                              \
    for (size_t element_size = element_tile + 1;                       \
         element_size < ((element_tile == 1) ? 10 : element_tile * 2); \
         element_size++) {                                             \
      VScaleExpMinusMaxMicrokernelTester()                             \
          .elements(element_size)                                      \
          .Test(ukernel);                                              \
    }                                                                  \
  }
#define XNN_TEST_VSCALEEXPMINUSMAX_ELEMENT_LT(ukernel, arch_flags, \
                                              element_tile, ...)   \
  TEST(ukernel, element_lt) {                                      \
    TEST_REQUIRES_ARCH_FLAGS(arch_flags);                          \
    for (size_t element_size = 1; element_size < element_tile;     \
         element_size++) {                                         \
      VScaleExpMinusMaxMicrokernelTester()                         \
          .elements(element_size)                                  \
          .Test(ukernel);                                          \
    }                                                              \
  }
#define XNN_TEST_VSCALEEXPMINUSMAX_ELEMENT_DIV(ukernel, arch_flags,        \
                                               element_tile, ...)          \
  TEST(ukernel, element_div) {                                             \
    TEST_REQUIRES_ARCH_FLAGS(arch_flags);                                  \
    for (size_t element_size = 2 * element_tile;                           \
         element_size < 10 * element_tile; element_size += element_tile) { \
      VScaleExpMinusMaxMicrokernelTester()                                 \
          .elements(element_size)                                          \
          .Test(ukernel);                                                  \
    }                                                                      \
  }

#define XNN_TEST_VSCALEEXPMINUSMAX_SCALE(ukernel, arch_flags, element_tile, \
                                         ...)                               \
  TEST(ukernel, scale) {                                                    \
    TEST_REQUIRES_ARCH_FLAGS(arch_flags);                                   \
    for (size_t element_size = 1; element_size <= 5 * element_tile;         \
         element_size += max(1, element_tile - 1)) {                        \
      VScaleExpMinusMaxMicrokernelTester()                                  \
          .elements(element_size)                                           \
          .scale(0.01f)                                                     \
          .Test(ukernel);                                                   \
      VScaleExpMinusMaxMicrokernelTester()                                  \
          .elements(element_size)                                           \
          .scale(100.0f)                                                    \
          .Test(ukernel);                                                   \
    }                                                                       \
  }

#define XNN_UKERNEL(arch_flags, ukernel, element_tile, datatype, params_type, \
                    init_params)                                              \
  XNN_TEST_VSCALEEXPMINUSMAX_ELEMENT_EQ(ukernel, arch_flags, element_tile,    \
                                        init_params);                         \
  XNN_TEST_VSCALEEXPMINUSMAX_ELEMENT_DIV(ukernel, arch_flags, element_tile,   \
                                         init_params);                        \
  XNN_TEST_VSCALEEXPMINUSMAX_ELEMENT_LT(ukernel, arch_flags, element_tile,    \
                                        init_params);                         \
  XNN_TEST_VSCALEEXPMINUSMAX_ELEMENT_GT(ukernel, arch_flags, element_tile,    \
                                        init_params);                         \
  XNN_TEST_VSCALEEXPMINUSMAX_SCALE(ukernel, arch_flags, element_tile,         \
                                   init_params);
#include "src/f32-vscaleexpminusmax/f32-vscaleexpminusmax.h"
#undef XNN_UKERNEL
