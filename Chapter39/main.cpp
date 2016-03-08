#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <locale>
#include <iomanip> // put_time, this works from GCC 5 UPWARDS
#include <cstdint>
#include <limits>
#include <ctime>
#include <vector>
#include <iterator>

using namespace std;


/*
	locale()		current global locale, can be "C"
	locale("")		user preferred locale, can be en_EN.UTF-8
	locale::classic()	"C" locale
*/		

// time_put facet - for printing date time to ostream
class DecorativeTime : public time_put<char>
{
public:
	//static locale::id id; // dont define id as this facet should replace time_put facet-inherited id is needed
protected:
	// do_put does the job of inserting date time into stream
	iter_type do_put(iter_type out, 
				std::ios_base& str, 
				char_type fill, 
				const std::tm* t,
                          	char format, 
				char modifier ) const override
	{
		string S = " *** "; // decorative string
		copy(S.begin(), S.end(), out);	// start with decoration
		time_put<char>::do_put(out, str, fill, t, format, modifier); // print normal date time
		copy(S.begin(), S.end(), out);	// end with decoration
		return out;
	}
};

void timeputExample()
{
/*
	First - set the user preferred locale ie. taken from environment variables. Eg, printout from `locale` command.:
	LANG=en_US.UTF-8
	LANGUAGE=en_US
	LC_CTYPE="en_US.UTF-8"
	LC_NUMERIC=pl_PL.UTF-8
	LC_TIME=pl_PL.UTF-8
	LC_COLLATE="en_US.UTF-8"
	LC_MONETARY=pl_PL.UTF-8
	LC_MESSAGES="en_US.UTF-8"
	LC_PAPER=pl_PL.UTF-8
	LC_NAME=pl_PL.UTF-8
	LC_ADDRESS=pl_PL.UTF-8
	LC_TELEPHONE=pl_PL.UTF-8
	LC_MEASUREMENT=pl_PL.UTF-8
	LC_IDENTIFICATION=pl_PL.UTF-8
	LC_ALL=
*/
	auto &os = cout;	// convenience alias	
	os.imbue(locale(locale(""), new DecorativeTime));	// set preferred locale, substitute time_put facet with DecorativeTime
	ostream::sentry  ok(os);   // auto initialize - finalize stream (eg lock for multithreading)
    	if (!ok) return;

	// get current datetime 
	time_t t = time(0);

	// print the date
	os << "time_put facet: Decorative time print with put_time(time, %c) manipulator:\n";
	os << put_time(localtime(&t), "%c"); // this manipulator will use DecorativeTime facet to print time

	cout << endl << endl;
}


// seasons facet as an example of user defined facet
enum Season { SeasonBegin = 0, spring = 0, summer = 1, fall = 2, winter = 3, SeasonEnd = 4 };

// Abstract facet to be implemented by specific language facets
class AbstractSeason : public locale::facet {
public:
	virtual const string toString(Season season) const = 0;
	static locale::id id; // this id is needed to extract requested facet from locale with use_facet<Facet>(locale)
};
locale::id AbstractSeason::id;

// polish seasons
class PlSeason : public AbstractSeason {
public:
	const string toString(Season season) const override {
		string SEASONS[] = {"wiosna", "lato", "jesień", "zima"};
		return SEASONS[season];
	}
};	

// english seasons
class EnSeason : public AbstractSeason {
public:
	const string toString(Season season) const override {
		string SEASONS[] = {"spring", "summer", "fall", "winter"};
		return SEASONS[season];
	}
};

ostream& operator<<(ostream& os, Season season) {
	ostream::sentry ok(os);
	if (!ok) return os;

	auto &seasonFacet = use_facet<AbstractSeason>(os.getloc());
	return os << seasonFacet.toString(season);
}

void seasonfacetExample()
{
	cout << "Season facet.\nUse PlSeason:\n";
	cout.imbue(locale(locale(""), new PlSeason));
	for (unsigned s = SeasonBegin; s < SeasonEnd; s++)
		cout << Season(s) << " ";


	cout << "\nUse EnSeason:\n";
	cout.imbue(locale(locale(""), new EnSeason));
	for (unsigned s = SeasonBegin; s < SeasonEnd; s++)
		cout << Season(s) << " ";

	cout << endl << endl;
}



// collate facet - string comparison. collate can be inherited and reimplemented just as time_put
void collatefacetExample()
{
	vector<string> letters {"d", "a", "c", "b"};
	cout << "collate facet. sort letters: ";
	copy(letters.begin(), letters.end(), ostream_iterator<string>(cout, ","));
	locale comparator = cout.getloc(); // locale () operator is string comparison really
	sort(letters.begin(), letters.end(), comparator);
	cout << " -> ";
	copy(letters.begin(), letters.end(), ostream_iterator<string>(cout, ","));

	cout << endl << endl;
}


// numpunct facet - numbers formatting
class NicePunct : public numpunct<char> {
protected:
	char do_decimal_point() const override { return ','; }
	char do_thousands_sep() const override { return '\''; }
	string do_grouping() const override { return "\003"; }
};

void numpunctfacetExample()
{
	// print double in crazy format
	locale loc(locale(), new NicePunct);
	cout.imbue(loc);
	cout << fixed <<  setprecision(2) << "numpunct facet: dyskietka " << 999999999.99 << " gier";
	cout << endl;

	// can also read this crazy format
	istringstream ss ("1'900,99");
	cout << "Now, read this crazy format: " << ss.str() << " = ";
	ss.imbue(loc);
	double d;
	ss >> d;
	cout.imbue(locale("")); // reset cout locale
	cout << d << endl << endl;;
}

// There is more standard facets for putting/getting numbers in any format eg roman MMXVI, money, etc

int main()
{
	timeputExample();
	seasonfacetExample();
	collatefacetExample();
	numpunctfacetExample();
}	
