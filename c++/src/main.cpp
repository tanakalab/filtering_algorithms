#include <main.hpp>

int main(int argc, char* argv[])
{
	/* check arguments */
	if (argc != 3) {
		printf("Usage: main <rule list> <pseudo packets>\n");
		return 1;
	}

	/* open and read rulelist */
	list<Rule> *rulelist;
	rulelist = new list<Rule>;
	try {
		readRulelist(argv[1],rulelist);
	} catch (string error_message) {
		cout << error_message; return 1;
	}

	/* open and read packets */
	list<string> *packets;
	packets = new list<string>;
	try {
		readPackets(argv[2],packets);
	} catch (string error_message) {
		cout << error_message; return 1;
	}

	/*
	list<string>::iterator packetIt = packets->begin();
	list<string>::iterator packetItEnd = packets->end();
	while (packetIt != packetItEnd) {
		cout << *packetIt << endl;
		++packetIt;
	}
	*/


	/* delete dynamicaly allocated memories */
	delete rulelist;
	delete packets;

	return 0;
}
