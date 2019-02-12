#include <string>
#include <sstream>
#include <vector>
#include<iterator>
#include <regex>
#include <algorithm>
#include <iostream>
#include "gradeutil.h"
#include <fstream>
#include <iomanip>

using namespace std;


string parseHeader(string line, string &season, string &year){
	string collegeName;
	stringstream ss(line);
	getline(ss, collegeName, ',');
	getline(ss, season, ',');
	getline(ss, year, ',');
	return collegeName;
}


void parseDept(Course &s, College &c){
	
	auto r = find_if(c.Depts.begin(), c.Depts.end(),
					 [&](const Dept d){
						 if(d.Name.compare(s.Dept) == 0){
							 return true;
						 }
						 else{
							 return false;
						 }
					 });
	
	if(r == c.Depts.end()){
		Dept d(s.Dept);
		d.Courses.push_back(s);
		c.Depts.push_back(d);
	}
	else{
		r->Courses.push_back(s);
	}
}



void summary(){
	
	return;
}



void search(){
	
	return;
}



void unknown(){
	
	return;
}



void dfw(){
	
	return;
}



void letterA(){
	
	return;
}



void queries(College &c){
	vector<string> commands{"summary", "search", "unknown", "dfw", "letterA"};
	string command = "";
	while (command.compare("#") != 0){
		cout << "Enter a command> ";
		getline(cin, command);
		if(command.compare("#") == 0){
			exit(0);
		}
		auto r = find_if(commands.begin(), commands.end(),
			   [&](string s){
				  if(command.compare(s) == 0){
					  return true;
				  }
				   else{
					   return false;
				   }
			   });
		if(r == commands.end()){
			cout << "**unknown command" << endl;
		}
		else{
			if(r->compare("search") == 0){
				
			}
			else if(r->compare("summary") == 0){
				
			}
			else if(r->compare("unknown") == 0){
				
			}
			else if(r->compare("dfw") == 0){
				
			}
			else if(r->compare("letterA") == 0){
				
			}
		}
	}
	
	return;
}


int main(){
	cout <<fixed;
	cout <<setprecision(2);
	
	string fileName;
	getline(cin, fileName);
	ifstream inData;
	inData.open(fileName);
	
	if(!inData.good()){
		cout << "File is bad/Couldn't open it";
		exit(-1);
	}
	
	string line, season, college, year;
	
	getline(inData, line);
	college = parseHeader(line, season, year);
	College c(college);
	getline(inData, line);
	
	cout << "** College of " << college << ", " << season << " " << year << " **" << endl;
	
	while(getline(inData, line)){
		Course n = ParseCourse(line);
		parseDept(n, c);
	}
	
	inData.close();
	
	queries(c);
	
	
	
	return 0;
}