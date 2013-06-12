#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

string rleText(char* t)
{
	string s(t);
	string ret = "";
	int i = 0;
	int c = 0;
	
	while(i < s.size())
	{
		if(isdigit(s.at(i)))
		{
			c = s.at(i) - 0x30;
			
			if((i+1 < s.size()) && (i+2 < s.size()) && s.at(i+1) == '@')
			{
				for(int a = 0; a < c; a++)
				{
					ret.push_back(s.at(i+2));
				}
				
				i+=2;
			}
			else
			{
				ret.push_back(s.at(i));
			}
			c=0;
		}
		else
		{
			ret.push_back(s.at(i));
		}
		
		i++;
	}
	return ret;
}

void rleFile(char* t)
{
	string fn(t);
	fn+=".dec";
	ifstream in(t, ios::in);
	ofstream out(fn.c_str(), ios::out | ios::trunc);
	
	if(in && out)
	{
		string s;
		while(getline(in, s))
		{
			s[s.size()] = '\0';
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

int sizeEntry(char* t)
{
	return 0;
}

void printHelp()
{
	cout << "Usage :\n" << "-t [TEXTE]\n" << "-f [FILE]" << std::endl;
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
			//cout << "Compression de " << std::setprecision(2)  << ((double)rleText(argv[2]).size()/sizeEntry(argv[2]))*100 << "%" << endl;
		break;
		
		default:
			cout << "Unknow option \"" << argv[1] << "\"" << endl;
			printHelp();
		break;
	}

	return 0;
}