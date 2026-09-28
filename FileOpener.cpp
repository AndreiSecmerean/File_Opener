#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "FileOpener.h"	 

using namespace std;

FileOpener::FileOpener(const string& filenameame) { //constructor
	dataFromCSV = readCSV(filenameame);
}

vector<vector<string>> FileOpener::readCSV(const string& filename) {
	/*DOCU:
	* This function purpuose is to read the file at the specified address in paranthasies line by line and separating the tags-address combo and
	* address in 2 different vectors in order to be proccesed in the scope of opening an instance of File Explorer.
	*
	* If a certain value  is desired it can be accessed as such:
	* wantedAddressBasedOnVector = vector_TagAddress[n][0/1];
	*
	* PARAMS:
	*	const string& filename -> name of the csv file that the app uses, in this case "Tag-Address.csv"
	*
	* RETURNS:
	*	vector<vector<string>> data	-> 2d vector containing all of the tag-address combos: <vector_Tag<vector_Address>>
	*								-> tagAdress[n][0] = "tag_n"
	*								-> tagAdress[n][1] = "adress"
	*/

	vector<vector<string>> data;
	ifstream file(filename);


	//----Checking to see if file opened successfully----
	if (!file.is_open()) {
		cerr << "Failed to open file: " << filename << endl;
		return data;
	}

	string line;
	while (getline(file, line))
	{
		vector<string> row;
		stringstream ss(line);
		string cell;

		while (getline(ss, cell, ',')) {
			row.push_back(cell);
		}

		data.push_back(row);
	}

	file.close();
	return data;
};

vector<string> FileOpener::readTags() {
	/*DOCU:
	* This functions purpuose is to read from the keyboard tags separated by "," and return them as a vector of strings
	*
	*
	* RETURNS:
	*		vector<string> separatedTags -> contains all of the tags separated by ","
	*/
	fflush(stdin);
	string tagsFromKeyboard;
	string tags;
	vector<string> separatedTags;

	cout << "Please input strings separated by a coma" << endl;
	cin >> tagsFromKeyboard;


	stringstream tagStream(tagsFromKeyboard);
	while (getline(tagStream, tags, ','))
	{
		separatedTags.push_back(tags);
	}

	cout << "read tags: \n";
	for (int i = 0; i < separatedTags.size(); i++) {
		cout << separatedTags[i] << endl;
	}



	return separatedTags;
};

void FileOpener::printCSV() {
	/*DOCU:
	* This function is used to print the data from the csv separatad by space
	*/

	cout << "Displaying posible directories\n\n" << "tags \taddress" << endl;
	for (const auto& row : this->dataFromCSV) {
		for (const auto& cell : row) {
			cout << cell << "\t";
		}
		cout << "\n";
	}

};

void FileOpener::openExplorer() {
	/*DOCU:
	* This function opens an instance of file explorer based on the address saved before calling this function
	*/
	string str = "explorer " + this->address;

	const char* command = str.c_str();
	system(command);
	cout << "\nOpened explorer at address: " << this->address;
	this->address.clear();

};

void FileOpener::extractAdress() {
	/*DOCU:
	* This whole function is used mainly to check for equality between the tags got from the readTags() function and the tags found
	* founueed at the address specified in readCSV(). After this it appends it to a string in order to be parsed to address creator
	*/

	for (int counter_separatedTags = 0; counter_separatedTags < this->separatedTags.size(); counter_separatedTags++) {
		//separated tags is a vector<string> containing the read tags from readTags()

		for (int counter_dataCSV = 0; counter_dataCSV < this->dataFromCSV.size(); counter_dataCSV++) {
			//separated tags is a vector<vector<string>> containing the read tags and coresponding addressed from readCSV()

			if (this->separatedTags[counter_separatedTags] == this->dataFromCSV[counter_dataCSV][0]) {
				string extractedData = this->dataFromCSV[counter_dataCSV][1];
				this->address.append(extractedData);
				//this if block compares each separated tag with all the tags in dataFromCSV one by one, 
				//when a tag is found, the coresponding address is appended                 
			}
		}
	}
}

bool FileOpener::tagExists(string tag, bool print) {
	/*DOCU:
	* This function searches the csv in order to check if a tag exists, this can be used when adding new tags or
	* not to waste time when doing other operation in the file opener
	*
	* params:
	*		string tag	->	tag to be evaluated
	*		bool print	->	specifies wether or not to print the tag-address combo found in the csv
	*
	* returns:
	*		true	 ->	 if the tag already exists
	*		false	 ->	 if the tag doesn't exist
	*/
	bool tagExists = false;
	for (int i = 0; i < this->dataFromCSV.size(); i++) {
		if (tag == this->dataFromCSV[i][0]) {
			tagExists = true;
			if (print) {
				cout << "Tag - Address combo found is: \n" << this->dataFromCSV[i][0] << ",\t" << this->dataFromCSV[i][1];
			}
			break;
		}
	}
	return tagExists;
};

bool FileOpener::addressExists(string address) {
	/*DOCU:
	* This function searches the csv in order to check if a address exists, this can be used when adding new address or
	* not to waste time when doing other operation in the file opener
	*
	* params:
	*		string tag	->	tag to be evaluated
	*
	* returns:
	*		true  -> if the tag already exists
	*		false -> if the tag doesn't exist
	*/
	bool addressExists = false;
	for (int i = 0; i < this->dataFromCSV.size(); i++) {
		if (address == this->dataFromCSV[i][1]) {
			addressExists = true;
			break;
		}
	}
	return addressExists;
}

//getters
vector<vector<string>> FileOpener::get_dataFromCSV() {
	return this->dataFromCSV;
}

string FileOpener::getAddress() {
	return this->address;
}

//setters
void FileOpener::setNewDataFromCSV(const string& filename) {
	this->dataFromCSV = readCSV(filename);
}

void FileOpener::setSeparatedTags(const vector<string> separatedTags) {
	this->separatedTags.clear();
	//cout <<"current nr. tags read" << this->separatedTags.size();
	this->separatedTags = separatedTags;
	//cout << "new nr. tags read" << this->separatedTags.size();
}