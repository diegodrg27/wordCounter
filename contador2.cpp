#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>

#include <unordered_map>
#include <ctime>
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
 
//const string path = "data";
 
int main()
{
	vector<string> files;
	files.push_back("data");
	files.push_back("data2");

    unordered_map<string,WordCounter> counter;
 	std::clock_t start;
    double duration;
 	int n_files = files.size();
 	
 	
 	start = std::clock();
 	#pragma omp parallel num_threads(n_files)
 	{
		ifstream input;
		input.open( files[omp_get_thread_num()].c_str() );
	 	cout<<files[omp_get_thread_num()]<<endl;
	 	
		if ( !input )
		{
		    cout << "Error in opening file Hamlet.txt\n";
		    return 0;
		}
	 
		string tok;     	

		while ( true )
		{
		    input >> tok;
	 
		    tok.resize( remove_if( tok.begin(), tok.end(), filter) - tok.begin() );///
		     
		    if ( input )
		    {
		        counter[ tok ]++;
		    }
		    else break;     
		}
    }
    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"printf: "<< duration <<'\n';
    /*
    for (auto& x: counter) {
		std::cout << x.first << ": " << x.second << std::endl;
	  }*/
 
    return 0;
}
