{
	TH1F hist("hist", "Histogram", 100, 05, 5);

	TRandom2 r;

	for(int i = 0; i < 1000; i++){
	
	hist.Fill(r.Gaus());
	}

	TCanvas *c1 = new TCanvas();
	hist.Draw();
	hist.Fit("gaus");
}
