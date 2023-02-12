#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  int currentpos = 0;
  int temppos = 0;
  int wordlength = 0;
  string word;
  char letter;
  set<string> ParsedWords;

  convToLower(rawWords);

  while(currentpos <= rawWords.size())
  {
    letter = rawWords[currentpos];

    if(ispunct(rawWords[currentpos]) || isblank(rawWords[currentpos])|| currentpos == rawWords.size() || letter == '-'){
      wordlength = currentpos - temppos;
      string word = rawWords.substr(temppos, wordlength);
      if(wordlength > 1){
        word = convToLower(word);
        ParsedWords.insert(word);
      }
      temppos = currentpos + 1;
    }
    currentpos++;
  }
  return ParsedWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}