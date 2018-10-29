#include "prelude.h"
#include <boost/version.hpp>
#include <boost/config.hpp>

void main_version()
{
	cout << BOOST_VERSION << endl;
	cout << BOOST_LIB_VERSION << endl;
	cout << BOOST_PLATFORM << endl;
	cout << BOOST_COMPILER << endl;
	cout << BOOST_STDLIB << endl;
	system("pause");
}