#pragma once
#ifndef RELATION_H
#define RELATION_H

#include <set>
#include "Tuple.h"
#include "Scheme.h"

using namespace std;

class Relation {

	public:
		Relation(){}
		Relation(string name, Scheme scheme);
		Relation select1(int column, string val);
		Relation select2(int column1, int column2);
		Relation project(vector <int> keepColumns);
		Relation rename(Scheme header);
		
		string getName();
		void setScheme(Scheme scheme);
		Scheme getScheme();
		
		string toString();
		void addTuple(Tuple tup);
		int getSize();
		int getColumn(string attribute);

	private:
		string name;
		Scheme scheme;
		set <Tuple> tuples;

};
#endif


