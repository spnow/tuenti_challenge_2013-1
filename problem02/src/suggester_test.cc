#include "gtest/gtest.h"

#include "src/suggester.h"

TEST(Suggester, Simple) {
  Suggester s("build/smallDictionary");

  vector<string> exp;
  exp.push_back("asmfoxgpbus");
  exp.push_back("foxgpbusasm");
  exp.push_back("oxgpbusasmf");
  exp.push_back("sasmfoxgpbu");

  vector<string>* sug = s.Suggest("gpbusasmfox");
  for (int i = 0; i < exp.size(); ++i) {
    EXPECT_EQ(exp[i], sug->at(i)) << "Vectors differ at index " << i;
  }
}

TEST(Suggester, Empty) {
  Suggester s("build/null");

  vector<string>* sug = s.Suggest("gpbusasmfox");
  ASSERT_EQ(0, sug->size());
}

TEST(Suggester, Hard) {
  Suggester s("build/bigDictionary");

  vector<string> exp;
  exp.push_back("lnjolaaaauojqjnrybjrqtsatsomwbxdxshatdrfuhqncjpymjcqscxhfpswtvnlqiaixskwwwqucolyyholxtrobhsqg");
  exp.push_back("olxtrobhsqglnjolaaaauojqjnrybjrqtsatsomwbxdxshatdrfuhqncjpymjcqscxhfpswtvnlqiaixskwwwqucolyyh");
  exp.push_back("qjnrybjrqtsatsomwbxdxshatdrfuhqncjpymjcqscxhfpswtvnlqiaixskwwwqucolyyholxtrobhsqglnjolaaaauoj");
  exp.push_back("uhqncjpymjcqscxhfpswtvnlqiaixskwwwqucolyyholxtrobhsqglnjolaaaauojqjnrybjrqtsatsomwbxdxshatdrf");

  vector<string>* sug = s.Suggest("aaaauojqjnrybjrqtsatsomwbxdxshatdrfuhqncjpymjcqscxhfpswtvnlqiaixskwwwqucolyyholxtrobhsqglnjol");
  for (int i = 0; i < exp.size(); ++i) {
    EXPECT_EQ(exp[i], sug->at(i)) << "Vectors differ at index " << i;
  }
}
