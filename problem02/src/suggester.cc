#include "src/suggester.h"

#include<iostream>
#include<fstream>
#include<algorithm>

using std::pair;

// Load the multimap using sorted string by char as a key.
Suggester::Suggester(string filename) {
  std::ifstream in;
  string line;

  in.open(filename.c_str());

  while (std::getline(in, line)) {
    string sorted_line(line);
    std::sort(sorted_line.begin(), sorted_line.end());
    dict_.insert(pair<string, string>(sorted_line, line));
  }
}

// Find all suggestions based on an input.
// Caller is responsible for cleaning up the returned vector.
vector<string>* Suggester::Suggest(string word) {
  vector<string>* s = new vector<string>;

  string key(word);
  std::sort(key.begin(), key.end());

  // multimap elements with the key = sorted chars in the word
  pair<multimap<string, string>::iterator,
    multimap<string, string>::iterator> v = dict_.equal_range(key);

  for (multimap<string, string>::iterator i = v.first; i != v.second; ++i) {
    if (i->second.compare(word)) {
      s->push_back(i->second);
    }
  }

  std::sort(s->begin(), s->end());
  return s;
}
