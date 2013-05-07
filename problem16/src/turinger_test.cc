#include "gtest/gtest.h"

#include "src/turinger.h"

#include <fstream>

TEST(Turinger, Simple) {
  std::string in = "#00000011#00001010#00001010#00001000#00001001#00000010#00001010#00000001#00010001#00000001#00000101#00001000#00000100#";
  std::string expected = "#11111111#";

  vs tape(in.begin(), in.end());
  vs exp(expected.begin(), expected.end());

  Turinger t;
  vs out = t.Turing(tape);

  for (int i = 0; i < out.size(); ++i) {
    ASSERT_EQ(expected[i], out[i]);
  }
}

TEST(Turinger, Fat) {
  std::string in = "#0000000000001100#0000000000010000#00000000000010010#0000001000010100#0000000000010011#";
  std::string expected = "#0001101101101100#";

  vs tape(in.begin(), in.end());
  vs exp(expected.begin(), expected.end());

  Turinger t;
  vs out = t.Turing(tape);

  for (int i = 0; i < out.size(); ++i) {
    ASSERT_EQ(expected[i], out[i]);
  }
}
