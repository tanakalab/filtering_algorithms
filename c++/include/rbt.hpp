/* rbt.hpp */

#ifndef __CLASIFICATION_RBT_HPP__
#define __CLASIFICATION_RBT_HPP__

#ifndef __CLASIFICATION_OPENFILE_HPP__
#include <openfile.hpp>
#endif

#include <vector>

class Run {
	private:
		string _bitString;
		unsigned _runNumber;
		unsigned _ruleNumber;
		bool _terminal;
	public:
		Run() { }
		Run(string bitString, unsigned runNumber, unsigned ruleNumber) {
			_bitString = bitString;
			_runNumber = runNumber;
			_ruleNumber = ruleNumber;
			_terminal = false;
		}
		~Run() { /* printf("call the Run deconstructor.\n"); */ }
		string getBitString() { return _bitString; }
		unsigned getRunNumber() { return _runNumber; }
		unsigned getRuleNumber() { return _ruleNumber; }
		bool isTerminal() { return _terminal; }
		void setTerminalTrue() { _terminal = true; }
};	

class RBT {
	private:
		static long unsigned _number_of_node_of_rbt;
		char _nodeBit;
		string _nodeString;
		unsigned _trieNumber;
		unsigned _dIndex;        /* an index for a Decision Tree Search */
		RBT* _left;
		RBT* _right;
		list<Run>* _runlist;
	public:
		RBT() { }
		RBT(char nodeBit, unsigned trieNumber, string nodeString) {
			_nodeBit = nodeBit;
			_nodeString = nodeString;
			_trieNumber = trieNumber;
			_dIndex = 0;
			_left = NULL;
			_right = NULL;
			_runlist = NULL;
		}
		~RBT() { /* printf("call a RBT deconstructor.\n"); */ }
		static void showNumberOfNodeOfRBT() { cout << _number_of_node_of_rbt << endl; }
		char getNodeBit() { return _nodeBit; }
		string getNodeString() { return _nodeString; }
		unsigned getTrieNumber() { return _trieNumber; }
		RBT* getLeft() { return _left; }
		RBT* getRight() { return _right; }
		list<Run>* getRun() { return _runlist; }
		void setLeft(RBT* left) { _left = left; }
		void setRight(RBT* right) { _right = right; }
		void setRun(Run r) {
			if (NULL == _runlist) { _runlist = new list<Run>; }
			_runlist->push_back(r);
		}
};

/* for constructing a Run-Based Trie */
class RunPair {
	private:
		unsigned _startBit;
		Run _run;
	public:
		RunPair() { }
		RunPair(unsigned startBit, Run run) {
			_startBit = startBit;
			_run = run;
		}
		~RunPair() { /* printf("call a RunPair deconstructor.\n"); */ }
		unsigned getStartBit() { return _startBit; }
		Run getRun() { return _run; }
};

void traverseAndMakeRBTNode(RBT*, Run);
list<RunPair>* cutOutRun(Rule);
void createTheRBTRootNodes(vector<RBT>*, unsigned);
void makeRunBasedTrie(list<Rule>*&, vector<RBT> *);
void postTraverse(RBT*);

#endif
