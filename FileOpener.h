#include <iostream>
#include <vector>
#pragma once



using namespace std;

class FileOpener {
private:
	vector<vector<string>> dataFromCSV;
	vector<string> tagsInCSV;
	vector<string> separatedTags;
	string address = "";

public:
	FileOpener(const string& filenameame);
	vector<vector<string>> readCSV(const string& filename);
	vector<string> readTags();
	void printCSV();
	void openExplorer();
	void extractAdress();
	bool tagExists(string tag, bool print);
	bool addressExists(string address);
	vector<vector<string>> get_dataFromCSV();
	string getAddress();	
	void setNewDataFromCSV(const string& filename);
	void setSeparatedTags(const vector<string> separatedTags);
};