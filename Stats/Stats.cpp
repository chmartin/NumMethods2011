//Stats for Num Methods
//Chris Martin

//includes
#include <nr3.h>
#include <fit_examples.h>
#include <gaussj.h>
#include <fitmrq.h>
#include <sort.h>
#include <ksdist.h>
#include <kstests.h>

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "bgfgauss.h"

//ROOT includes for graphing
#include <TROOT.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TAxis.h>

using namespace std;

#ifndef PI
#define PI           3.14159265358979323846
#endif

int main()
{

	//make output file
	ofstream ofile ("Stats-ChrisMartin.txt");
	if(ofile.is_open())
	{
		//text header
		ofile << "Stats NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << std::setprecision(std::numeric_limits<double>::digits10+2);
		ofile << endl;
	
		ofile << "Number 1" << endl;
		
		//define canvas and legend
		TCanvas *c1 = new TCanvas("c1","Simulated",700,500);
   		c1->SetGrid();
   		
   		//set data arrays
   		const double x_min = 0.05;
   		const double x_max = 1.50;
   		const int nbins = 100;
   		double x_step = (x_max-x_min)/nbins;
   		double x_i[nbins] = {0};
   		for (int i = 0; i < nbins; i++)
   		{
   			x_i[i] = x_min+i*x_step;
   		}
   		
   		//generate gaussian variables
   		const int ngauss_x_3 = 6;
   		double mu0=1.0, Sig0=0.05, Norm0=1., mu1=1.1, Sig1=0.01, Norm1=1.0;
   		double bare[ngauss_x_3] = {mu0, Sig0, Norm0, mu1, Sig1, Norm1};
   		double B0=bare[2]/(bare[1]*sqrt(2*PI));
   		double E0=bare[0];
   		double G0=sqrt(2)*bare[1];
   		double B1=bare[5]/(bare[4]*sqrt(2*PI));
   		double E1=bare[3];
   		double G1=sqrt(2)*bare[4];
   		double arr[ngauss_x_3] = {B0, E0, G0, B1, E1, G1};
   		VecDoub a(ngauss_x_3,arr);
   		VecDoub dyda_gauss(ngauss_x_3);
   		
   		//find y(x) = 1+gauss(1)+gauss(2) and dy/dx for each x
   		double y_i[nbins] = {1};
   		//set y error on each point to .1 (noise) and x error to 0
   		double ey[nbins] = {0};
   		double ex[nbins] = {0};
   		//Randomize input. +/- .05 for each value
   		srand ( time(NULL) );
   		int plus_minus;
   		for (int j = 0; j < nbins; j++)
   		{
   			bgfgauss(x_i[j], a, y_i[j], dyda_gauss);
   			ey[j] = .1;
   			plus_minus = rand() % 2;
   			if(plus_minus == 0)
			{
				y_i[j] += .05;
			}
			else
			{
				y_i[j] -= .05;
			}
   			
   		}
   			
   		
   		//variables needed for graphing
	   	TGraphErrors *graph = new TGraphErrors(nbins,x_i,y_i,ex,ey);
   		graph->SetMarkerColor(1);
   		graph->SetMarkerStyle(6);
   			

		c1->cd();
   		graph->SetTitle("Number 1 Data with Error Bars +/- .1");
   		graph->Draw("AP");
   		c1->Update();
		
		//print output to PDF
		c1->cd();
		c1->Print ( "Number1.pdf" ) ;
		
		ofile << endl << "Output contained in the following files: " << endl;
		ofile << "Number1.pdf" << endl;
		
		ofile << endl <<"Number 2" << endl;
		
		//define canvas and legend
		TCanvas *c2 = new TCanvas("c2","Simulated with Fit",700,500);
   		c2->SetGrid();
   		TLegend *leg = new TLegend(0.1, 0.7, .5, .9);
   		leg->SetHeader("Number 2");
   		
   		//Randomize input. +/- 10% for each value
   		srand ( time(NULL) );
   		for(int i = 0; i < ngauss_x_3; i++)
		{
			plus_minus = rand() % 2;
			if(plus_minus == 0)
			{
				bare[i] += .1*bare[i];
			}
			else
			{
				bare[i] -= .1*bare[i];
			}
		}
		B0=bare[2]/(bare[1]*sqrt(2*PI));
   		E0=bare[0];
   		G0=sqrt(2)*bare[1];
   		B1=bare[5]/(bare[4]*sqrt(2*PI));
   		E1=bare[3];
   		G1=sqrt(2)*bare[4];
   		double arr2[ngauss_x_3] = {B0, E0, G0, B1, E1, G1};
   		VecDoub a2(ngauss_x_3,arr2);
   		VecDoub dyda_gauss2(ngauss_x_3);
		
		//recalculate the data points
		for (int j = 0; j < nbins; j++)
   		{
   			bgfgauss(x_i[j], a2, y_i[j], dyda_gauss2);
   			ey[j] = .1;
   			//put some more realistic noise
   			plus_minus = rand() % 2;
   			if(plus_minus == 0)
			{
				y_i[j] += .05;
			}
			else
			{
				y_i[j] -= .05;
			}
   			
   		}
   		
   		//variables needed for graphing
	   	TGraphErrors *graph2 = new TGraphErrors(nbins,x_i,y_i,ex,ey);
   		graph2->SetMarkerColor(1);
   		graph2->SetMarkerStyle(6);
   		graph2->SetTitle("Number 2 Data with Fit");
   		graph2->Draw("AP");
   		leg->AddEntry(graph,"Simulated Data with Error Bars +/- .1","P");
   		c2->Update();
   		
   		
   		//Fit Data using pre-randomized values for initial conditions
   		VecDoub x(nbins,x_i);
   		VecDoub y(nbins,y_i);
   		VecDoub Ey(nbins,ey);
   		Fitmrq myfit(x, y, Ey, a, bgfgauss);
		myfit.fit();
		
		for (int j = 0; j < nbins; j++)
   		{
   			y_i[j] = y[j];
   			bgfgauss(x_i[j], myfit.a, y_i[j], dyda_gauss2);
   			
   		}
   		
   		TGraph *graph3 = new TGraph(nbins,x_i,y_i);
		graph3->SetMarkerColor(8);
   		graph3->SetMarkerStyle(25);
   		graph3->Draw("PL");
   		char title [35];
  		int p;
  		p=sprintf(title,"Fit to Data with Chi^2/DOF = %+.2e", myfit.chisq/myfit.a.size());
   		leg->AddEntry(graph3, title,"PL");
   		leg->Draw();
   		c2->Update();
		
		//print output to PDF
		c2->Print ( "Number2.pdf" ) ;
		
		ofile << endl << "Output contained in the following files: " << endl;
		ofile << "Number2.pdf" << endl;
		
		ofile << endl <<"Number 3" << endl;
		// read off fit parameters
		double mu0fit = abs(myfit.a[1]);
		double mu1fit = abs(myfit.a[4]);
		double Sig0fit = abs(myfit.a[2]/sqrt(2.));
		double Sig1fit = abs(myfit.a[5]/sqrt(2.));
		double Norm0fit = abs(myfit.a[0]*myfit.a[2]*sqrt(PI));
		double Norm1fit = abs(myfit.a[3]*myfit.a[5]*sqrt(PI));
		
		//loop over each parameter to find error
		double chisqinitial = myfit.chisq;
		double paraminit[myfit.a.size()];
		double paramfinal[myfit.a.size()];
		double step = 1e-5;
		for(int i = 0; i < myfit.a.size(); i++)
		{
			double chisqnew = 0;
			double count = 0;
			do
			{
				//freeze one parameter
				paraminit[i] = myfit.a[i];
				myfit.hold(i, (paraminit[i]*(1. + count*step)));
				//refit
				myfit.fit();
				paramfinal[i] = myfit.a[i];
				chisqnew = myfit.chisq;
				myfit.free(i);
				count++;
			}
			while(abs(chisqnew-chisqinitial) < 1.);
		}
		
		//find final paramaters
		double mu0new = abs(paramfinal[1]);
		double mu1new = abs(paramfinal[4]);
		double Sig0new = abs(paramfinal[2]/sqrt(2.));
		double Sig1new = abs(paramfinal[5]/sqrt(2.));
		double Norm0new = abs(paramfinal[0]*paramfinal[2]*sqrt(PI));
		double Norm1new = abs(paramfinal[3]*paramfinal[5]*sqrt(PI));		
		
		ofile << "Here are the fit Parameters." << endl;
		ofile << "mu0 = " << mu0fit << ", % Error = " << abs(mu0fit-mu0new)/mu0fit << endl;
		ofile << "Sig0 = " << Sig0fit << ", % Error = " << abs(Sig0fit-Sig0new)/Sig0fit << endl;
		ofile << "Norm0 = " << Norm0fit << ", % Error = " << abs(Norm0fit-Norm0new)/Norm0fit << endl;
		ofile << "mu1 = " << mu1fit << ", % Error = " << abs(mu1fit-mu1new)/mu1fit << endl;
		ofile << "Sig1 = " << Sig1fit << ", % Error = " << abs(Sig1fit-Sig1new)/Sig1fit << endl;
		ofile << "Norm0 = " << Norm1fit << ", % Error = " << abs(Norm1fit-Norm1new)/Norm1fit << endl;
		
		ofile << endl <<"Number 4" << endl;
		//declare data arrays
		double a4[15] = {1,1,3,0,0,3,1,5,4,9,0,6,5,0,8};
		VecDoub A4(15,a4);
		double b4[15] = {4,0,2,2,1,2,0,0,3,0,3,4,2,1,0};
		VecDoub B4(15,b4);
		double c4[15] = {2,3,2,0,3,4,0,3,4,0,0,3,0,0,2};
		VecDoub C4(15,c4);
		double prob_ab, prob_ac, prob_bc, d;
		
		kstwo(A4, B4, d, prob_ab);
		kstwo(A4, C4, d, prob_ac);
		kstwo(B4, C4, d, prob_bc);
		
		ofile << "The probability that a and b are from the same distribution is: " << prob_ab << endl;
		ofile << "The probability that a and c are from the same distribution is: " << prob_ac << endl;
		ofile << "The probability that c and b are from the same distribution is: " << prob_bc << endl;
		
		ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}