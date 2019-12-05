#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include "Lexer.h"
#include "Tokens.h"
#include "parser.h"
#include "Interpreter.h"

using namespace std;

/*Tuple createTuple(vector<string> tuples) {

	Tuple t;

	for (unsigned i = 0; i < tuples.size(); i++) {

		t.push_back(tuples.at(i));
	}

	return t;

}

bool testProject() {

	Scheme header;

	header.push_back("S");
	header.push_back("N");
	header.push_back("A");
	header.push_back("P");

	Relation r = Relation("snap", header);

	r.addTuple(createTuple({ "1","B","C","D" }));
	r.addTuple(createTuple({ "2","E","F","G" }));
	r.addTuple(createTuple({ "3","H","I","J" }));

	Scheme head;

	head.push_back("C");
	head.push_back("S");
	head.push_back("G");

	Relation l = Relation("csg", head);

	l.addTuple(createTuple({ "A","1","K" }));
	l.addTuple(createTuple({ "A","2","L" }));
	l.addTuple(createTuple({ "A","3","M" }));
	l.addTuple(createTuple({ "Z","1","N" }));
	l.addTuple(createTuple({ "Z","2","O" }));

	Relation joined;
	joined = l.joinRelation(r);

	cout << joined.toString() << "\n\n\n\n";

	Scheme H;

	H.push_back("A");
	H.push_back("B");

	Relation rel = Relation("snap", H);

	rel.addTuple(createTuple({ "1","2" }));
	rel.addTuple(createTuple({ "3","4" }));
	rel.addTuple(createTuple({ "3","4" }));
	rel.addTuple(createTuple({ "5","6" }));
	rel.addTuple(createTuple({ "7","8" }));
	rel.addTuple(createTuple({ "5","6" }));

	Scheme h;

	h.push_back("A");
	h.push_back("B");

	Relation rela = Relation("snop", h);

	rela.addTuple(createTuple({ "4","5" }));
	rela.addTuple(createTuple({ "8","9" }));
	rela.addTuple(createTuple({ "1","2" }));
	rela.addTuple(createTuple({ "2","3" }));
	rela.addTuple(createTuple({ "6","7" }));
	rela.addTuple(createTuple({ "5","6" }));

	rel.unionRelation(rela);
	cout << endl;
	cout << rel.toString();
	return true;
}
*/


int main(int argc, char* argv[]) {

	Lexer activate(argv[1]);

	parser parsing;
	parsing.setvector(activate.getVector());
	parsing.startParser();



	Interpreter interpreter = Interpreter(parsing);
	interpreter.evalQueries();
	//testProject();

	return 0;
}
