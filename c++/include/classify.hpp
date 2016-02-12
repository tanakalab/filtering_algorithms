/* classify.hpp */

#ifndef __CLASIFICATION_CLASSIFY_HPP__
#define __CLASIFICATION_CLASSIFY_HPP__

#ifndef __CLASIFICATION_OPENFILE_HPP__
#include <openfile.hpp>
#endif

#ifndef __CLASIFICATION_RBT_HPP__
#include <rbt.hpp>
#endif

unsigned simpleSearch(vector<RBT> *&, vector<unsigned>*, string&, unsigned);
bool compareRuleAndPacket(Rule&, string&);
unsigned sequentialSearch(list<Rule> *&, string&);

#endif