#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>

#include <unordered_map>
#include <ctime>
 
using namespace std;
 
class WordCounter
{
public:
    int value;
    WordCounter() : value( 0 ) {}
     
    void operator++ (int) { value++; }
};
 
ostream& operator<<(ostream& st, WordCounter& wc )
{
    return st << wc.value;
}
 
void filtro(string cadena, vector<string> & cont){
	cadena+="-";
	int N = cadena.size();
	string palabra="";
	for(int i=0; i<N; i++){
		if( (cadena[i]>=97 && cadena[i]<=122) || (cadena[i]>=65 && cadena[i]<=90)){
			palabra += cadena[i];
		}	
		else{	
			if(!palabra.empty()){
				cont.push_back(palabra);
				palabra.clear();
			}
		}
	}
}

 
const string path = "data";
 
int main()
{
    unordered_map<string,WordCounter> counter;
 
    ifstream input;
    input.open( path.c_str() );
 
    if ( !input )
    {
        cout << "Error in opening file"<<path<< "\n";
        return 0;
    }
 
    string tok;     
 
 	std::clock_t start;
    double duration;

    start = std::clock();

    while ( true )
    {
        input >> tok;
	vector<string> fuente;
	filtro(tok,fuente);
 
	int N = fuente.size();
         
        if ( input )
        {
            for(int i=0;i<N;i++){				
		if(fuente[i].size() != 0){
			counter[fuente[i]]++;
		}
	    }
        }
        else break;     
    }
    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    
    ofstream lout("salida.txt");
    
    std::cout<<"printf: "<< duration <<'\n';
    
    for (auto& x: counter) {
		lout << x.first << ": " << x.second << std::endl;
	  }
 
    return 0;
}
