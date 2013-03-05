#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <ctype.h>
#define MIN 5
#define MAX 15
#define COEFF 0

bool isVowel( char test ){
	test = tolower(test);
	if( test == 'a' || test == 'e' || test == 'i' || test == 'o' || test == 'u' )
		return true;
	else
		return false;
}

class NameGenerator{
	std::map< char, std::map< char, std::map< char, int > > > mat;	// macierz trójwymiarowa przechowująca prawdopodobieństwo 
																	// wystąpienia danego znaku po wystąpieniu 2 innych

	public:

	void update( std::string str ){
		if( str.length() <= 0 || str[0] == '\n')
			return;
		mat[255][str[0]][str[1]] += 1;		// char = 255 to oznacza początek słowa
		for( int i = 0; i <= str.length() - 2; ++i ){
			mat[str[i]][str[i+1]][str[i+2]] += 1;	// zwiekszenie licznika wystąpień znaku 
		}
	}

	std::string generate(){
		char last, curr, next;
		std::string result;

		do {
			std::vector<char> list;
			int vow = 0;
			int cons = 0;

			result.clear();
			last = 255;		// generowanie słowa zaczynamy od znaku początku słowa, duh...

			for( auto i = mat[last].begin(); i != mat[last].end(); ++i ){	// wylosowanie pierwszej litery nowego słowa
				list.push_back(i->first);									// sposrod wszystkich które wystąpiły jako pierwsza
			}																// litera słowa z słownika
			curr = list.at( rand()%list.size() );							//
			
			if ( isVowel(curr) )
				vow = 1;
			else
				cons = 1;

			do {								// pętla generowania słowa
				list.clear();
				result.push_back( last );
					
				for( auto i = mat[last].begin(); i != mat[last].end(); ++i ){	// dodanie to tymczasowej listy kazdego znaku
					auto matrix = i->second;									// tyle razy ile wystapił po dwóch wcześniejszych znakach
					for( auto j = matrix.begin(); j != matrix.end(); ++j){		// generowanego słowa
						int bias;
						if( !isVowel(j->first) ){
							bias = vow;
						} else {
							bias = cons;
						}
						for( int k = j->second + j->second * COEFF * bias; k > 0; --k ){//
							list.push_back(j->first);				
						}
					}															//
				}																//

				if( list.empty() )							// jeśli po danym dwuznaku nigdy nie wystepowala zadna litera
					next = '\0';							// zakończ generowanie
				else
					next = list.at( rand()%list.size() );   // w przeciwnym wypadku wylosuj znak z listy

				if( isVowel(next) ){
					vow		=	0;
					cons	+=	1;
				} else {
					vow		+=	1;
					cons	=	0;
				}
				last = curr;								// zapisanie poprzednich znakow
				curr = next;								//
			} while (curr != '\0' && last != '\0') ;

			result = result.substr( 1, result.size() - 1 );	// usuniecie znaku oznaczajacego poczatek slowa

		} while ( result.size() < MIN || result.size() > MAX );

		return result;
	}

};

int main(){
	NameGenerator nam;
	srand( time(NULL) );
	std::ifstream file;
	file.open("dict");
	while( file.good() ){
		std::string temp;
		file >> temp;
		nam.update(temp);
	}
	std::cout << nam.generate() << std::endl;
	return 0;
}
