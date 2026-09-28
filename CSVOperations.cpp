#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "FileOpener.h"
#include "CSVOperations.h"
#include "Custom_Excepions.h"


using namespace std;

bool CSVOperations::fileExists(const string& filename) {
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

void CSVOperations::createCSVFile(const string& filename) {
	static bool doesFileExist = CSVOperations::fileExists(filename);
	if (!doesFileExist) {

	}
}

void CSVOperations::addressCreator(FileOpener fileCSV) {
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

			cout << "\nInput a new addres for tag " << this->newTag << ": ";
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

void CSVOperations::editTag(FileOpener fileCSV, const string& filename) {
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

void CSVOperations::editAddress(FileOpener fileCSV, const string& filename) {
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

void CSVOperations::deleteAddress(FileOpener fileCSV, const string& filename)
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

		//get data from csv and check if the tag exists, if it doesn't throw an exception
		dataFromCSV = fileCSV.get_dataFromCSV();
		if (fileCSV.tagExists(tagToDelete, false) == false) {
			string error = "Tag " + tagToDelete + " does not exist in csv!";
			throw TagNotFound("Tag does not exist in csv!");
		}

		//creates a new csv file and coppies content from the old csv to the new one, but skips the tag that we want to delete
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

void CSVOperations::orderTags(FileOpener fileCSV, const string& filename) {
	/*DOCU:
	* This function is used to order the tags in the csv. It reads from the csv and saves the tag-address combo to a new auxiliary file. When it does find the tag-address to be edited, the program replaces the address with the new address.
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




}