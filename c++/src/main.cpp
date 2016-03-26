#include <main.hpp>

int main(int argc, char* argv[])
{
	/* check arguments */
	if (argc != 3) {
		printf("Usage: main <rule list> <pseudo packets>\n");
		return 1;
	}

	/* open and read a rulelist */
	list<Rule> *rulelist = new list<Rule>;
	try {
		readRulelist(argv[1],rulelist);
	} catch (string error_message) {
		cout << error_message; return 1;
	}

	/* open and read packets */
	list<string> *packets = new list<string>;
	try {
		readPackets(argv[2],packets);
	} catch (string error_message) {
		cout << error_message; return 1;
	}

	/* do the sequential search */
	list< list<Result> > results;
	list<Result>* resultOfSequential = new list<Result>;
	classifyViaSequentialSearch(rulelist, packets, resultOfSequential);

	/* make a Run-Based Trie */
	vector<RBT>* rbt = new vector<RBT>;
	makeRunBasedTrie(rulelist,rbt);

	/* do the simple search */
	/*
	list<Result>* resultOfSimpleSearch = new list<Result>;
	{
  	unsigned n = rulelist->size();
		classifyViaSimpleSearch(rbt, n, packets, resultOfSimpleSearch);
	}
	results.push_back(*resultOfSimpleSearch);
	*/

	/* make a Match Run Set Trie */
	vector<MR>* mr = new vector<MR>;
	makeMatchRunSetTrie(rbt,mr);

	/* make a Naive Decision Tree (not pruned Decision Tree) */
	double start, end;
	Dtree *naive_dtree;
	naive_dtree = new Dtree("root");
	start = gettimeofday_sec();
	constructNaiveDtree(naive_dtree, mr);
	end = gettimeofday_sec();
	Result::setConstructTimeOfRBTNDtree(end-start);
	cout << "number of Naive Dtree Node: "; Dtree::showNumberOfNodeOfDtree(); 
	cout << "construct time of Naive Dtree Node: " << Result::getConstructTimeOfRBTNDtree() << endl; 
	//showChild(naive_dtree);
	Dtree::initNumberOfNodeOfDtree();

	/* classify packets via Naive Decision Tree */
	list<Result>* resultOfRBTNDtree = new list<Result>;
	classifyViaRBTNDtree(naive_dtree, mr, packets, resultOfRBTNDtree);
	//cout << Result::getLatencyRBTNDtree() << endl;
	results.push_back(*resultOfRBTNDtree);

	/* make a Decision Tree */
	Dtree *dtree;
	dtree = new Dtree("root");
	start = gettimeofday_sec();
	constructDtree(dtree, mr);
	end = gettimeofday_sec();
	Result::setConstructTimeOfRBTDtree(end-start);
	cout << "number of Dtree Node: "; Dtree::showNumberOfNodeOfDtree(); 
	cout << "construct time of Dtree Node: " << Result::getConstructTimeOfRBTDtree() << endl; 
	//showChild(dtree);

	/* classify packets via Naive Decision Tree */
	list<Result>* resultOfRBTDtree = new list<Result>;
	classifyViaRBTDtree(naive_dtree, mr, packets, resultOfRBTDtree);
	//cout << Result::getLatencyRBTDtree() << endl;
	results.push_back(*resultOfRBTDtree);

	assert(0 == checkClassifyResult(resultOfSequential, results));

	/*
	list<string>::iterator packetIt = packets->begin();
	list<string>::iterator packetItEnd = packets->end();
		
	vector<unsigned> *A = new vector<unsigned>;
	for (unsigned i = 0; i <= rulelist->size(); ++i) { A->push_back(0); }
	while (packetIt != packetItEnd) {
		for (unsigned i = 0; i <= rulelist->size(); ++i)
			(*A)[i] = 0;
		cout << *packetIt << ' ' << sequentialSearch(rulelist, *packetIt) << endl;
		cout << *packetIt << ' ' << simpleSearch(rbt, A, *packetIt, rulelist->size()) << endl;
		cout << *packetIt << ' ' << RBTDtreeSearch(dtree, mr, *packetIt) << endl;
		putchar('\n');
		++packetIt;
	}
	delete A;
	putchar('\n');
	string s = "01001111";
	cout << RBTDtreeSearch(dtree, mr, s) << endl << endl;
	s = "01010000";
	cout << RBTDtreeSearch(dtree, mr, s) << endl;
	*/

	/* delete dynamicaly allocated memories */
	delete packets;
	delete rbt;
	delete mr;
	delete naive_dtree;
	delete dtree;
	delete resultOfSequential;
	//delete resultOfSimpleSearch;
	delete resultOfRBTNDtree;
	delete resultOfRBTDtree;

	return 0;
}
