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
	//list< list<Result> > results;
	//list<Result>* resultOfSequential = new list<Result>;
	//classifyViaSequentialSearch(rulelist, packets, resultOfSequential);

	/* make a Run-Based Trie */
	vector<RBT>* rbt = new vector<RBT>;
	makeRunBasedTrie(rulelist,rbt);

	/* do the simple search */
	//list<Result>* resultOfSimpleSearch = new list<Result>;
	//{
  	//unsigned n = rulelist->size();
		//classifyViaSimpleSearch(rbt, n, packets, resultOfSimpleSearch);
	//}
	//results.push_back(*resultOfSimpleSearch);

	/* make a Match Run Set Trie */
	vector<MR>* mr = new vector<MR>;
	makeMatchRunSetTrie(rbt,mr);

	/*
	for (unsigned i = 1; i <= mr->size(); ++i) { 
		postTraverse(&(*mr)[i]);
		putchar('\n');
	}
	*/

	double start, end;
	// /* make a Naive Decision Tree (not pruned Decision Tree) */
	// Dtree *naive_dtree;
	// naive_dtree = new Dtree("root");
	// start = gettimeofday_sec();
	// constructNaiveDtree(naive_dtree, mr);
	// end = gettimeofday_sec();
	// Result::setConstructTimeOfRBTNDtree(end-start);
	// cout << "number of Naive Dtree Node: "; Dtree::showNumberOfNodeOfDtree(); 
	// cout << "construct time of Naive Dtree Node: " << Result::getConstructTimeOfRBTNDtree() << endl; 
	// //showChild(naive_dtree);
	// Dtree::initNumberOfNodeOfDtree();

	// /* classify packets via Naive Decision Tree */
	// list<Result>* resultOfRBTNDtree = new list<Result>;
	// classifyViaRBTNDtree(naive_dtree, mr, packets, resultOfRBTNDtree);
	// // cout << Result::getLatencyRBTNDtree() << endl;
	// results.push_back(*resultOfRBTNDtree);

	/* make a Decision Tree */
	Dtree *dtree;
	dtree = new Dtree("root");
	start = gettimeofday_sec();
	constructDtree(dtree, mr);
	end = gettimeofday_sec();
	Result::setConstructTimeOfRBTDtree(end-start);
	//cout << "number of rule: " << rulelist->size() << endl;
	cout << "number of Decision Tree Node: "; Dtree::showNumberOfNodeOfDtree(); 
	cout << "construct time of Decision Tree: " << Result::getConstructTimeOfRBTDtree() << endl; 
	cout << "memory for construct Decision Tree: " << getrusageMem() << endl; 
	//showChild(dtree);

	/* classify packets via Decision Tree */
	list<Result>* resultOfRBTDtree = new list<Result>;
	classifyViaRBTDtree(dtree, mr, packets, resultOfRBTDtree);
	cout << "Decision Tree Search Time: "<< Result::getLatencyRBTDtree() << endl;
	//results.push_back(*resultOfRBTDtree);

	//assert(0 == checkClassifyResult(resultOfSequential, results));

	/* delete dynamicaly allocated memories */
	delete packets;
	delete rbt;
	delete mr;
	//delete naive_dtree;
	delete dtree;
	//delete resultOfSequential;
	//delete resultOfSimpleSearch;
	//delete resultOfRBTNDtree;
	delete resultOfRBTDtree;

	return 0;
}
