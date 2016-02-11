/* rbt.hpp */

#ifndef __CLASIFICATION_RBT_HPP__
#define __CLASIFICATION_RBT_HPP__

#ifndef __CLASIFICATION_OPENFILE_HPP__
#include <openfile.hpp>
#endif

#include <vector>
#include <cmath>

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
		RBT* _left;
		RBT* _right;
		list<Run>* _runlist;
	public:
		RBT() { }
		RBT(char nodeBit, unsigned trieNumber, string nodeString) {
			_nodeBit = nodeBit;
			_nodeString = nodeString;
			_trieNumber = trieNumber;
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

/* Match Run Set Trie */
class MR {
	private:
		static long unsigned _number_of_node_of_mr;
		char _nodeBit;
		string _nodeString;
		string _mrString;       /* for pruning the Decision Tree */
		unsigned _dIndex;       /* an index for a Decision Tree Search */
		unsigned _trieNumber;
		unsigned _weight;
		MR* _parent;
		MR* _left;
		MR* _right;
		list<Run>* _runlist;
		string _safeNodeString; /* for pruning the Decision Tree */
		MR* _safeLeft;          /* for pruning the Decision Tree */
		MR* _safeRight;         /* for pruning the Decision Tree */
		list<string>* _mrlist;  /* for pruning the Decision Tree */
	public:
		MR() { }
		MR(char nodeBit, unsigned trieNumber, string nodeString, MR* p) {
			_nodeBit = nodeBit;
			_nodeString = nodeString;
			_mrString = nodeString;
			_dIndex = 0;
			_trieNumber = trieNumber;
			_weight = 0;
			_parent = p;
			_left = NULL;
			_right = NULL;
			_runlist = NULL;
			_mrlist = NULL;
			_safeNodeString = "";
			_safeLeft = NULL;
			_safeRight = NULL;
		}
		~MR() { /* printf("call a MR deconstructor.\n"); */ }
		static void showNumberOfNodeOfMRT() { cout << _number_of_node_of_mr << endl; }
		char getNodeBit() { return _nodeBit; }
		string getNodeString() { return _nodeString; }
		string getMRString() { return _mrString; }
		unsigned getTrieNumber() { return _trieNumber; }
		unsigned getWeight() { return _weight; }
		MR* getParent() { return _parent; }
		MR* getLeft() { return _left; }
		MR* getRight() { return _right; }
		list<Run>* getRun() { return _runlist; }
		void changeMRString(string s) { _mrString = s; }
		void setWeight(unsigned w) { _weight = w; }
		void setLeft(MR* left) { _left = left; }
		void setRight(MR* right) { _right = right; }
		void setRun(Run r) {
			if (NULL == _runlist) { _runlist = new list<Run>; }
			_runlist->push_back(r);
		}
		void changeNodeString(string s) { _nodeString = s; }
		void subtractWeight(unsigned m) { _weight -= m; }
};

void walkToRoot(MR*);
void MRTWeightTraverse(MR*);
void allMRTWeightTraverse(vector<MR>*);
void traverseAndMakeMRTNode(RBT *, MR *, unsigned&, unsigned&);
void copyRBTtoMRT(vector<RBT>*&, vector<MR>*);
void createTheMRTRootNodes(vector<MR>*, unsigned);
void makeMatchRunSetTrie(vector<RBT>*&, vector<MR>*);
void traverseAndMakeRBTNode(RBT*, Run);
list<RunPair>* cutOutRun(Rule);
void createTheRBTRootNodes(vector<RBT>*, unsigned);
void makeRunBasedTrie(list<Rule>*&, vector<RBT> *);
void postTraverse(RBT*);
void postTraverse(MR*);

#endif
