void runIDplot(const char *dirname="/home/guy/software/geant4/geant4-v11.2.2-gdml-mt-install/projects/diamondDetectorResults/testData/", const char *ext1=".root", const char *ext2=".root") {

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
			if (!file->IsDirectory() && fname.EndsWith(ext1)) {
				//cout << fname.Data() << endl;
				filenames[file_count] = new TString(fname);  //allocate and copy
                    		file_count++;	
			} 
		}
	}

	double arr[file_count][2];
	double x[file_count], y[file_count];
	
	Long64_t nEntries; //the number of entries from each .root file
	double runID; //the runID from each .root file
	
	TGraph* graph;
	TCanvas* c1 = new TCanvas("c1", "varBeamEnergy70to90MeV", 800, 600);
	c1->SetGrid();
	TLegend* legend = new TLegend(0.7, 0.8, 0.9, 0.9);
	
	char legEnt[256], legName[256];
	int strLength;
	
	for(int i = 0; i < file_count; i++){
	
		TFile *file = TFile::Open(filenames[i]->Data(), "READ");

		// Checking file and tree contents
		if (!file || file->IsZombie()) {
			std::cerr << "Error opening file!" << std::endl;
			return;
		}
		TTree *tree1 = (TTree*)file->Get("Position");
		if (!tree1) {
			std::cerr << "TTree Position not found!" << std::endl;
			file->Close();
			return;
		}
		TTree *tree2 = (TTree*)file->Get("RunID");
		if (!tree2) {
			std::cerr << "TTree RunID not found!" << std::endl;
			file->Close();
			return;
		}
		
		nEntries = tree1->GetEntries();
		
		tree2->SetBranchAddress("RunID", &runID);
		tree2->GetEntry(0);
		
		arr[i][0] = runID;
		arr[i][1] = nEntries;
		
		x[i] = arr[i][0];
		y[i] = arr[i][1];
		
		cout << x[i] << " " << y[i] << endl;
		
		graph = new TGraph(file_count, x, y);
		graph->SetTitle("varBeamEnergy70to90MeV; Beam Energy (MeV); Observed Events (N)");
		graph->SetMarkerStyle(1); 
		graph->SetMarkerColor(1);
		graph->SetMarkerSize(3);
		graph->SetLineColor(2);
		graph->SetLineWidth(1);
		graph->SetMaximum(50000);
		graph->SetMinimum(0);
		graph->Draw("AL*");	
	}
	
	legend->AddEntry(graph, "Counts Observed" , "l");
	legend->Draw();
	c1->Update();
	c1->SaveAs("varBeamEnergy70to90MeV.png");
}
