#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include "Custom_Excepions.h"
#include "Logger.h"
#include <conio.h>

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
	}

	vector<string> readTags() {
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
		/*DOCU:
		* This function is used to print the data from the csv separatad by space
		*/

		cout << "Displaying posible directories\n\n" << "tags \taddress" << endl;
		for (const auto& row : this->dataFromCSV) {
			for (const auto& cell : row) {
				cout << cell << "\t";
			}
			 cout<<"\n";
		}

	}

	void openExplorer() {
		/*DOCU:
		* This function opens an instance of file explorer based on the address saved before calling this function
		*/
		string str = "explorer " + this->address;

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
		* params:  
		*		string tag	->	tag to be evaluated
		*		bool print	->	specifies wether or not to print the tag-address combo found in the csv
		*
		* returns: 
		*		true	 ->	 if the tag already exists
		*		false	 ->	 if the tag doesn't exist
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
		* params:  
		*		string tag	->	tag to be evaluated
		*
		* returns: 
		*		true  -> if the tag already exists
		*		false -> if the tag doesn't exist
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
		/*DOCU:
		* Checks if there is a file in the app directory with the specified filename
		* 
		* PARAMS:
		*		const string& filename -> file to be checked
		* 
		* RETURNS:
		*		true -> file exists
		*		false -> file doesn't exist
		*/
		ifstream file(filename);
		return file.good();
	}

	void createCSVFile(const string& filename) {
		if (!fileExists(filename)) {

		}
	}

	void addressCreator(FileOpener fileCSV) {
		/*DOCU:
		* This function is used to create a tag-address combination and write it to the csv. It reads from the keyboard in sequence the new tag and address and checks if they already
		* exist in db.
		*
		* params: 
		*		FileOpener fileCSV  -> this field is required in order to check for presence of the new tag and address
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

	void editTag(FileOpener fileCSV, const string& filename) {
		/*DOCU:
		* This function opens the csv, reads it contents and saves the tag-address combo to a new auxiliary file. This copying continues as normal untill the algorithm
		* encounters the tag that we want to edit. When it does find the tag to be edited the program replaces the tag with the new tag. In the end it renames the auxiliary
		* file to the original file, but only after it deletes the original
		* 
		* PARAMS: 
		* 
		* FileOpener fileCSV -> required to check the tag in the csv
		* const string& filename -> required to check the presence of the file
		* 
		* RETURNS:
		* 
		* void
		*/
		string tagToEdit, edditedTag;
		vector<vector<string>> dataFromCSV;
		fstream newCSV;
		string NewTag_Address = "NewTag-Address.csv";


		try {
			if (!fileExists(filename)) {
				throw TagFileNotFound("File not found");
			}

			cout << "\nPlease input the tag that you want to edit: ";
			cin >> tagToEdit;
			cout << "\nPlease input new name for tag {" << tagToEdit << "}: ";
			cin >> edditedTag;


			dataFromCSV = fileCSV.get_dataFromCSV();
			if (fileCSV.tagExists(tagToEdit, false) == false) {
				string error = "Tag " + tagToEdit + " does not exist in csv!";
				throw TagNotFound("Tag does not exist in csv!");
			}

			newCSV.open(NewTag_Address.c_str(), ios::out | ios::app);
			for (int csvCounter = 0; csvCounter < dataFromCSV.size(); csvCounter++) {
				if (dataFromCSV[csvCounter][0] == tagToEdit) {
					dataFromCSV[csvCounter][0] = edditedTag;
					newCSV << dataFromCSV[csvCounter][0] << ", " << dataFromCSV[csvCounter][1] << endl;
				}
				else
				{
					newCSV << dataFromCSV[csvCounter][0] << ", " << dataFromCSV[csvCounter][1] << endl;
				}
			}

			newCSV.close();
			remove(filename.c_str());
			rename(NewTag_Address.c_str(), filename.c_str());
			cout << "\Edited tag: " << tagToEdit << " to: " << edditedTag << endl;

		}
		catch (TagFileNotFound e) {
			cout << e.what();
		}
		catch (TagNotFound e) {
			cout << e.what();
		}
	}

	void editAddress(FileOpener fileCSV, const string& filename) {
		/*DOCU:
		* This function opens the csv, reads it contents and saves the tag-address combo to a new auxiliary file. This copying continues as normal untill the algorithm
		* encounters the tag that we want to edit its address. When it does find the tag-address to be edited, the program replaces the address with the new address.
		* In the end it renames the auxiliary file to the original file, but only after it deletes the original
		* 
		* 
		* PARAMS: 
		* 
		* FileOpener fileCSV -> required to check the tag in the csv
		* const string& filename -> required to check the presence of the file
		* 
		* RETURNS:
		* 
		* void
		*/
		string tagToEdit, edditedAddress;
		vector<vector<string>> dataFromCSV;
		fstream newCSV;
		string NewTag_Address = "NewTag-Address.csv";


		try {
			if (!fileExists(filename)) {
				throw TagFileNotFound("File not found");
			}

			cout << "\nPlease input the tag that you want to edit it's address: ";
			cin >> tagToEdit;
			cout << "\nPlease input new address for tag {" << tagToEdit << "}: ";
			cin >> edditedAddress;


			dataFromCSV = fileCSV.get_dataFromCSV();
			if (fileCSV.tagExists(tagToEdit, false) == false) {
				string error = "Tag " + tagToEdit + " does not exist in csv!";
				throw TagNotFound("Tag does not exist in csv!");
			}

			newCSV.open(NewTag_Address.c_str(), ios::out | ios::app);
			for (int csvCounter = 0; csvCounter < dataFromCSV.size(); csvCounter++) {
				if (dataFromCSV[csvCounter][0] == tagToEdit) {
					dataFromCSV[csvCounter][1] = edditedAddress;
					newCSV << dataFromCSV[csvCounter][0] << ", " << dataFromCSV[csvCounter][1] << endl;
				}
				else
				{
					newCSV << dataFromCSV[csvCounter][0] << ", " << dataFromCSV[csvCounter][1] << endl;
				}
			}

			newCSV.close();
			remove(filename.c_str());
			rename(NewTag_Address.c_str(), filename.c_str());
			cout << "\Edited tag: " << tagToEdit << " to: " << edditedAddress << endl;

		}
		catch (TagFileNotFound e) {
			cout << e.what();
		}
		catch (TagNotFound e) {
			cout << e.what();
		}

	}

	void deleteAddress(FileOpener fileCSV, const string& filename)
	{
		/*DOCU:
		* This function is used to delete a tag-address combination from the csv. It reads from the keyboard in sequence the tag and checks if it
		* exists in db.
		*
		* params: FileOpener fileCSV  -> this field is required in order to check for presence of the tag
		*
		* returns: bool isDeleted ->    true  if tag was deleted
		*			                    false if tag was not deleted / found
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

		
	}
};


void main()
{


	cout << "Started shell file opener\n" << endl;
	try {
		string tags;
		string tagToFind;
		char exitOption = NULL;
		bool exitLoop = false;
		bool exitMain = false;
		Logger logger("LOG.txt",INFO, true);
		CSVOperations csv;
		string message;

		if (!csv.fileExists("Tag-Address.csv")) {
			throw TagFileNotFound("File with inital tag locations is not present, check to see if it was deleted");
		}


		FileOpener dataFromCSV("Tag-Address.csv");
		logger.log(DEBUG, "created dataFromCSV");
		while (!exitLoop) {
			try {
				int menu;
				cout << "\n-----MENU-----\n"
					<< "1.Open File Explorer\n"
					<< "2.Show available tags and addresses\n"
					<< "3.Show address based on tag\n"
					<< "4.Create new tag - address\n"
					<< "5.Edit tag\n"
					<< "6.Edit address\n"
					<< "7.Delete tag - address\n"
					<< "0.exit"
					<< endl;

				cout << "Make your choice and press enter: ";
				cin >> menu;

				switch (menu)
				{
				case 0: //exit
					message = "User exited the program :" + to_string(menu);
					logger.log(DEBUG, message);


					cout << "\nAre you sure you want to quit?\n [Y/N]: ";
					fflush(stdin);
					exitOption = _getche();


					if (exitOption == 'y' || exitOption == 'Y') {
						exitLoop = true;
						logger.log(DEBUG, "selected exit option: y/Y");
						exit(1);
					}
					else if (exitOption == 'n' || exitOption == 'N') {
						exitLoop = false;
						logger.log(DEBUG, "selected exit option: n/N");
						//cout << exitLoop;
						break;
					}
					else {
						throw InvalidSelection("Selection invalid! Please chose again!");
						exitLoop = false;
						break;
					}

					//exitLoop = true;
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
				case 5: //Edit tag
					csv.editTag(dataFromCSV, "Tag-Address.csv");
					dataFromCSV.setNewDataFromCSV("Tag-Address.csv");
					break;
				case 6: //Edit address
					csv.editAddress(dataFromCSV, "Tag-Address.csv");
					dataFromCSV.setNewDataFromCSV("Tag-Address.csv");
					break;

				case 7: //Delete tag - address
					csv.deleteAddress(dataFromCSV, "Tag-Address.csv");
					dataFromCSV.setNewDataFromCSV("Tag-Address.csv");
					break;
				default:
					cout << "Selection invalid! Please chose again!" << endl;
					break;
				}
			}
			catch (InvalidSelection e) {
				cout << e.what();
				exitLoop = false;
			}
			catch (exception e) {
				cout << "Error detected: \n" << e.what() << endl;
			}
		}
	}
	catch (TagFileNotFound e) {
		cout << e.what();
	}
	catch (exception e) {
		cout << "Error detected: \n" << e.what() << endl;
	}

}

//TODO: Implement feature to check if "Tag-Address.csv" existance, if it does -> program continues; if it doesn't -> create file