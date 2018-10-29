#include "ch16_template-flip.h"

// int -> string -> pair<int,string>
pair<int, string> neg(int& i, string& s)
{
	return make_pair(i, s);
}



void main_flip()
{
	string str = "love";
	int in = 5;
	auto r = flip(neg, str, in);
	system("pause");
}