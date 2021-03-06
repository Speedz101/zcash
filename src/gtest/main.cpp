#include "gtest/gtest.h"
#include "crypto/common.h"
#include "pubkey.h"

#include "libsnark/common/default_types/r1cs_ppzksnark_pp.hpp"
#include "libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp"
#include "zcash/JoinSplit.hpp"
#include "util.h"

struct ECCryptoClosure
{
    ECCVerifyHandle handle;
};

ECCryptoClosure instance_of_eccryptoclosure;

ZCJoinSplit* params;

int main(int argc, char **argv) {
  assert(init_and_check_sodium() != -1);
  libsnark::default_r1cs_ppzksnark_pp::init_public_params();
  libsnark::inhibit_profiling_info = true;
  libsnark::inhibit_profiling_counters = true;
  boost::filesystem::path pk_path = ZC_GetParamsDir() / "sprout-proving.key";
  boost::filesystem::path vk_path = ZC_GetParamsDir() / "sprout-verifying.key";
  params = ZCJoinSplit::Prepared(vk_path.string(), pk_path.string());
  
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
