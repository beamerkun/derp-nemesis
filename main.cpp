#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <ctype.h>
#define MIN 7
#define MAX 15


class NameGenerator{
	std::map< char, std::map< char, int > > mat;
	
	public:
	
	void update( std::string str ){
		if( str.length() <= 0 )
			return;
		for( int i=0; i <= str.length() - 1; ++i ){
			int* num = &mat[tolower(str[i])][str[i+1]];
			*num += 1;
		}
	}

	std::string generate(){
		char temp;
		std::string result;

		temp = rand()%26 + 97;

		do {
			std::vector<char> list;
			result.push_back( temp );
			for( auto i = mat[temp].begin(); i != mat[temp].end(); ++i ){
				for( int k = i->second; k > 0; --k ){
					list.push_back( i->first );
				}
			}
			if( list.size() != 0 )
				temp = list.at( rand()%list.size() );
			else
				temp = '\0';
		} while ( temp != '\0' );
		if( result.size() < MIN || result.size() > MAX )
			result = generate();
		result.at(0) = toupper( result.at(0) );
		return result;
	}

};

int main(){
	NameGenerator nam;
	srand( time(NULL) );
	while( !std::cin.eof() ){
		std::string temp;
		std::cin >> temp;
		nam.update(temp);
	}
	std::cout << nam.generate() << std::endl;
	return 0;
}
