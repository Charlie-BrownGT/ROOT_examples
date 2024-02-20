//initialise data plotting function
void template_data_plotter(){

	//create a new canvas using one of several options, here named c1 and gr respectively
	TCanvas *c1 = new TCanvas();
	TGraphErrors *gr = new TGraphErrors();

	//set any graph parameters that you like
	gr->SetMarkerStyle(kFullCircle);
        gr->SetMarkerSize(1);
        gr->SetLineWidth(2);
        gr->SetLineColor(kRed);
        gr->SetTitle("Graph");
        gr->GetXaxis()->SetTitle("X Values");
        gr->GetYaxis()->SetTitle("Y Values");

	//open data file and set to read in
	fstream file;
	file.open("example_file_output.c", ios::in);

	//define any variables that you need
	double x, y, x_err, y_err;
	int n = 0;

	//iterate through data
	while(1){

		//asign data to variables previously defined
		file >> x >> y >> x_err >> y_err;

		//find length of data set
		n = gr->GetN();

		//plot the points from the variables to the graph
		gr->SetPoint(n, x, y);

		//plot the errors from the variables to the graph
		gr->SerPointError(n, x_err, y_err);

		//break the loop at the end of the file
		if(file.eof()) break;
	}

	//close the data file
	file.close();

	//draw the graph with a plot denoted by A*
	gr->Draw("A*");
}
