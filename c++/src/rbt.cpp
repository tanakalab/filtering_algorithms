/* rbt.cpp */

#include <rbt.hpp>

void traverseAndMakeRBTNode(RBT rbt, Run run)
{
	printf("%d ", rbt.getTrieNumber());
	cout << run.getBitString() << ' ';
	if (run.isTerminal())
	 putchar('t');
	putchar('\n');	
}

list<RunPair>* cutOutRun(Rule rule)
{
	unsigned ruleNumber = rule.getRuleNumber();
	string bitString = rule.getRuleBitString();
	unsigned w = bitString.length();
	unsigned i = 0;
	unsigned runNumber = 1;
	bool flag = false;
	string buf = "";
	list<RunPair>* runPair = new list<RunPair>;

	while (i < w) {
		if ('*' == bitString[i]) {
			if (true == flag) {
				Run run = Run(buf, runNumber, ruleNumber);
				runPair->push_back(RunPair(i+1-buf.length(),run));
				flag = false, buf = "", ++runNumber;
			}
		}
		else 
			flag = true, buf += bitString[i];
		++i;
	}

	if (true == flag) {
		Run run = Run(buf, runNumber, ruleNumber);
		runPair->push_back(RunPair(i+1-buf.length(),run));
	}

	list<RunPair>::iterator it = runPair->end();
	--it;

	Run tmpRun = it->getRun();
	unsigned tmpStart = it->getStartBit();
	tmpRun.setTerminalTrue();

	runPair->pop_back();
	runPair->push_back(RunPair(tmpStart, tmpRun));

	return runPair;
}

void createTheRBTRootNodes(vector<RBT>* rbt, unsigned w)
{
	/* create the root nodes not to rbt[w-1] but to rbt[w] */
  rbt->push_back(RBT(' ', 0, " "));
	unsigned i = 1;
	while (i <= w) {
		rbt->push_back(RBT('p', i, "p"));
		++i;
	}
}

void makeRunBasedTrie(list<Rule>*& rulelist, vector<RBT> *rbt)
{
	list<Rule>::iterator ruleIt = rulelist->begin();
	list<Rule>::iterator ruleItEnd = rulelist->end();

	createTheRBTRootNodes(rbt,ruleIt->getRuleBitString().size());

	list<RunPair>* rpPtr;
	list<RunPair>::iterator rpIt, rpItEnd; 
	while (ruleIt != ruleItEnd) {
		rpPtr = cutOutRun(*ruleIt);
		rpIt = rpPtr->begin(), rpItEnd = rpPtr->end();
		while (rpIt != rpItEnd) {
			traverseAndMakeRBTNode((*rbt)[rpIt->getStartBit()], rpIt->getRun());
			//cout << '(' << rpIt->getRun().getBitString() << ',' << rpIt->getStartBit() << ')' << ' ';
			++rpIt;
		}
		//cout << "\n=== " << ruleIt->getRuleNumber() << " ===\n";
		++ruleIt;
	}
}
