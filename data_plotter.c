void data_plotter()
{
	TCanvas *c1 = new TCanvas();
	TGraphErrors *gr = new TGraphErrors();

	gr->SetMarkerStyle(kFullCircle);
        gr->SetMarkerSize(1);
        gr->SetLineWidth(2);
        gr->SetLineColor(kRed);
        gr->SetTitle("Graph");
        gr->GetXaxis()->SetTitle("X Values");
        gr->GetYaxis()->SetTitle("Y Values");

	fstream file;
	file.open("data.txt", ios::in);

	double x, y, ex, ey;

	int n = 0;

	while(1){

		file >> x >> y >> ex >> ey;

		n = gr->GetN();
		gr->SetPoint(n, x, y);
		gr->SetPointError(n, ex, ey);

		if(file.eof()) break;
	}

	file.close();

	gr->Draw("A*");
}
