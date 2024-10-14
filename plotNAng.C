void plotNAng(const char *dirname="/home/guy/software/geant4/geant4-v11.2.2-gdml-mt-install/projects/diamondDetectorResults/testData/", const char *ext=".txt") {

	//setting up the file output names  
   	char pngFile[256]; // Adjust the size if needed

	//used to get the file names with .txt extension in current working directory
	const int MAX_FILES = 1000;
	TString* filenames[MAX_FILES];
	int file_count = 0;
	
	TString filenames2[MAX_FILES]; //defining a seperate array to hold the file names
	
	//get list of .txt files in current directory
	TSystemDirectory dir(dirname, dirname);
	TList *files = dir.GetListOfFiles();
	
	//copy file names to arrays for storage
	if (files) {
		TSystemFile *file;
		TString fname;
		TIter next(files);
		while ((file=(TSystemFile*)next())) {
			fname = file->GetName();
			if (!file->IsDirectory() && fname.EndsWith(ext)) {
				filenames[file_count] = new TString(fname);
				filenames2[file_count] = fname.Data();
				//cout << filenames2[file_count] << endl;
                    		file_count++;	
			} 
		}
	}
	
	//create graph array, legend and canvas
	TGraph* graphs[file_count];
	TCanvas* c1 = new TCanvas("c1", "varBeamEnergy70to90MeV", 800, 600);
    	c1->SetGrid();
	TLegend* legend = new TLegend(0.7, 0.8, 0.9, 0.9);
	
	//initialize variables for name length change
	char legEnt[256], legName[256];
	int strLength;
	
	for (int i = 0; i < file_count; i++) {
		std::ifstream infile(filenames2[i]);
		if (!infile.is_open()) {
			std::cerr << "Error: Could not open file " << filenames2[i] << std::endl;
			continue;
		}
		
		cout << filenames2[i] << endl;
		
		// Vectors to store x and y values
		std::vector<double> x, y;

		double xval, yval;
		while (infile >> xval >> yval) {
			x.push_back(xval);
			y.push_back(yval);
		}
		infile.close();

		// Create a TGraph for the data from the file
		graphs[i] = new TGraph(x.size(), &x[0], &y[0]);
		graphs[i]->SetTitle("varBeamEnergy70to90MeV; Beam Energy (MeV); Observed Events (N)");

		// Set different colors and styles for each graph
		graphs[i]->SetLineColor(i+1);
		graphs[i]->SetLineWidth(3);
		graphs[i]->SetMarkerStyle(1);
		graphs[i]->SetMarkerColor(1);
		
		//Set max and min values for y
		graphs[i]->SetMaximum(50000);
		graphs[i]->SetMinimum(0);

		// Draw the graph
		if (i == 0) {
			// Draw the first graph and set axis labels
			graphs[i]->Draw("ALP");  // A = Axis, L = Line, P = Points
		} else {
		 //Draw subsequent graphs on the same canvas
			graphs[i]->Draw("LP SAME");
		}
		
		//remove the .root suffix in the file name
		strcpy(legEnt, filenames2[i]);
		std::cout << legEnt << std::endl;
		strLength = strlen(legEnt);
		strLength = strLength - 4;
		legEnt[strLength] = '\0';
		strcpy(legName, legEnt);
		
		legend->AddEntry(graphs[i], legName, "l");
	}
	
	legend->Draw();
	c1->Update();
	c1->SaveAs("varBeamEnergy70to90MeV.png");
}
