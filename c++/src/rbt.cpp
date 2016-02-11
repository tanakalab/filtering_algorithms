/* rbt.cpp */

#include <rbt.hpp>

void addMRTInfo(MR* mr)
{
	MR *ptr = mr, *base = mr;

	ptr = ptr->getParent();
	while (NULL != ptr) {
		if (0 < ptr->getWeight()) {
			ptr->setMRInfo(base->getNodeString());
		}
		ptr = ptr->getParent();
	}
}

void MRTInfoTraverse(MR* mr)
{
	if (NULL == mr) { return; }

	MRTInfoTraverse(mr->getLeft());
	MRTInfoTraverse(mr->getRight());

	if (mr->getWeight() > 0) { addMRTInfo(mr); }
}

void settingMRInfo(vector<MR>* mrt)
{
	vector<MR>::iterator it = mrt->begin();
	vector<MR>::iterator end = mrt->end();
	while (it != end) {
		MRTInfoTraverse(&(*it));
		++it;
	}
}

void moveRun(MR* p, MR* c)
{
	if (NULL != p->getRun()) {
		list<Run>::iterator it = p->getRun()->begin();
		list<Run>::iterator end = p->getRun()->end();
		while (it != end) {
			c->setRun(*it);
			++it;
		}
	}
}

void updateMRT(MR* mrp, MR* mrc, char c)
{
	unsigned i = mrp->getTrieNumber();
	if (NULL == mrc) { 
		if ("p" == mrp->getNodeString())
			if ('0' == c) { mrp->setLeft(new MR(c, i, "0", mrp)); }
			else { mrp->setRight(new MR(c, i, "1", mrp)); }
		else
			if ('0' == c) { mrp->setLeft(new MR(c, i, mrp->getNodeString()+"0", mrp)); }
			else { mrp->setRight(new MR(c, i, mrp->getNodeString()+"1", mrp)); }
	}
	mrp->setWeight(0);
	if ('0' == c) { 
		mrp->getLeft()->setWeight(999);
		moveRun(mrp, mrp->getLeft()), mrp->deleteRun(); 
	}
	else { 
		mrp->getRight()->setWeight(999);
		moveRun(mrp, mrp->getRight()), mrp->deleteRun(); 
	}
}

bool noMRS(MR* mr)
{
	if (NULL == mr) { return true; }
	if (0 == mr->getWeight()) { return true; }

	return false;
}

void changeMRSet(MR* mr)
{
	if (NULL == mr) { return ; }

	if (mr->getWeight() > 0) {
		if (noMRS(mr->getLeft()) && !noMRS(mr->getRight())) { /* exist _left and no _right */
			updateMRT(mr, mr->getLeft(), '0');
		}
		if (!noMRS(mr->getLeft()) && noMRS(mr->getRight())) { /* no _left and exist _right */
			updateMRT(mr, mr->getRight(), '1');
		}
	}

	changeMRSet(mr->getLeft());
	changeMRSet(mr->getRight());
}

void changeAllMRSet(vector<MR>* mrt)
{
	vector<MR>::iterator it = mrt->begin();
	vector<MR>::iterator end = mrt->end();
	while (it != end) {
		changeMRSet(&(*it));
		++it;
	}
}

void addRun(MR* wptr, MR* base)
{
	list<Run>::iterator it = wptr->getRun()->begin();
	list<Run>::iterator end = wptr->getRun()->end();
	while (it != end) {
		base->setRun(*it);
		++it;
	}
}

void walkToRoot(MR* ptr)
{
	MR *wptr = ptr, *base = ptr;
	unsigned baseWeight = base->getWeight();

	wptr = wptr->getParent();
	while (NULL != wptr) {
		if (NULL != wptr->getRun() || 'p' == wptr->getNodeBit()) {
			wptr->subtractWeight(baseWeight);
			if ('p' != wptr->getNodeBit()) { addRun(wptr, base); }
			//wptr->setMRInfo(base->getNodeString());
			if (0 == wptr->getWeight()) { wptr->deleteRun(); }
		}
		wptr = wptr->getParent();
	}
}

void MRTWeightTraverse(MR* mr)
{
	if (NULL == mr) { return; }

	MRTWeightTraverse(mr->getLeft());
	MRTWeightTraverse(mr->getRight());

	if (mr->getWeight() > 0) { walkToRoot(mr); }
}

void allMRTWeightTraverse(vector<MR>* mrt)
{
	vector<MR>::iterator it = mrt->begin();
	vector<MR>::iterator end = mrt->end();
	while (it != end) {
		MRTWeightTraverse(&(*it));
		++it;
	}
}

void traverseAndMakeMRTNode(RBT* rbt, MR* mr, unsigned& w, unsigned& i)
{
	if (NULL == rbt) { return ; }

	if ("p" == mr->getNodeString()) { mr->setWeight(pow(2, w+1-i)); }
	if (NULL != rbt->getRun()) {
		list<Run>::iterator it = rbt->getRun()->begin();
		list<Run>::iterator itEnd = rbt->getRun()->end();
		while (it != itEnd) {
			mr->setRun(*it);
			++it;
		}
		mr->setWeight(pow(2,w+1-i-mr->getNodeString().length()));
	}

  if (NULL != rbt->getLeft()) 
		mr->setLeft(new MR('0', i, rbt->getLeft()->getNodeString(), mr)); 
  if (NULL != rbt->getRight())
		mr->setRight(new MR('1', i, rbt->getRight()->getNodeString(), mr)); 

	traverseAndMakeMRTNode(rbt->getLeft(), mr->getLeft(), w, i);
	traverseAndMakeMRTNode(rbt->getRight(), mr->getRight(), w, i);
}

void copyRBTtoMRT(vector<RBT>*& rbt, vector<MR>* mr)
{
	unsigned w = rbt->size()-1;
	for (unsigned i = 1; i < w+1; ++i) {
		traverseAndMakeMRTNode(&(*rbt)[i], &(*mr)[i], w, i);
	}
}

void createTheMRTRootNodes(vector<MR>* mr, unsigned w)
{
  mr->push_back(MR(' ', 0, " ", NULL));
	unsigned i = 1;
	while (i < w) {
		mr->push_back(MR('p', i, "p", NULL));
		++i;
	}
}

void makeMatchRunSetTrie(vector<RBT>*& rbt, vector<MR>* mr)
{
	createTheMRTRootNodes(mr, rbt->size());
	copyRBTtoMRT(rbt,mr);
	allMRTWeightTraverse(mr);
	changeAllMRSet(mr);
	settingMRInfo(mr);
}

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

void postTraverse(MR *mr)
{
	if (NULL == mr) { return ; }
	postTraverse(mr->getLeft());
	postTraverse(mr->getRight());

	if (mr->getWeight() > 0) {
		cout << mr->getNodeString() << ' ' << mr->getWeight();
	list<Run>* runlist;

	if (NULL != (runlist = mr->getRun())) {
		printf(": ");
		list<Run>::iterator it, itEnd;
		it = runlist->begin(), itEnd = runlist->end();
		while (it != itEnd) {
			cout << '(' << it->getRuleNumber() << ',' << it->getRunNumber() << ") ";
			++it;
		}
	}

	list<string>* slist;
	if (NULL != (slist = mr->getMRInfo())) {
		printf(" -- [");
		list<string>::iterator it, itEnd;
		it = slist->begin(), itEnd = slist->end();
		while (it != itEnd) {
			cout << *it << ", ";
			++it;
		}
		cout << "]";
	}
	putchar('\n');
	}
}
