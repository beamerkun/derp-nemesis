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

class NameGenerator{
	std::map< char, std::map< char, std::map< char, int > > > mat;	// 3 dimensional matrix containing
																	// how many times any letter 
																	// had appeared after 2 another letters

	public:

	NameGenerator( int seed = time(NULL) ) : mat() {
		srand( seed );
	}

	void update( std::string str ){
		if( str.length() <= 0 || str[0] == '\n')
			return;
		mat[255][str[0]][str[1]] += 1;						// char = 255 marks start of word
		for( int i = 0; i <= str.length() - 2; ++i ){
			mat[str[i]][str[i+1]][str[i+2]] += 1;			// increase counters corresponding to 
															//  letters appearing in 'str'
		}
	}

	std::string generate(){
		char last, curr, next;
		std::string result;

		do {
			std::vector<char> list;

			result.clear();
			last = 255;										// any word begins with 'word-start' char

			for( auto i = mat[last].begin(); i != mat[last].end(); ++i ){	// random pick first letter from
				list.push_back(i->first);									// any letter that occurred as
			}																// first letter in any of words
			curr = list.at( rand()%list.size() );							// from word-list

			do {											// word generation loop
				list.clear();
				result.push_back( last );

				auto matrix = mat[last][curr];								// add any letter which ever appeared
				for( auto j = matrix.begin(); j != matrix.end(); ++j){		// after 'last' and 'curr' as many times
					for( int k = j->second; k > 0; --k ){					// , as it had appeared
						list.push_back(j->first);							//
					}														//
				}															//


				if( list.empty() )							// if theres no chance for any letter to appear
					next = '\0';							// after 'last' and 'curr', finish generating name
				else
					next = list.at( rand()%list.size() );   // if there is some chance though, 
															// pick random letter from 'list'

				last = curr;								// prepare next loop iteration
				curr = next;								//
			} while (curr != '\0' && last != '\0') ;		// '\0' marks end of word

			result = result.substr( 1, result.size() - 1 );	// delete 'word-start' mark from result

		} while ( result.size() < MIN || result.size() > MAX ); // if word isn't short/long enough
																// , generate another word
		return result;
	}

};

int main(int argc, char* argv[]){
	std::string name("dict");
	if( argc > 1){
		name = argv[1];
	}
	NameGenerator generator;
	std::ifstream file;
	file.open(name);
	if( file.good() ){
		while( file.good() ){
			std::string temp;
			file >> temp;
			generator.update(temp);
		}
		std::cout << generator.generate() << std::endl;
		return 0;
	}
	else {
		std::cout << "word-list file \'" << name << "\' doesnt exist!" << std::endl;
	}
	return 1;
}
