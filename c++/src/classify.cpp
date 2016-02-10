/* classify.cpp */

#include <classify.hpp>

bool compareRuleAndPacket(Rule& rule, string& packet)
{
	string ruleBitString = rule.getRuleBitString();
	unsigned l = ruleBitString.size();
	unsigned i = 0;
	while (i < l) {
		if (ruleBitString[i] != '*' && ruleBitString[i] != packet[i])
			return false;
		++i;
	}
	return true;
}

unsigned sequentialSearch(list<Rule>*& rulelist, string packet)
{
	list<Rule>::iterator ruleIt = rulelist->begin();
	list<Rule>::iterator ruleItEnd = rulelist->end();

	while (ruleIt != ruleItEnd) {
		if (compareRuleAndPacket(*ruleIt, packet))
			return ruleIt->getRuleNumber();
		++ruleIt;
	}
	
	return 0;
}
