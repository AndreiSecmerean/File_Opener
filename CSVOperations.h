#include <iostream>
#include <string>
#include <vector>
#include "FileOpener.h"

#pragma once

using namespace std;

class CSVOperations {
private:
	string newTag;
	string newAddress;
public:
	static bool fileExists(const string& filename);
	bool createCSVFile(const string& filename);
	void addressCreator(FileOpener fileCSV);
	void editTag(FileOpener fileCSV, const string& filename);
	void editAddress(FileOpener fileCSV, const string& filename);
	void deleteAddress(FileOpener fileCSV, const string& filename);
	void orderTags(FileOpener fileCSV, const string& filename);
};