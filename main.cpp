#include<iostream>
#include<vector>
#include<runge.h>
#include<boost/numeric/ublas/matrix.hpp>
#include<boost/numeric/ublas/io.hpp>
using namespace boost::numeric::ublas;
using namespace std;
double Func(double x, double y) // исходная функция
{
    return y+x*x+1;
}



int main()
{

    matrix<double> butcher (4, 4); //  матрица батчера

    for (unsigned i = 0; i < butcher.size1 (); ++ i)        // заполнение  матрицы нулями
        for (unsigned j = 0; j < butcher.size2 (); ++ j)
            butcher (i, j) = 0;

    butcher(1,0) = 0.5; butcher(2,1) = 0.5;butcher(3,1) = 1; // определение ненулевых элементов матрицы
    std::cout << butcher<< std::endl; // вывод для проверки полученной матрицы

    using vector_d = std::vector<double>;

    vector_d ci = {0,0.5,0.5,1}; // вектор столбец
    vector_d bi = {0.166,0.333,0.333,0.166}; // вектор-строка
    vector_d yi; // решения
    vector_d xi;// значения по икс
    vector_d ki;// коэффициены
    double sum=0; double sum1 = 0;
    double a,b;// границы
    a = 0; b = 1;
    double step = 0.001; // шаг сетки
    int n = static_cast<int>((b-a)/step); // число итераций, зависит от шага

    uint8_t stages = butcher.size1()+1; // количество стадий

    double y0 = 0.5; // начальные условия
    double x0 = a;// начальные условия

    // n = static_cast<int>((b-a)/step);

    for(auto nn=0;nn<stages;++nn)
    {   ki.push_back(0);
        bi.push_back(0);
    }
    ki[0] = Func(x0,y0);


    for(auto nn=0;nn<n;++nn){
        xi.push_back(0);
        yi.push_back(0);
    }

    yi[0] = 0.5;

    for(unsigned nn=1;nn<n;++nn){
        sum1=0;
        for (unsigned i = 0; i < butcher.size1 ()-1; ++ i){
            sum = 0;
            for (unsigned j = 0; j < butcher.size2 ()-1; ++ j){
                sum+=butcher(i+1,j)*ki[j];
                ki[i+1] = Func(xi[nn-1]+ci[i+1]*step,yi[nn-1]+step*sum);
            }
        }
        for (unsigned k = 0; k < butcher.size2 (); ++ k){
            sum1 += bi[k]*ki[k];

        }
        yi[nn] = yi[nn-1]+step*sum1;
        cout<<xi[nn-1]<<":::"<<yi[nn-1]<<endl;
        xi[nn] = xi[nn-1]+step;}


}
