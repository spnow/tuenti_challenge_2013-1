#include "gtest/gtest.h"

#include "src/finder.h"

TEST(Finder, Simple) {
  Finder f;

  vector<string> in;
  in.push_back(".john gets into the plane");
  in.push_back("<john sees paul at the airport");
  in.push_back(".john tells mia they are going to die");
  in.push_back(">the plane crashes");

  vector<string> exp;
  exp.push_back("john sees paul at the airport");
  exp.push_back("john gets into the plane");
  exp.push_back("john tells mia they are going to die");
  exp.push_back("the plane crashes");

  vector<string>* r = f.Find(in);
  for (int i = 0; i < r->size(); ++i) {
    EXPECT_EQ(exp[i], r->at(i)) << "Vectors differ at index " << i;
  }
  delete r;
}

TEST(Finder, WrongInput1) {
  Finder f;

  vector<string> exp;
  exp.push_back("<john gets into the plane");
  exp.push_back(".john sees paul at the airport");

  vector<string>* r = f.Find(exp);
  ASSERT_EQ(NULL, r);
}

TEST(Finder, WrongInput2) {
  Finder f;

  vector<string> exp;
  exp.push_back("<john gets into the plane");
  exp.push_back(".john sees paul at the airport");

  ASSERT_EQ(NULL, f.Find(exp));
}

TEST(Finder, InvalidPrevAppearsAfter) {
  Finder f;

  vector<string> exp;
  exp.push_back(".john sees paul at the airport");
  exp.push_back("<john gets into the plane");
  exp.push_back(".some crap");
  exp.push_back(".john gets into the plane"); // WRONG

  ASSERT_EQ(NULL, f.Find(exp));
}

TEST(Finder, InvalidSelfPrev) {
  Finder f;

  vector<string> exp;
  exp.push_back(".john sees paul at the airport");
  exp.push_back("<john sees paul at the airport");

  ASSERT_EQ(NULL, f.Find(exp));
}

TEST(Finder, InvalidSelfFuture) {
  Finder f;

  vector<string> exp;
  exp.push_back(".john sees paul at the airport");
  exp.push_back(">john sees paul at the airport");

  ASSERT_EQ(NULL, f.Find(exp));
}

TEST(Finder, Valid) {
  Finder f;

  vector<string> exp;
  exp.push_back(".john gets into the plane");
  exp.push_back("<john sees paul at the airport.");
  exp.push_back(".john tells mia they are going to die");
  exp.push_back(">the plane crashes");
  exp.push_back(".the plane takes off");
  exp.push_back(".mia sees through the window an isolated island");
  exp.push_back("<the plane crashes");

  vector<string>* r = f.Find(exp);
  ASSERT_EQ(1, r->size());
  ASSERT_EQ("valid", r->at(0));
}

TEST(Finder, Complex) {
  Finder f;

  vector<string> in;
  in.push_back(".Daniel charges besides the law");
  in.push_back(".Richard tests towards the athlete");
  in.push_back(".Frank and Ben argue inside the postage");
  in.push_back(".Boone disappears amid the produce");
  in.push_back(".Sun fastens atop the teller");
  in.push_back(".Michael, Libby and Kate to beneath the ethiopia");
  in.push_back(">Locke and Sun put out the nail");
  in.push_back(".Sayid indicates beyond");
  in.push_back("<Locke and Sun put out the nail");
  in.push_back(".Kate, Rose and Hurley stick");
  in.push_back(".Juliet and Bernard seem over the double");
  in.push_back(".Ben and Charlotte thank beyond the skiing");
  in.push_back(">Charlie and Charlotte obtain around the dragonfly");
  in.push_back(".Claire inresss beside the throat");
  in.push_back("<Charlie and Charlotte obtain around the dragonfly");
  in.push_back(".Richard, Claire and Frank think beside the overcoat");
  in.push_back(".Kate states beneath the evening");
  in.push_back(".Ben and Ana ought against the gander");

  vector<string> exp;
  exp.push_back("Daniel charges besides the law");
  exp.push_back("Richard tests towards the athlete");
  exp.push_back("Frank and Ben argue inside the postage");
  exp.push_back("Boone disappears amid the produce");
  exp.push_back("Sun fastens atop the teller");
  exp.push_back("Michael, Libby and Kate to beneath the ethiopia");
  exp.push_back("Locke and Sun put out the nail");
  exp.push_back("Sayid indicates beyond");
  exp.push_back("Kate, Rose and Hurley stick");
  exp.push_back("Juliet and Bernard seem over the double");
  exp.push_back("Ben and Charlotte thank beyond the skiing");
  exp.push_back("Charlie and Charlotte obtain around the dragonfly");
  exp.push_back("Claire inresss beside the throat");
  exp.push_back("Richard, Claire and Frank think beside the overcoat");
  exp.push_back("Kate states beneath the evening");
  exp.push_back("Ben and Ana ought against the gander");

  vector<string>* r = f.Find(in);
  for (int i = 0; i < r->size(); ++i) {
    EXPECT_EQ(exp[i], r->at(i)) << "Vectors differ at index " << i;
  }
  delete r;
}

TEST(Finder, Corner) {
  Finder f;

  vector<string> in;
  in.push_back(".Richard, Boone and Frank enable underneath the deborah");
  in.push_back(".Charlotte and Daniel want atop the milk");
  in.push_back(">Locke and Lucia sleep amidst the fiber");
  in.push_back(".Daniel and Shannon succeed after the timer");
  in.push_back(">Frank and Vincent fill behind the sound");
  in.push_back(".Ana, Boone and Miles state around the period");
  in.push_back("<Frank and Vincent fill behind the sound");
  in.push_back(".Richard rises for the creek");
  in.push_back("<Locke and Lucia sleep amidst the fiber");
  in.push_back(".Vincent and Rose obtain amongst the storm");

  vector<string>* r = f.Find(in);
  ASSERT_EQ(1, r->size());
  ASSERT_EQ("valid", r->at(0));
  delete r;
}
