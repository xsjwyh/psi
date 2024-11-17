// Copyright 2022 Ant Group Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <future>
#include <iostream>

#include "benchmark/benchmark.h"
#include "psi/psi21_experiment/el_q_psi/el_opprf.h"
#include "psi/psi21_experiment/el_q_psi/el_q_psi.h"
#include "yacl/base/exception.h"
#include "yacl/crypto/hash/hash_utils.h"
#include "yacl/link/test_util.h"

namespace {
std::vector<uint128_t> CreateRangeItems(size_t begin, size_t size) {
  std::vector<uint128_t> ret(size);
  for (size_t i = 0; i < size; i++) {
    auto hash = yacl::crypto::Blake3(std::to_string(begin + i));
    memcpy(&ret[i], hash.data(), sizeof(uint128_t));
  }
  return ret;
}

void ElQPsiSend(const std::shared_ptr<yacl::link::Context>& link_ctx,
                const std::vector<uint128_t>& items_hash) {
  // auto ot_recv = psi::kkrt::GetKkrtOtSenderOptions(link_ctx, 512);
  // return psi::kkrt::KkrtPsiSend(link_ctx, ot_recv, items_hash);
  std::vector<uint64_t> shares;
  for (size_t i = 0; i < items_hash.size(); i++) {
    uint64_t item = 0;
    shares.push_back(item);
  }

  return psi::psi::ElOpprfSend(link_ctx, items_hash, shares);
}

std::vector<uint64_t> ElQPsiRecv(
    const std::shared_ptr<yacl::link::Context>& link_ctx,
    const std::vector<uint128_t>& items_hash) {
  // auto ot_send = psi::kkrt::GetKkrtOtReceiverOptions(link_ctx, 512);
  // return psi::kkrt::KkrtPsiRecv(link_ctx, ot_send, items_hash);
  return psi::psi::ElOpprfRecv(link_ctx, items_hash);
}

}  // namespace

static void BM_El_Q_Psi(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    size_t n = state.range(0);
    auto alice_items = CreateRangeItems(1, n);
    auto bob_items = CreateRangeItems(2, n);

    auto contexts = yacl::link::test::SetupWorld(2);

    state.ResumeTiming();

    std::future<void> kkrt_psi_sender =
        std::async([&] { return ElQPsiSend(contexts[0], alice_items); });
    std::future<std::vector<uint64_t>> kkrt_psi_receiver =
        std::async([&] { return ElQPsiRecv(contexts[1], bob_items); });

    kkrt_psi_sender.get();
    auto results_b = kkrt_psi_receiver.get();
  }
}

// [256k, 512k, 1m, 2m, 4m, 8m]
BENCHMARK(BM_El_Q_Psi)
    ->Unit(benchmark::kMillisecond)
    ->Arg(256 << 10)
    ->Arg(512 << 10)
    ->Arg(1 << 20)
    ->Arg(2 << 20)
    ->Arg(4 << 20)
    ->Arg(8 << 20);
