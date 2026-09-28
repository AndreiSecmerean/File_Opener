#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <conio.h>
#include <iterator>
#include "Custom_Excepions.h"
#include "Logger.h"
#include "FileOpener.h"	 
#include "CSVOperations.h"



using namespace std;

//TODO: refactor code so that the 2 classes are in separate files, and the main function is this file


void main()
	{
		string error_message;
		Logger logger("LOG.txt", INFO, true, true); // Create a logger instance with the following options: log level, enabled, and display logs

		logger.log(INFO, "Started folder/file opener");
		try {
			string tags;
			string tagToFind;
			char exitOption = NULL;
			bool exitLoop = false;
			bool exitMain = false;
			CSVOperations csv;

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
						error_message = "User exited the program :" + to_string(menu);
						logger.log(DEBUG, error_message);


						cout << "\nAre you sure you want to quit?\n [Y/N]: ";
						fflush(stdin);
						exitOption = _getche();


						if (exitOption == 'y' || exitOption == 'Y') {
							exitLoop = true;
							logger.log(DEBUG, "selected exit option: [y/Y]");
							logger.log(INFO, "Exiting program");
							exit(1);
						}
						else if (exitOption == 'n' || exitOption == 'N') {
							exitLoop = false;
							logger.log(DEBUG, "selected exit option: [n/N]");
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
					error_message = "Error detected: \n";
					error_message.append(e.what());
					logger.log(ERROR, error_message);
				}
			}
		}
		catch (TagFileNotFound e) {
			cout << e.what();
		}
		catch (exception e) {
			error_message = "Error detected: \n";
			error_message.append(e.what());
			logger.log(ERROR, error_message);
		}

	}

	//TODO: Implement feature to check if "Tag-Address.csv" existance, if it does -> program continues; if it doesn't -> create file
