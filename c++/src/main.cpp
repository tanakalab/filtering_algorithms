#include <main.hpp>

int main(int argc, char* argv[])
{
	/* check arguments */
	if (argc != 3) {
		printf("Usage: main <rule list> <pseudo packets>\n");
		return 1;
	}

	/* open and read rulelist */
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

	/* make Run-Based Trie */
	vector<RBT>* rbt = new vector<RBT>;
	makeRunBasedTrie(rulelist,rbt);

	/* make Match Run Set Trie */
	vector<MR>* mr = new vector<MR>;
	makeMatchRunSetTrie(rbt,mr);

	{
		unsigned i = 1;
		while (i <= 4) {
			postTraverse(&((*mr)[i]));
			putchar('\n');
			++i;
		}
	}

	/*
	list<string>::iterator packetIt = packets->begin();
	list<string>::iterator packetItEnd = packets->end();
		
	vector<unsigned> *A = new vector<unsigned>;
	for (unsigned i = 0; i <= rulelist->size(); ++i)
			A->push_back(0); 
	while (packetIt != packetItEnd) {
		for (unsigned i = 0; i <= rulelist->size(); ++i)
			(*A)[i] = 0;
		cout << *packetIt << ' ' << sequentialSearch(rulelist, *packetIt) << endl;
		cout << *packetIt << ' ' << simpleSearch(rbt, A, *packetIt, rulelist->size()) << endl;
		putchar('\n');
		++packetIt;
	}
	delete A;
	*/

	/* delete dynamicaly allocated memories */
	delete rulelist;
	delete packets;
	delete rbt;

	return 0;
}
