//Simulation HW for Num Methods
//Chris Martin

//includes

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Evolve.h"

//root includes for graphing
#include <TROOT.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TLegend.h>
#include <TAxis.h>

using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Simulation-ChrisMartin.txt");
	if(ofile.is_open())
	{
		//text header
		ofile << "Simulation NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << endl;
	
		ofile << "Number 1" << endl;
		
		//define canvas and legend
		TCanvas *c1 = new TCanvas("c1","Two Mass Positions",700,500);
   		c1->SetGrid();
   		TLegend *leg = new TLegend(0.8, 0.8, 1.0, 1.0);
   		leg->SetHeader("2 Mass");
		
		//define system
		const int nMasses = 2;
		double Mass[nMasses] = {0};
		ofile << "Masses: ";
		for(int i = 0; i < nMasses; i++)
		{
			 Mass[i] = 9;
			 ofile << Mass[i] << ", ";
		}
		ofile << endl;
		double position[nMasses][3] = {0};
		for(int i = 0; i < nMasses; i++)
		{
			 position[i][0] = (i+1)*4;
		}
		double velocity[nMasses][3] = {0};

		double DeltaT = .1;
		const int nsteps = 500;
		
		//arrays for graphing
		double x_t[nMasses][nsteps] = {0};
		double t[nsteps] = {0};
		
		for(int time = 0; time < nsteps; time++)
		{
			//Update Pos and Vel
			Evolve(nMasses, Mass, position, velocity, DeltaT);
			for(int i = 0; i < nMasses; i++)
			{
				x_t[i][time] = position[i][0];
			}
			
			t[time] = time*DeltaT;
		}
		
		//variables needed for graphing
		TGraph *graph = new TGraph(nsteps,t,x_t[0]);
   		graph->SetMarkerColor(1);
   		graph->SetMarkerStyle(7);
		TGraph *graph1 = new TGraph(nsteps,t,x_t[1]);
   		graph1->SetMarkerColor(2);
   		graph1->SetMarkerStyle(7);

   		c1->cd();
   		graph1->SetTitle("2 Mass r_{soft} = 3");
   		graph->SetTitle("2 Mass r_{soft} = 3");
   		graph->Draw("ACP");
   		graph1->Draw("CP");
   		graph->GetYaxis()->SetRangeUser(0.,10.);
   		leg->AddEntry(graph,"Mass1","P");

		leg->AddEntry(graph1,"Mass2","P");
   		c1->Update();
			
		//print output to PDF
		c1->cd();
   		leg->Draw();
		c1->Print ( "Mass_x_vs_t.pdf" ) ;
		ofile << endl << "Output contained in the following files: " << endl;
		ofile << "Mass_x_vs_t.pdf" << endl;
		
		//Circular Oribits
		ofile << "Number 2.1" << endl;
		
		/*OUTPUT BROKEN
		//Place masses
		position[0][0] = 2.;
		position[0][1] = 0.;
		position[0][2] = 0.;
		position[0][0] = -2.;
		position[0][1] = 0.;
		position[0][2] = 0.;
		velocity[0][0] = 0.;
		velocity[0][1] = 1.5;
		velocity[0][2] = 0.;
		velocity[0][0] = 0.;
		velocity[0][1] = -1.5;
		velocity[0][2] = 0.;
		
		//Make graphing arrays
		double x2[nMasses];
		double y2[nMasses];
		double z2[nMasses];
		TCanvas *c2 = new TCanvas("c2");
		
		for(int time = 0; time < nsteps; time++)
		{
			
			//Update Pos and Vel
			Evolve(nMasses, Mass, position, velocity, DeltaT);
			for(int i = 0; i < nMasses; i++)
			{
				x2[i] = position[i][0];
				y2[i] = position[i][1];
				z2[i] = position[i][2];
			}
			
			TGraph2D *graph2 = new TGraph2D(nMasses, x2, y2, z2);
			graph2->Draw("P0");
			graph2->GetXaxis()->SetRangeUser(-10.,10.);
			graph2->GetYaxis()->SetRangeUser(-10.,10.);
			graph2->GetZaxis()->SetRangeUser(-10.,10.);
			char title [10];
  			int p;
  			p=sprintf (title, "time_%i.gif", time);
			c2->Print ( title ) ;
			delete graph2;
		}
		*/
		
	ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}	