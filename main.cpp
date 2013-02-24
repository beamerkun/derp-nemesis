#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <ctype.h>
#define MIN 3
#define MAX 15


class NameGenerator{
	std::map< char, std::map< char, std::map< char, int > > > mat;

	public:

	void update( std::string str ){
		if( str.length() <= 0 )
			return;
		int* n = &mat[255][str[0]][str[1]];
		*n += 1;
		for( int i = 0; i <= str.length() - 2; ++i ){
			int* num = &mat[tolower(str[i])][str[i+1]][str[i+2]];
			*num += i;
		}
	}

	std::string generate(){
		char last, curr, next;
		std::string result;

		do {
			last = 255;

			std::vector<char> list;
			for( auto i = mat[last].begin(); i != mat[last].end(); ++i ){
				list.push_back(i->first);
			}
			curr = list.at( rand()%list.size() );

			do {
				result.push_back( last );

				for( auto i = mat[last].begin(); i != mat[last].end(); ++i ){
					auto matrix = i->second;
					for( auto j = matrix.begin(); j != matrix.end(); ++j){
						for( int k = j->second; k > 0; --k )
							list.push_back(j->first);
					}
				}

				if( list.empty() )
					next = '\0';
				else
					next = list.at( rand()%list.size() );

				last = curr;
				curr = next;
				list.clear();
			} while (last != '\0' || curr != '\0');
		} while ( result.size() < MIN || result.size() > MAX );

		result = result.substr( 1, result.size() -1 );
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
