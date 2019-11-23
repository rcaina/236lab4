#pragma once
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <iostream>
#include <vector>
#include "Database.h"
#include "parser.h"
#include "Relation.h"

using namespace std;

//Process schemes into relations

class Interpreter {

	public:
		Interpreter(parser& datalogProgram);

		//Set database should : turn each scheme into a relation and put it in the database
		//turn each fact into a tuple and put it in a relation (which is in the database)
		
		//sepearte function to evalaute all queries... calls evaluate predicate and prints out final results
		void evalQueries();
		Relation evaluatePredicate(predicate pred); // (will need this for lab 4)

	private:

		parser dL;
		Database db;
};
#endif


