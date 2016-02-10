/* rbt.cpp */

#include <rbt.hpp>

void traverseAndMakeRBTNode(RBT *rbt, Run run)
{
	string bitString = run.getBitString();
	unsigned l = bitString.length();
	unsigned tn = rbt->getTrieNumber();
	unsigned i = 0;
	RBT* ptr = rbt;

	while (i < l) {
		if (bitString[i] == '0') {
			if (NULL == ptr->getLeft()) {
				RBT* lptr = new RBT('0', tn, bitString.substr(0,i+1));
				ptr->setLeft(lptr);
			}
			ptr = ptr->getLeft();
		}
		else {
			if (NULL == ptr->getRight()) {
				RBT* rptr = new RBT('1', tn, bitString.substr(0,i+1));
				ptr->setRight(rptr);
			}
			ptr = ptr->getRight();
		}
		++i;
	}

	ptr->setRun(run);
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
			traverseAndMakeRBTNode(&(*rbt)[rpIt->getStartBit()], rpIt->getRun());
			//cout << '(' << rpIt->getRun().getBitString() << ',' << rpIt->getStartBit() << ')' << ' ';
			++rpIt;
		}
		//cout << "\n=== " << ruleIt->getRuleNumber() << " ===\n";
		++ruleIt;
	}
}

void postTraverse(RBT *rbt)
{
	if (NULL == rbt) { return ; }
	postTraverse(rbt->getLeft());
	postTraverse(rbt->getRight());
	list<Run>* runlist;

	if (NULL != (runlist = rbt->getRun())) {
		cout << rbt->getNodeString() << ": ";
		list<Run>::iterator it, itEnd;
		it = runlist->begin(), itEnd = runlist->end();
		while (it != itEnd) {
			cout << '(' << it->getRuleNumber() << ',' << it->getRunNumber() << ',' << it->isTerminal() << ") ";
			++it;
		}
		putchar('\n');
	}
}
