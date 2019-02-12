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


void info(const College &c){
	int courseCounter = 0;
	int studentCounter = 0;
	GradeStats g = GetGradeDistribution(c);
	int dfw = 0;
	int n = 0;
	for(const Dept &d: c.Depts){
		courseCounter += d.Courses.size();
		for(const Course &s: d.Courses){
			studentCounter += s.getNumStudents();
		}
	}
	
	cout << "# of courses taught: " << courseCounter << endl;
	cout << "# of students taught: " << studentCounter << endl;
	cout << "grade distribution (A-F): " << g.PercentA << "%, " <<
		g.PercentB << "%, " << g.PercentC << "%, " << g.PercentD 
		<< "%, " << g.PercentF << "% " << endl;
	cout << "DFW rate: " <<  GetDFWRate(c, dfw, n) << "%" << endl << endl;
	
	return;
}


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


auto findDept(const College &c){
	string line = "";
	getline(cin, line);
	
	if(line.compare("all") == 0){
		return c.Depts;
	}
	
	auto r = find_if(line.begin(), line.end(), 
					[](string s){
						//////////////ended here!!!
					});
}


void summary(const College &c){
	cout << "dept name, or all? ";
	return;
}



void search(const College &c){
	
	return;
}



void unknown(const College &c){
	
	return;
}



void dfw(const College &c){
	
	return;
}



void letterA(const College &c){
	
	return;
}



void queries(const College &c){
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
	
	info(c);
	
	queries(c);
	
	
	
	return 0;
}