#include<vector>
#include<iostream>
#include<stack>
using namespace std;
using rows = vector<bool>;
using mat = vector<rows>;
using vector_d =vector <double>;
class Runge{
public:
    Runge();



    //vector *get_k();
    void compute_k();
private:
//    using rows = vector<bool>;
//    using mat = vector<rows>;
//    using vector_d =vector <double>;
    mat butcher;
    vector_d ci;
    vector_d bi;
    vector_d ki;
    stack <double> y;
    double h;
};


