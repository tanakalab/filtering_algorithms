/* classify.cpp */

#include <classify.hpp>

unsigned RBTDtreeSearch(Dtree *&d, vector<MR> *&mrt, string& packet)
{
	MR* mptr;
	Dtree* dptr = d;
	unsigned w = packet.length();
	unsigned result;

	for (unsigned t = 1; t <= w; ++t) {
		int index = -1;
		mptr = &(*mrt)[t];
		for (unsigned i = t-1; i < w; ++i) {
			//cout << "dindex: " << mptr->getDindex() << endl;
			if (-1 != mptr->getDindex()) { index = mptr->getDindex(); }
			if ('0' == packet[i]) {
				if (NULL != mptr->getLeft()) { 
					mptr = mptr->getLeft(); 
//					cout << packet[i] << endl;
				}
				else { break; }
			} else {
				if (NULL != mptr->getRight()) { 
					mptr = mptr->getRight(); 
					//cout << packet[i] << endl;
				}
				else { break; }
			}
		}
		//cout << "index: " << index << endl;
		//
		if (dptr->getNodeString() == "dummy") {
			printf("dummy\n"); break;
		}
		//
		if (-1 != mptr->getDindex()) { index = mptr->getDindex(); }
		dptr = (*(dptr->getChild()))[index];
		//cout << dptr->getNodeString() << endl;
		if (0 != dptr->getRule()) { 
			result = dptr->getRule(); 
			break; 
		}
	}

	return result;
}

unsigned simpleSearch(vector<RBT>*& rbt, vector<unsigned> *A, string& packet, unsigned n)
{
	RBT* ptr;
	unsigned w = packet.length();
	unsigned match = n+1;
	list<Run>::iterator runIt, runItEnd;

	for (unsigned t = 1; t <= w; ++t) {
		ptr = &(*rbt)[t];
		for (unsigned i = t-1; i < w; ++i) {
			if ('0' == packet[i])
				if (NULL != ptr->getLeft()) { ptr = ptr->getLeft(); }
				else { break; }
			else 
				if (NULL != ptr->getRight()) { ptr = ptr->getRight(); }
				else { break; }
			if (NULL != ptr->getRun()) {
				runIt = ptr->getRun()->begin(), runItEnd = ptr->getRun()->end();
				while (runIt != runItEnd) {
					unsigned j = runIt->getRuleNumber();
					unsigned k = runIt->getRunNumber();
					if (k-1 == (*A)[j]) {
						(*A)[j] = k;
						if (runIt->isTerminal())
							if (j < match) { match = j; }
					}
					++runIt;
				}
			}
		}
	}

	return match;
}

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

unsigned sequentialSearch(list<Rule>*& rulelist, string& packet)
{
	list<Rule>::iterator ruleIt = rulelist->begin();
	list<Rule>::iterator ruleItEnd = rulelist->end();

	while (ruleIt != ruleItEnd) {
		if (compareRuleAndPacket(*ruleIt, packet))
			return ruleIt->getRuleNumber();
		++ruleIt;
	}
	
	return rulelist->size()+1;
}
