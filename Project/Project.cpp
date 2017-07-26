//project for Num Methods
//Chris Martin

//ROOT includes
#include <TROOT.h>
#include <TRandom.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TMath.h>
#include <TF1.h>
#include <TStyle.h>
#include <TLegend.h>

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Custom includes
#include "Lifetime.h"

using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Project-ChrisMartin.txt");
	if(ofile.is_open())
	{
		//text header
		ofile << "Project NumMthds Sp2012" << endl;
		ofile << "Output for Project" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << endl << endl;
		
		//beam energy parameters (MeV) random from Gaussian
		const double BeamE_mean = 1000.;
		const double BeamE_stdev = 10.;
		
		//number of tried and generated events
		const int Tried = 100000;
		int Detected = 0;
		
		//Set t_max nanoseconds
		const double t_max = 50.;
	
		// lepton lifetimes microseconds
		const double tau_mu = 2.197034;
		const double tau_mu_Err = .000021;
		const double tau_tau = 2.906e-7;
		const double tau_tau_Err = 1.0e-9;
		
		//lepton mass (MeV/c^2)
		const double mu_m = 105.658367;
		const double mu_mErr = 4e-6;
		const double tau_m = 1776.82;
		const double tau_mErr = .16;
		
		//variables needed
		double gamma; //(v/c)
		double t[Tried] = {0.};
		TCanvas *beam_canvas = new TCanvas("beam_canvas", "",1000,600);
		TH1F *beamhist = new TH1F("E_{Beam} Distribution", "", 1000, BeamE_mean - BeamE_stdev*10.,BeamE_mean + BeamE_stdev*10.);
		beamhist->SetTitle("Beam Energy; E[MeV];");
		beamhist->SetStats(0);
		
		/* initialize random seed: */
		srand ( time(NULL) );
		TRandom r_beam;
		
		//Generate
		for(int i = 0; i < Tried; i++)
		{	
			//assign flavor
			int flavor = rand() % 3;
			
			//beam energy (MeV) random from Gaussian
			double BeamE = r_beam.Gaus(BeamE_mean,BeamE_stdev);
			beamhist->Fill(BeamE);
			
			if(flavor == 0)
			{
				//electron
				//No decay
				t[i] = t_max;
			}	
			else if(flavor == 1)
			{
				//muon
				gamma = BeamE/mu_m;
				t[i] = Lifetime(tau_mu)*gamma;
				if(t[i] > t_max)
				{
					t[i] = t_max;
					continue;
				}
				Detected++;
			}
			
			else if(flavor == 2)
			{
				//tau
				gamma = BeamE/tau_m;
				t[i] = Lifetime(tau_tau)*gamma;
				if(t[i] > t_max)
				{
					t[i] = t_max;
					continue;
				}
				Detected++;
			}
		}
		
		beamhist->Draw();
		
		beam_canvas->Print("Beam_Energy.png");
		
		//Define mu and tau gamma
		double tau_gamma = BeamE_mean/tau_m;
		double tau_gamma_Err = 1./tau_m * sqrt(BeamE_stdev*BeamE_stdev + tau_gamma*tau_gamma*tau_mErr*tau_mErr);
		double mu_gamma = BeamE_mean/mu_m;
		double mu_gamma_Err = 1./mu_m * sqrt(BeamE_stdev*BeamE_stdev + mu_gamma*mu_gamma*mu_mErr*mu_mErr);
		
		ofile << "The accepted lifetimes (microseconds): " << endl;
		ofile << "Muon Lifetime: " << tau_mu << " +/- " << tau_mu_Err << endl;
		ofile << "Tau Lifetime: " << tau_tau << " +/- " << tau_tau_Err << endl << endl;
		
		ofile << "Number of Events Seeded: " << Tried << endl;
		ofile << "Number of Events Detected: " << Detected << endl << endl;
		
		//Create Muon Histogram
		gStyle->SetOptFit();
		const int n_bins = 100;
		double t_graph_min = .00001;
		double t_graph_max = t_max;
		TCanvas *c = new TCanvas("c", "",1000,600);
		c->SetLogy();
		TH1F *h = new TH1F("N(t) = N_{#mu0}Exp[-t/(#gamma#tau_{1/2#mu})]", "", n_bins, t_graph_min, t_graph_max);
		h->SetTitle("MC #mu sector; t[#mus];");
		h->Sumw2();
		
		for(int i = 0; i < Tried; i++)
		{
			if(t[i] < t_graph_max && t[i] > t_graph_min)
			{
				h->Fill(t[i]);
			}
		}
		
		TF1* fit = new TF1("fit","[0]*TMath::Exp(-x/[1])",t_graph_min,t_graph_max);
		fit->SetParameters(Detected/2,tau_mu*mu_gamma);
		fit->SetParNames("N_{#mu0}","#gamma#tau_{1/2#mu}");
		fit->SetParLimits(0,0.,Detected);
		h->Fit("fit", "IWL");
		h->Draw();
		
		c->Print("Muon_MC.png");
		
		//Create Tau Histogram
		const int n_bins1 = 100;
		double t_graph_max1 = t_graph_min;
		TCanvas *c1 = new TCanvas("c1", "",1000,600);
		c1->SetLogy();
		TH1F *h1 = new TH1F("N(t) = N_{#tau0}Exp[-t/(#gamma#tau_{1/2#tau})]", "", n_bins1, 0., t_graph_max1);
		h1->SetTitle("MC #tau sector; t[#mus];");
		h1->Sumw2();
		
		for(int i = 0; i < Tried; i++)
		{
			if(t[i] < t_graph_max1)
			{
				h1->Fill(t[i]);
			}
		}
		
		TF1* fit1 = new TF1("fit1", "[0]*TMath::Exp(-x/[1])", 0., t_graph_max1);
		fit1->SetParameters(Detected - fit->GetParameter(0)/2.,tau_tau*tau_gamma);
		fit1->SetParNames("N_{#tau0}","#gamma#tau_{1/2#tau}");
		fit1->SetParLimits(0,0,Detected - fit->GetParameter(0)); 
		h1->Fit("fit1","IWL");
		
		h1->Draw();
		c1->Print("Tau_MC.png");
		
		//Create Full Histogram
		const int n_bins2 = 100;
		TCanvas *c2 = new TCanvas("c2", "",1000,600);
		c2->SetLogy();
		TH1F *h2 = new TH1F("Full Plot","",n_bins2,0.,t_graph_max);
		h2->Sumw2();
		
		for(int i = 0; i < Tried; i++)
		{
			if(t[i] < t_graph_max)
			{
				h2->Fill(t[i]);
			}
		}
		
		double mu_lifetime = fit->GetParameter(1)/mu_gamma;
		double mu_lifeErr = 1./mu_gamma * sqrt(fit->GetParError(1)*fit->GetParError(1) + mu_lifetime*mu_lifetime*mu_gamma_Err*mu_gamma_Err);
		double tau_lifetime = fit1->GetParameter(1)/tau_gamma;
		double tau_lifeErr = 1./tau_gamma * sqrt(fit1->GetParError(1)*fit1->GetParError(1) + tau_lifetime*tau_lifetime*tau_gamma_Err*tau_gamma_Err);
		
		ofile << "The Fits found (microseconds): " << endl;
		ofile << "Muon Lifetime: " << mu_lifetime << " +/- " << mu_lifeErr << endl;
		ofile << "Tau Lifetime: " << tau_lifetime << " +/- " << tau_lifeErr << endl;
	
	
		ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}