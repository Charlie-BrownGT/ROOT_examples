void txtGenerator(const char *dirname="/home/guy/software/geant4/geant4-v11.2.2-gdml-mt-install/projects/diamondDetectorResults/testData/", const char *ext=".root") {
	
	//setting up the file output names  
   	char pngFile[256]; // Adjust the size if needed
	
	//used to get the file names with .root extension in current working directory
	const int MAX_FILES = 1000;
	TString* filenames[MAX_FILES];
	int file_count = 0;
	
	TSystemDirectory dir(dirname, dirname);
	TList *files = dir.GetListOfFiles();
	if (files) {
		TSystemFile *file;
		TString fname;
		TIter next(files);
		while ((file=(TSystemFile*)next())) {
			fname = file->GetName();
			if (!file->IsDirectory() && fname.EndsWith(ext)) {
				//cout << fname.Data() << endl;
				filenames[file_count] = new TString(fname);  //allocate and copy
                    		file_count++;	
			} 
		}
	}
	
	Long64_t nEntries; //the number of entries from each .root file
	double arr[file_count];
	
	for(int i = 0; i < file_count; i++){
	
		TFile *file = TFile::Open(filenames[i]->Data(), "READ");

		// Checking file and tree contents
		if (!file || file->IsZombie()) {
			std::cerr << "Error opening file!" << std::endl;
			return;
		}
		TTree *tree = (TTree*)file->Get("Position");
		if (!tree) {
			std::cerr << "TTree not found!" << std::endl;
			file->Close();
			return;
		}
		
		//finding and printing the total number of entries per tree here
		nEntries = tree->GetEntries();
		arr[i] = nEntries;
		//std::cout << arr[i] << std::endl;
	}
	 /*
	for (int i = 0; i < file_count-1; i++) {
		for (int j = 0; j < file_count-i-1; j++) {
			if (arr[j] < arr[j+1]) {  // Compare adjacent elements
				// Swap arr[j] and arr[j+1] to put the larger element first
				double temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	*/
	
	std::ofstream outputFile;
	outputFile.open("varBeamEnergy70to90MeV.txt");
	double ang = 70;
	
	for(int i = 0; i < file_count; i++){
		outputFile << ang << " " << arr[i] << std::endl;
		std::cout << ang << " " << arr[i] << std::endl;
		ang = ang + 1.;
	}
	outputFile.close();
	
	// Print the filenames stored in the array and free memory used
	std::cout << "Stored Filenames:" << std::endl;
	for (int i = 0; i < file_count; i++) {
		delete filenames[i];
	}
}

