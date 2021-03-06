//prob 10 for Num Methods
//Chris Martin

//includes
#include <nr3.h>
#include <odeint.h>
#include <stepper.h>
#include <stepperbs.h>

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "Van_der_Pol.h"
#include "Lane_Emden.h"

//root includes for graphing
#include <TROOT.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TAxis.h>

using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Prob10-ChrisMartin.txt");
	if(ofile.is_open())
	{
		//text header
		ofile << "Problem 10 NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << std::setprecision(std::numeric_limits<double>::digits10+2);
		ofile << endl;
	
		ofile << "Number 1" << endl;
		
		//define canvas and legend
		TCanvas *c1 = new TCanvas("c1","Van der Pol oscillator x(t)",700,500);
   		c1->SetGrid();
   		TLegend *leg = new TLegend(0.8, 0.8, 1.0, 1.0);
   		leg->SetHeader("x(t) vs t");
   		
   		TCanvas *c2 = new TCanvas("c2","Van der Pol oscillator x(t)",500,500);
   		c2->SetGrid();
   		TLegend *leg1 = new TLegend(0.8, 0.8, 1.0, 1.0);
   		leg1->SetHeader("x'(t) vs x(t)");
   		
		
		//follow form on page 906 for limits
		const int n_variables = 2;
		const double atol = 1e-3;
		const double rtol = atol;
		const double h1 = .01;
		const double hmin = 0.;
		const double t1 = 0.;
		const double t2 = 20.;
		
		VecDoub xstart(n_variables);
		
		// loop over different values of mu
		double mu[6] = {0.1,1,2,4,10,50};
		for(int i = 0; i < 6; i++)
		{
			//set initial conditions
			xstart[0] = -2.0;
			xstart[1] = 0.;
			
			//Dense output at 200 points plus t1
			Output out(500);
		
			//Call Van_der_pol
			Van_der_Pol f(mu[i]);
			
			//pass to Odeint
			Odeint<StepperBS<Van_der_Pol> > ode(xstart,t1,t2,atol,rtol,h1,hmin,out,f);
			ode.integrate();
			
			//print output
			Double_t x[out.count], t[out.count], x_dot[out.count];
   			for (Int_t j = 0; j < out.count; j++) 
   			{
    			x_dot[j] = out.ysave[1][j];
     			x[j] = out.ysave[0][j];
    			t[j] = out.xsave[j];
     
   			}
   			
   			//variables needed for graphing
			TGraph *graph = new TGraph(out.count,t,x);
   			graph->SetMarkerColor(i+1);
   			graph->SetMarkerStyle(7);
   			TGraph *graph1 = new TGraph(out.count,x,x_dot);
   			graph1->SetMarkerColor(i+1);
   			graph1->SetMarkerStyle(7);
   			char title [10];
  			int p;
  			p=sprintf (title, "mu = %f", mu[i]);
   			if(i==0) 
   			{
   				c1->cd();
   				graph->SetTitle("Van der Pol oscillator x(t)");
   				graph->Draw("ACP");
   				leg->AddEntry(graph,title,"P");
   				c2->cd();
   				graph1->SetTitle("Van der Pol oscillator");
   				graph1->Draw("AP");
   				leg1->AddEntry(graph,title,"P");
   			}
   			else
   			{
   				c1->cd();
   				graph->Draw("CP");
   				leg->AddEntry(graph,title,"P");
   				c2->cd();
   				graph1->Draw("P");
   				leg1->AddEntry(graph,title,"P");
   			}
   			c1->Update();
   			c2->Update();	
			
		}
		
		//print output to PDF
		c1->cd();
   		leg->Draw();
   		c2->cd();
   		leg1->Draw();
		c1->Print ( "Number1_x_vs_t.pdf" ) ;
		c2->Print ( "Number1_xprime_vs_x.pdf" ) ;
		ofile << endl << "Output contained in the following files: " << endl;
		ofile << "Number1_x_vs_t.pdf" << endl;
		ofile << "Number1_xprime_vs_x.pdf" << endl;
		
		ofile << "Number 2" << endl;
		
		//define canvas and legend
		TCanvas *c3 = new TCanvas("c3","Num 2",700,500);
   		c3->SetGrid();
   		TLegend *leg3 = new TLegend(0.8, 0.8, 1.0, 1.0);
   		leg3->SetHeader("Psi(s) vs s");
   		
   		TCanvas *c4 = new TCanvas("c4","Num 2",500,500);
   		c4->SetGrid();
   		TLegend *leg4 = new TLegend(0.8, 0.8, 1.0, 1.0);
   		leg4->SetHeader("Psi'(s) vs Psi(s)");
   		
		
		//follow form on page 906 for limits
		const int n_variables2 = 2;
		const double atol2 = 1e-3;
		const double rtol2 = atol2;
		const double h2 = .01;
		const double hmin2 = 0.;
		const double s1 = 0.01;
		const double s2 = 7.;
		
		VecDoub Psistart(n_variables2);
		
		// loop over different values of mu
		double n[6] = {0,1,2,3,4,5};
		for(int i = 0; i < 6; i++)
		{
			//set initial conditions
			Psistart[0] = 1.;
			Psistart[1] = 0.;
			
			//Dense output at 200 points plus s1
			Output out2(50);
		
			//Call Van_der_pol
			Lane_Emden f2(n[i]);
			
			//pass to Odeint
			Odeint<StepperBS<Lane_Emden> > ode2(Psistart,s1,s2,atol2,rtol2,h2,hmin2,out2,f2);
			ode2.integrate();
			
			//print output
			Double_t Psi[out2.count], s[out2.count], Psi_dot[out2.count];
   			for (Int_t j = 0; j < out2.count; j++) 
   			{
    			Psi_dot[j] = out2.ysave[1][j];
     			Psi[j] = out2.ysave[0][j];
    			s[j] = out2.xsave[j];
     
   			}
   			
   			//variables needed for graphing
			TGraph *graph2 = new TGraph(out2.count,s,Psi);
   			graph2->SetMarkerColor(i+1);
   			graph2->SetMarkerStyle(7);
   			TGraph *graph3 = new TGraph(out2.count,Psi,Psi_dot);
   			graph3->SetMarkerColor(i+1);
   			graph3->SetMarkerStyle(7);
   			char title2 [10];
  			int q;
  			q=sprintf (title2, "n = %f", n[i]);
   			if(i==0) 
   			{
   				c3->cd();
   				graph2->SetTitle("Lane-Emden Psi(s)");
   				graph2->GetYaxis()->SetRangeUser(-1,1);
   				graph2->Draw("ACP");
   				leg3->AddEntry(graph2,title2,"P");
   				c4->cd();
   				graph3->SetTitle("Lane-Emden");
   				graph3->GetYaxis()->SetRangeUser(-1,1);
   				graph3->GetXaxis()->SetRangeUser(-1,1);
   				graph3->Draw("ACP");
   				leg4->AddEntry(graph2,title2,"P");
   			}
   			else
   			{
   				c3->cd();
   				graph2->Draw("CP");
   				leg3->AddEntry(graph2,title2,"P");
   				c4->cd();
   				graph3->Draw("CP");
   				leg4->AddEntry(graph2,title2,"P");
   			}
   			c3->Update();
   			c4->Update();	
			
		}
		
		//print output to PDF
		c3->cd();
   		leg3->Draw();
   		c4->cd();
   		leg4->Draw();
		c3->Print ( "Number2_Psi_vs_s.pdf" ) ;
		c4->Print ( "Number2_Psiprime_vs_Psi.pdf" ) ;
		ofile << endl << "Output contained in the following files: " << endl;
		ofile << "Number2_Psi_vs_s.pdf" << endl;
		ofile << "Number2_Psiprime_vs_Psi.pdf" << endl;
		
		ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}