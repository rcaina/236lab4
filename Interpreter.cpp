#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <map>
#include "Interpreter.h"

using namespace std;

Interpreter::Interpreter(parser& datalogProgram) {

	this->dL = datalogProgram;

	for (predicate scheme : dL.getSchemes()) {

		Scheme header;
		for (string list : scheme.getAttributes()) {
			header.push_back(list);
		}

		Relation r = Relation(scheme.getName(), header);
		db.insert({ r.getName(), r });
	}

	for (predicate fact : dL.getFacts()) {

		Tuple t;
		for (string attribute : fact.getAttributes()) {

			t.push_back(attribute);
		}
		db.at(fact.getName()).addTuple(t);
	}

	evalAllRules();

}

void Interpreter::evalQueries() {

	cout << "Query Evaluation\n";
	vector <string> items;
	Relation result;
	for (predicate q : dL.getQueries()) {

		cout << q.to_string() << '?';
		result = evaluatePredicate(q);

		int relationSize = result.getSize();

		if (relationSize > 0) {

			cout << " Yes(" << relationSize << ")\n";
			//if it has variable then print, else don't
		}
		else {

			cout << " No\n";
		}

		cout << result.toString();


	}
}

Relation Interpreter::evaluatePredicate(predicate pred) {

	vector <string> items;

	//new relation
	items = pred.getAttributes();

	map<string, int> variables;
	Scheme header;
	//loop over each param in query
	//
	Relation result = db[pred.getName()];
	vector<int> columns;

	for (unsigned i = 0; i < items.size(); i++) {

		//check if param is string or ID
		if (items.at(i).at(0) == '\'') {

			result = result.select1(i, items.at(i));
		}
		else {
			if (variables.find(items.at(i)) != variables.end()) {
				result = result.select2(variables[items.at(i)], i);
			}
			else {
				variables.insert({ items.at(i), i });
				header.push_back(items.at(i));
				columns.push_back(i);
			}
		}
		//-flowchart
	}

	result = result.project(columns);
	result = result.rename(header);

	return result;
}

// will call eval predicate function, this function is called by evaluateAllrules function
bool Interpreter::evalSingleRule(rulez rule1) {

	vector <Relation> newRelations;
	vector <predicate> rulepreds = rule1.getPredicates();

	for (unsigned i = 0; i < rulepreds.size(); i++) {

		newRelations.push_back(evaluatePredicate(rulepreds[i]));
	}

	Relation rhs = newRelations[0];

	for (unsigned i = 1; i < newRelations.size(); i++) {

		rhs = rhs.joinRelation(newRelations[i]);
	}

	predicate headpred = rule1.getHeadPred();

	vector<int> keepColumns;
	vector<string> attributes = headpred.getAttributes();
	vector<string> rhsAttr = rhs.getAttributes();
	for (unsigned int i = 0; i < attributes.size(); i++) {

		for (unsigned int j = 0; j < rhsAttr.size(); j++) {

			if (attributes[i] == rhsAttr[j]) {

				keepColumns.push_back(rhs.getColumn(rhsAttr[j]));
			}
		}
	}

	rhs = rhs.project(keepColumns);

	rhs.setName(headpred.getName());
	string name = rhs.getName();

	rhs.rename(db[name].getScheme());

	int currentsize = db[name].getSize();

	db[name].unionRelation(rhs);

	if (currentsize == db[name].getSize()) {

		return false;
	}

	return true;
}

void Interpreter::evalAllRules() {

	int count = 0;

	cout << "Rule Evaluation\n";
	while (!done) {

		done = true;

		for (rulez rule : dL.getRules()) {

			cout << rule.to_String() << ".\n";
			if (evalSingleRule(rule)) {

				done = false;

			}
		}

		count++;
	}

	cout << "\nSchemes populated after " << count << " passes through the Rules.\n\n";
}