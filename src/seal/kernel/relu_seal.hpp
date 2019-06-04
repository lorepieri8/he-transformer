//*****************************************************************************
// Copyright 2018-2019 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#pragma once

#include <memory>
#include <vector>

#include "ngraph/type/element_type.hpp"
#include "seal/he_seal_backend.hpp"
#include "seal/seal_ciphertext_wrapper.hpp"
#include "seal/seal_plaintext_wrapper.hpp"

namespace ngraph {
namespace he {
inline void scalar_relu_seal(const HEPlaintext& arg, HEPlaintext& out) {
  const std::vector<float>& arg_vals = arg.get_values();
  std::vector<float> out_vals(arg.num_values());

  auto relu = [](float f) { return f > 0 ? f : 0.f; };
  // TODO: remove
  auto relu6 = [](double d) {
    if (d < 0) {
      return 0.0;
    }
    if (d > 6) {
      return 6.0;
    }
    return d;
  };

  // TODO: set to relu!
  std::transform(arg_vals.begin(), arg_vals.end(), out_vals.begin(), relu6);
  out.set_values(out_vals);
}

inline void relu_seal(const std::vector<HEPlaintext>& arg,
                      std::vector<HEPlaintext>& out, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    scalar_relu_seal(arg[i], out[i]);
  }
}

}  // namespace he
}  // namespace ngraph