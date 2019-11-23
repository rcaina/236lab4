#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctype.h>
#include <map>
#include "Interpreter.h"

using namespace std;

Interpreter::Interpreter(parser& datalogProgram){

	this->dL = datalogProgram;
	
	for(predicate scheme: dL.getSchemes()){
		
		Scheme header;
		for(string list: scheme.getAttributes()){
			header.push_back(list);
		}

		Relation r = Relation(scheme.getName(), header);
		db.insert({r.getName(), r});
	}
	
	for(predicate fact: dL.getFacts()){
	
		Tuple t;
		for(string attribute: fact.getAttributes()){
		
			t.push_back(attribute);
		}
		db.at(fact.getName()).addTuple(t);
	}
//	for( auto [key, val] : db){
//		cout << key << ':' << val.toString() << endl ;
//	}

}

void Interpreter::evalQueries(){
	
	vector <string> items;
	for(predicate q: dL.getQueries()){
		cout << q.to_string() << '?';
//new relation
		items = q.getAttributes();
		
		map<string, int> variables;
		Scheme header;	
//loop over each param in query
//
 		Relation result = db[q.getName()];
		vector<int> columns;

		for(unsigned i = 0; i < items.size(); i++){

		//check if param is string or ID
			if(items.at(i).at(0) == '\''){
			
				result = result.select1(i , items.at(i));	
			}
			else{
				if(variables.find(items.at(i)) != variables.end()){
					result = result.select2(variables[items.at(i)], i);
				}
				else{
					variables.insert({items.at(i), i});
					header.push_back(items.at(i));
					columns.push_back(i);
				}
			}
//-flowchart
		}
		int relationSize = result.getSize();
		
		if(relationSize > 0){
	
			cout << " Yes(" << relationSize << ")\n";
		}
		else{

			cout << " No\n";
		}

		result = result.project(columns);
		result = result.rename(header);

		cout << result.toString();


	}
}
