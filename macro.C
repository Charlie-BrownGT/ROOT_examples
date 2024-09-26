void macro(){
	
	TH1F *h1 = new TH1F("h1", "Random Gaussian distribution with polynomial", 100, -20, 20); 
	TRandom3 rndgen;
	
	TCanvas *c1 = new TCanvas("c1", "Gaussion and polynomial plot");
	
	int a = 0;
	int b = 1;
	int c = 0;
	
	double N[6];
	double M[6];
	double Nerr[6];
	double Merr[6];
	
	while(b <= 100000){
	
		for (int i = 0; i < b; ++i){
			h1->Fill(rndgen.Gaus(-1,5.));
			a = i + 1;
		}
		
		TF1 *myGaus = new TF1("myGaus", "gaus", -20, 20);
		
		h1->Draw();
		h1->Fit(myGaus);
		
		double sigma=myGaus->GetParameter(2);
		double errorSigma=myGaus->GetParError(2);
		double mean=myGaus->GetParameter(1);
		double errorMean=myGaus->GetParError(1);
		
		cout<<"Mean is : "<<mean<<" Error mean is: "<<errorMean<<endl;
		cout<<"Sigma is : "<<sigma<<" Error sigma is: "<<errorSigma<<endl;
		
		double gaussianIntegral = myGaus->Integral(-sigma, sigma);
		cout<<"Integral is : "<<gaussianIntegral<<endl;
		
		N[c] = b;
		M[c] = mean;
		Nerr[c] = 0;
		Merr[c] = errorMean;
		
		b = b * 10;
		c = c + 1;
	}
	
	TF1 *polynomial = new TF1("polynomial", "[0] + [1]*x + [2]*x^2", -20, 20);
	polynomial->SetParameters(1, 0.5, 10);
	polynomial->SetLineColor(kBlue);
	polynomial->Draw("same");
	c1->Update();
	
	TCanvas *c2 = new TCanvas("c2", "TGraph with errors showing errors in Gaussion distribution against points plotted");
	TGraphErrors *h2 = new TGraphErrors(c, N, M, Nerr, Merr);
	h2->SetTitle("TGraph with errors showing errors in Gaussion distribution against points plotted");
	h2->GetHistogram()->GetXaxis()->SetTitle("Number of points");
	h2->GetHistogram()->GetYaxis()->SetTitle("Mean Error");
	h2->Draw();	
}
