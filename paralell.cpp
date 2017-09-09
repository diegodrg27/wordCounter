#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>

#include <unordered_map>
//#include <ctime>
#include <sys/time.h>

#include <vector> 
#include <omp.h>
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
 
bool filter(char c)
{
    return isalpha( c ) == 0;///
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

//const string path = "data";
 
int main()
{
	vector<string> files;
files.push_back("data1");
files.push_back("data2");

    unordered_map<string,WordCounter> counter;

 /*	std::clock_t start;
    double duration;
    start = std::clock();*/

struct timeval start, end;
gettimeofday(&start, NULL); 	

    int n_files = files.size();
 	
 	
 	#pragma omp parallel num_threads(n_files)
 	{
		ifstream input;
		input.open( files[omp_get_thread_num()].c_str() );
	 	//cout<<files[omp_get_thread_num()]<<endl;
	 	
		if ( !input )
		{
		    cout << "Error en abrir el archivo: "<<files[omp_get_thread_num()].c_str()<<endl;
		}
	 
	 	else{
			string tok;     	
			while ( true )
			{
				//tok.resize( remove_if( tok.begin(), tok.end(), filter) - tok.begin() );///
				//cout<<tok<<endl;
				input >> tok;
				vector<string> fuente;
				
				filtro(tok,fuente);
				
				int N = fuente.size();
				
				if (input)
				{
					for(int i=0;i<N;i++){				
							if(fuente[i].size() != 0){
								#pragma omp critical
							 	counter[fuente[i]]++;
							}
					}
					
				}
				else break;     
			}
		}
		
    }

   // duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
   // std::cout<<"printf: "<< duration <<'\n';
	gettimeofday(&end, NULL);

	double duration = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
	cout<<"printf: "<< duration <<'\n';

    ofstream lout("salida_p.txt");
    for (auto& x: counter) {
		lout << x.first << ": " << x.second << std::endl;
	  }
 
    return 0;
}
