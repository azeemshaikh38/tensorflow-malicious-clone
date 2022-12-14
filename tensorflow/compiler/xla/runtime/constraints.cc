/* Copyright 2022 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/compiler/xla/runtime/constraints.h"

#include <utility>

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"
#include "tfrt/support/error_util.h"  // from @tf_runtime

namespace xla {
namespace runtime {

using llvm::ArrayRef;
using llvm::Expected;
using llvm::raw_ostream;
using llvm::StringRef;

using tfrt::MakeStringError;

raw_ostream& operator<<(raw_ostream& os, const ArgumentConstraint& constraint) {
  auto str = [](ArgumentConstraint constraint) {
    switch (constraint) {
      case ArgumentConstraint::kResolved:
        return "resolved";
      case ArgumentConstraint::kRank:
        return "rank";
      case ArgumentConstraint::kShape:
        return "shape";
      case ArgumentConstraint::kValue:
        return "value";
      default:
        llvm_unreachable("unknown operand constraint");
    }
  };

  os << str(constraint);
  return os;
}

raw_ostream& operator<<(raw_ostream& os,
                        ArrayRef<ArgumentConstraint> constraints) {
  os << "[";
  llvm::interleaveComma(constraints, os);
  os << "]";
  return os;
}

Expected<ArgumentConstraint> ParseArgumentConstraint(StringRef str) {
  if (str == "rank") return ArgumentConstraint::kRank;
  if (str == "shape") return ArgumentConstraint::kShape;
  if (str == "value") return ArgumentConstraint::kValue;
  return MakeStringError("unknown operand constraint: ", str);
}

}  // namespace runtime
}  // namespace xla
