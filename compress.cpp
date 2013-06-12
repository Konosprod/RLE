#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

string rleText(char* t);

void printHelp()
{
	cout << "Usage :\n" << "-t [TEXTE]\n" << "-f [FILE]" << std::endl;
}

void rleFile(char* t)
{
	string fn(t);
	fn+=".rle";
	ifstream in(t, ios::in);
	ofstream out(fn.c_str(), ios::out | ios::trunc);
	
	if(in && out)
	{
		string s;
		while(getline(in, s))
		{
			char *p= strdup(s.c_str());	
			out << rleText(p) << endl;
			free(p);
		}
	}
	else
	{
		cerr << "Erreur à l'ouverture ou à la création du fichier" << endl;
	}
		
}

string rleText(char* t)
{
	string s2(t);
	string s;
	int c = 1;
	int i = 1;
	
	
	while(i <= s2.size())
	{
		while(s2[i-1] == s2[i] && i < s2.size())
		{
			c++;
			i++;
		}
		if(c > 10)
		{
			while(c > 9)
			{
				s.push_back(9+0x30);
				s.push_back('@');
				s.push_back(s2[i-1]);
				c-=9;
			}
			
			s.push_back(c+0x30);
			s.push_back('@');
			s.push_back(s2[i-1]);
		}
		else if(c > 2)
		{
			s.push_back(c+0x30);
			s.push_back('@');
			s.push_back(s2[i-1]);
		}
		else
		{
			if(c == 2)
			{
				s.push_back(s2[i-2]);
			}
			s.push_back(s2[i-1]);
		}
		c=1;
		i++;
	}
	
	return s;
}

int sizeEntry(char* t)
{
	string s(t);
	
	return s.size();
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printHelp();
	}
	
	switch(argv[1][1])
	{
		case 'f':
			rleFile(argv[2]);
		break;
		
		case 't':
			cout << rleText(argv[2]) << endl;
			cout << "Compression de " << std::setprecision(2)  << ((double)rleText(argv[2]).size()/sizeEntry(argv[2]))*100 << "%" << endl;
		break;
		
		default:
			cout << "Unknow option \"" << argv[1] << "\"" << endl;
			printHelp();
		break;
	}
		
	
	return 0;
}