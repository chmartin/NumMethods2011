#ifndef PRINT_H
#define PRINT_H
 
class Print{
public:
Print(MatDoub Matrix, ofstream& file);
Print(VecDoub Vector, ofstream& file);
Print(VecComplex Vector, ofstream& file);
Print(double array[], const int height, const int width, ofstream& file);
bool done;
}; 
#endif