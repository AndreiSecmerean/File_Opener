#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include "Custom_Excepions.h"
#include "Logger.h"

using namespace std;


class FileOpener {
private:
	vector<vector<string>> dataFromCSV;
	vector<string> tagsInCSV;
	vector<string> separatedTags;
	string address = "";

public:
	FileOpener(const string& filenameame) { //constructor
		dataFromCSV = readCSV(filenameame);
	}


	vector<vector<string>> readCSV(const string& filename) {
		/*DOCU:
		* This function purpuose is to read the file at the specified address in paranthasies line by line and separating the tags-address combo and
		* address in 2 different vectors in order to be proccesed in the scope of opening an instance of File Explorer.
		*
		* These 2 vectors are formated as such:
		* tagAdress[n] = "tag_n, adress"
		* adress[n] = "address"
		*
		* The function will retun a vector of this format: vector_TagAddress<vector_Address>
		*
		* If a certain value  is desired it can be accessed as such:
		* wantedAddressBasedOnVector = vector_TagAddress[n][n];
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
	}

	vector<string> readTags() {
		/*This function purpuose is to read from the keyboard tags separated by " " and return them as a vector of strings that is then parsed to other functions
		* as a vector.
		*
		* the vector looks like this
		* vector[0] = tag_1
		* vector[1] = tag_2
		* ...
		* vector[n] = tag_n
		*/
		fflush(stdin);
		string tagsFromKeyboard;
		string tags;
		vector<string> separatedTags;

		cout << "Please input strings separated by a coma" << endl;
		//cin >> tagsFromKeyboard; DO NOT USE CIN, IT CONSIDERS WHITE-SPACE AS A TERMINATING CHARACTER
		cin >> tagsFromKeyboard;


		stringstream tagStream(tagsFromKeyboard);
		while (getline(tagStream, tags,','))
		{
			separatedTags.push_back(tags);
		}

		cout << "read tags: \n";
		for (int i = 0; i < separatedTags.size(); i++) {
		    cout << separatedTags[i] << endl;
		}
		
		

		return separatedTags;
	}


	void printCSV() {
		/*This function is used to print the data from the csv separatad by space,*/

		cout << "Displaying posible directories\n\n" << "tags \taddress" << endl;
		for (const auto& row : this->dataFromCSV) {
			for (const auto& cell : row) {
				cout << cell << "\t";
			}
			 cout<<"\n";
		}

	}

	void openExplorer() {
		string str = "explorer " + this->address;
		//cout << dataFromCSV[0][1];

		const char* command = str.c_str();
		system(command);
		cout << "\nOpened explorer at address: " << this->address;
		this->address.clear();

	}

	void extractAdress() { 
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

	bool tagExists(string tag, bool print) {
		/*DOCU:
		* This function searches the csv in order to check if a tag exists, this can be used when adding new tags or
		* not to waste time when doing other operation in the file opener
		*
		* params:  string tag   -> tag to be evaluated
		*		   bool print	-> specifies wether or not to print the tag-address combo found in the csv
		*
		* returns: true  -> if the tag already exists
		*          false -> if the tag doesn't exist
		*/
		bool tagExists = false;
		for (int i = 0; i < size(this->dataFromCSV); i++) {
			if (tag == this->dataFromCSV[i][0]) {
				tagExists = true;
				if (print) {
					cout << "Tag - Address combo found is: \n" << this->dataFromCSV[i][0] << ",\t" << this->dataFromCSV[i][1];
				}
				break;
			}
		}
		return tagExists;
	}

	bool addressExists(string address) {
		/*DOCU:
		* This function searches the csv in order to check if a address exists, this can be used when adding new address or
		* not to waste time when doing other operation in the file opener
		*
		* params:  address   -> tag to be evaluated
		*
		* returns: true  -> if the tag already exists
		*          false -> if the tag doesn't exist
		*/
		bool addressExists = false;
		for (int i = 0; i < size(this->dataFromCSV); i++) {
			if (address == this->dataFromCSV[i][1]) {
				addressExists = true;
				break;
			}
		}
		return addressExists;
	}

	//getters
	vector<vector<string>> get_dataFromCSV() {
		return this->dataFromCSV;
	}

	string getAddress() {
		return this->address;
	}

	//setters
	void setNewDataFromCSV(const string& filename) {
		this->dataFromCSV = readCSV(filename);
	}

	void setSeparatedTags(const vector<string> separatedTags) {
		this->separatedTags.clear();
		//cout <<"current nr. tags read" << this->separatedTags.size();
		this->separatedTags = separatedTags;
		//cout << "new nr. tags read" << this->separatedTags.size();
	}

};

class CSVOperations {
private:
	string newTag;
	string newAddress;
public:
	bool fileExists(const string& filename) {
		ifstream file(filename);
		return file.good();
	}

	void addressCreator(FileOpener fileCSV) {
		/*DOCU:
		* This function is used to create a tag-address combination and write it to the csv. It reads from the keyboard in sequence the new tag and address and checks if they already
		* exist in db.
		*
		* params: FileOpener fileCSV  -> this field is required in order to check for presence of the new tag and address
		*
		* returns: void
		*/
		bool tagAdded = false;
		fstream csv;
		int i = 0;

		do {

			try {
				cout << "\nInput a a new tag: ";
				cin >> this->newTag;
				if (fileCSV.tagExists(this->newTag, false)) {
					throw ValueAlreadyExists("Tag already exists in database");
				}

				cout << "\nInput a new addres for tag " << this->newTag<<": ";
				cin >> this->newAddress;
				if (fileCSV.addressExists(this->newAddress)) {
					throw ValueAlreadyExists("Address already exists in database");
				}

			}
			catch (ValueAlreadyExists e) {
				cout << e.what();
			}

			tagAdded = true;
		} while (!tagAdded);

		csv.open("Tag-Address.csv", ios::out | ios::app);
		csv << this->newTag << ", " << this->newAddress << "\n";
		csv.close();
		cout << "\nSuccessfully added new tag " << this->newTag << " \nand it's coresponding address " << this->newAddress << endl;
	}

	bool deleteAddress(FileOpener fileCSV, const string& filename)
	{
		/*DOCU:
		* This function is used to delete a tag-address combination from the csv. It reads from the keyboard in sequence the tag and checks if it
		* exists in db.
		*
		* params: FileOpener fileCSV  -> this field is required in order to check for presence of the tag
		*
		* returns: bool isDeleted ->   true  if tag was deleted
									   false if tag was not deleted / found
		*/
		bool isDeleted = true;
		string tagToDelete;
		string NewTag_Address = "NewTag-Address.csv";
		vector<vector<string>> dataFromCSV;
		fstream newCSV;

		try {
			cout << "\nPlease input tag: ";
			cin >> tagToDelete;
			if (!fileExists(filename)) {
				throw TagFileNotFound("File not found");
			}

			dataFromCSV = fileCSV.get_dataFromCSV();
			if (fileCSV.tagExists(tagToDelete, false) == false) {
				string error = "Tag " + tagToDelete + " does not exist in csv!";
				throw TagNotFound("Tag does not exist in csv!");
			}

			newCSV.open(NewTag_Address.c_str(), ios::out | ios::app);
			for (int csvCounter = 0; csvCounter < dataFromCSV.size(); csvCounter++) {
				if (dataFromCSV[csvCounter][0] == tagToDelete) {
					continue;
				}
				else
				{
					newCSV << dataFromCSV[csvCounter][0] << ", " << dataFromCSV[csvCounter][1] << endl;
				}
			}

			newCSV.close();
			remove(filename.c_str());
			rename(NewTag_Address.c_str(), filename.c_str());
			cout << "\nRemoved tag: " << tagToDelete << " from tag-address list";

		}
		catch (TagFileNotFound e) {
			cout << e.what();
		}
		catch (TagNotFound e) {
			cout << e.what();
		}

		
		return isDeleted;
	}
};


void main()
{


	cout << "Started shell file opener\n" << endl;
	try {
		int menu;
		string tags;
		string tagToFind;
		char exitOption;
		bool exitLoop = false;
		bool exitMain = false;
		Logger logger("LOG.txt", true);
		CSVOperations csv;

		if (!csv.fileExists("Tag-Address.csv")) {
			throw TagFileNotFound("File with inital tag locations is not present, check to see if it was deleted");
		}


		FileOpener dataFromCSV("Tag-Address.csv");
		logger.log(INFO, "created dataFromCSV");

		do {
			cout << "\n-----MENU-----\n"
				<< "1.Open File Explorer\n"
				<< "2.Show available tags and addresses\n"
				<< "3.Show address based on tag\n"
				<< "4.Create new tag - address\n"
				<< "5.Delete tag - address\n"
				<< "0.exit"
				<< endl;

			cout << "Your choice: ";
			cin >> menu;

			switch (menu)
			{
			case 0: //exit
				cout << "\nAre you sure you want to quit?\n [Y/N]: ";
					cin >> exitOption;
					if (exitOption == 'y' || exitOption == 'Y') {
						exitLoop = true;
						exit(1);
					}
					else if (exitOption == 'n' || exitOption == 'N') {
						exitLoop = false;
						cout << exitLoop;
						break;
					}
					else cout << "selection invalid, chose again [Y/N]: ";
				 
				exitLoop = true;
				break;

			case 1: //Open File 
				dataFromCSV.setSeparatedTags(dataFromCSV.readTags());
				dataFromCSV.extractAdress();
				dataFromCSV.openExplorer();
				break;

			case 2: //Show available tags and addresses
				dataFromCSV.printCSV();
				break;

			case 3: //Show address based on tag
				cout << "Input tag you want to search ";
				cin >> tagToFind;
				dataFromCSV.tagExists(tagToFind, true);
				break;

			case 4: //Create new tag - address
				csv.addressCreator(dataFromCSV);
				dataFromCSV.setNewDataFromCSV("Tag-Address.csv");
				break;

			case 5: //Delete tag - address
				csv.deleteAddress(dataFromCSV, "Tag-Address.csv");
				dataFromCSV.setNewDataFromCSV("Tag-Address.csv");
			default:
				break;
			}
		} while (!exitLoop);
	}
	catch (TagFileNotFound e) {
		cout << e.what();
	}
}