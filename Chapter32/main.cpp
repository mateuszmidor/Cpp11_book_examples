#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <cctype> // toupper

using namespace std;

template <class T>
void println(const vector<T> &v)
{
	ostream_iterator<T> stdout_iterator(cout, ", ");
	copy(v.begin(), v.end(), stdout_iterator) ;
	cout << endl;
}

template <class T>
void commentPrintln(const string & comment, const vector<T> &c)
{
	cout << comment << endl;
	println(c);
	cout << endl;
}

template <class T>
void commentPrintln(const string & comment, T item)
{
	cout << comment << endl << item << endl << endl;
}
	
void nonmodifyingAlgorithmExample()
{
	vector<string> names {"Marcin", "Andrzej", "Gosia", "Justyna", "Radek", "Teresa"};
	commentPrintln("Working set: ", names);

	// copy
	decltype(names) copy_names(names.size());
	copy(names.begin(), names.end(), copy_names.begin());
	commentPrintln("1. copy:", copy_names);
		
	// sort
	sort(copy_names.begin(), copy_names.end());
	commentPrintln("2. sort:", copy_names);

	// sort predicate
	auto gender_sort_pred = [] (string a, string) { return *(a.end()-1) == 'a' ? 1 : 0; }; // ends with 'a' means girl 
	sort(copy_names.begin(), copy_names.end(), gender_sort_pred);
	commentPrintln("3. sort by gender:", copy_names);

	// find
	auto pos = find(names.begin(), names.end(), "Gosia") - names.begin();
	commentPrintln("4. find Gosia in names at position:", pos);

	// find_if (similar: find_if_not, find_first_of, adjecent_find, find_end)
	auto Aname_pred = [] (string s) { return s[0] == 'A'; };
	pos = find_if(names.begin(), names.end(), Aname_pred) - names.begin();
	commentPrintln("5. find_if name starts with A at position:", pos);

	// for_each
	auto print_quotated = [] (string s) { cout << "\"" << s << "\" "; };
	cout << "6. for_each print name in quotation marks:" << endl;
	for_each(names.begin(), names.end(), print_quotated);
	cout << endl << endl;

	// any_of (similar: all_of, none_of)
	auto startwithT_pred = [] (string s) { return s[0] == 'T'; };
	cout << boolalpha;
	commentPrintln("7. any_of the names starts with T:", any_of(names.begin(), names.end(), startwithT_pred));

	// count_if (similar: count) 
	auto isgirl_pred = [] (string s) { return s.back() == 'a' ? 1 : 0; }; // ends with 'a' means girl
	auto num_girls = count_if(names.begin(),names.end(), isgirl_pred);
	commentPrintln("8. count_if the total girl numer:", num_girls);

	// equal
	copy(names.begin(), names.end(), copy_names.begin());
	copy_names.back() = "Jola";
	cout << "9. equal:" << endl;
	println(names); 
	println(copy_names);
	cout << equal(names.begin(), names.end(), copy_names.begin()) << endl << endl;

	// mismatch
	decltype(names.begin()) p1, p2;
	tie(p1, p2) = mismatch( names.begin(), names.end(), copy_names.begin());
	cout << "10. mismatch at " << p1 - names.begin() << ", " << p2 - copy_names.begin() << endl << endl;

	// search
	string sequence { "http://www.multimedia.com" };
	string subsequence { "multimedia" };
	auto subseq_pos = search(sequence.begin(), sequence.end(), subsequence.begin(), subsequence.end()) - sequence.begin();
	commentPrintln("11. search " + subsequence + " in " + sequence + " and find it at position:", subseq_pos);
}

void modifyingAlghorithmExample()
{
	vector<string> names {"Marcin", "Andrzej", "Gosia", "Gosia", "Justyna", "Radek", "Teresa"};
	commentPrintln("Working set: ", names);

	// transform (also two-input iterators version exists)
	vector<string> result (names.size());
	auto toUpper = [] (string s) { transform(s.begin(), s.end(), s.begin(), ::toupper); return s; };
	transform(names.begin(), names.end(), result.begin(), toUpper);
	commentPrintln("1. transform names to uppercase:", result);
	
	// copy_if (similar: copy_n, for exact element count)
	auto is_boy = [] (string s) { return s.back() != 'a' ? 1 : 0; }; // ends with 'a' means girl
	result.clear();
	copy_if(names.begin(), names.end(), back_inserter(result), is_boy);
	commentPrintln("2. copy_if is a boy:", result); 

	// unique (similar: unique_copy)
	vector<string> names_copy (names);
	sort(names_copy.begin(), names_copy.end());
	auto unique_last = unique(names_copy.begin(), names_copy.end());
	result = vector<string>(names_copy.begin(), unique_last);
	commentPrintln( "3. unique names are: ", result);

	// remove - erase (similar: remove_if)
	result = vector<string>(names);
	auto nogosia_last = remove(result.begin(), result.end(), "Gosia");
	result.erase(nogosia_last, result.end());
	commentPrintln("4. remove-erase Gosia:", result);

	// reverse (similar: reverse_copy)
	result = vector<string>(names);
	reverse(result.begin(), result.end());
	commentPrintln("5. reverse names:", result);

	// replace (similar: replace_if, replace_copy, replace_copy_if)
	result = vector<string>(names);
	replace(result.begin(), result.end(), string("Gosia"), string("Viri"));
	commentPrintln("6. replace Gosia to Viri:", result);

	// rotate (similar: rotate_copy)
	result = vector<string>(names);
	rotate(result.begin(), result.begin() + 1, result.end()); // begin()+1 will become first elem
	commentPrintln("7. rotate names left:", result);

	// random_shuffle (similar: shuffle)
	result = vector<string>(names);
	random_shuffle(result.begin(), result.end());
	commentPrintln("8. random_shuffle the names:", result);

	// stable_partition (similar: partition, partition_copy, is_partitioned)
	result = vector<string>(names);
	stable_partition(result.begin(), result.end(), is_boy);
	commentPrintln("9. partition names by gender:", result);

	// next_permutation (similar: prev_permutation)
	cout << "10. generate permutations of abc:" << endl;
	string abc { "abc" };
	do 		
		cout << abc << ", ";
	while (next_permutation(abc.begin(), abc.end()));
	cout << endl << endl;

	// fill (similar: fill_n)
	result = vector<string>(names);	
	fill(result.begin(), result.end(), string("[EMPTY]"));
	commentPrintln("11. fill names with [EMPTY]:", result);

	// generate (similar: generate_n)
	result = vector<string>(names);
	auto generator = []() { static char letter = 'A'; return string(1, letter++); };
	generate(result.begin(), result.end(), generator);
	commentPrintln("12. generate subsequent letters A, B, C, ...", result);

	// partial_sort_copy (similar: sort, stable_sort, partial_sort, is_sorted, is_sorted_until)
	vector<int> top_sales { 13, 11, 6, 22, 9, 7, 3, 5, };
	vector<int> top_5(5);
	partial_sort_copy(top_sales.begin(), top_sales.end(), top_5.begin(), top_5.end(), greater<int>{});
	commentPrintln("13. partial_sort to figureout 5 highest numbers from 13, 4, 11, 6, 22, 7, 3, 5", top_5);			
	
	// lower bound, upper bound, binary search - the input must be sorted!
	vector<int> numbers { 1, 2, 3, 4, 4, 4, 6, 9 };
	cout << "The numbers are: ";
	println(numbers);
	cout << "14. lower_bound for 4 (ie. first occurence): " << lower_bound(numbers.begin(), numbers.end(), 4) - numbers.begin() << endl << endl;
	cout << "15. upper_bound for 4 (ie. first occurence of higher number): " << upper_bound(numbers.begin(), numbers.end(), 4) - numbers.begin() << endl << endl;
	cout << "16. binary_search for 4: " << binary_search(numbers.begin(), numbers.end(), 4) << endl << endl;
	
	// merge (similar: inplace_merge) - the inputs must be sorted!
	int series_a[] { 1, 2, 3 };
	int series_b[] { 4, 5, 6 };
	vector<int> merge_result;
	merge(begin(series_a), end(series_a), begin(series_b), end(series_b), back_inserter(merge_result));
	commentPrintln("17. merge of [1, 2, 3] and [4, 5, 6]:", merge_result);

	// set operations: +, -, *, xor
	int subset_a[] {1, 2};
	int set_a[] { 1, 2, 3 };
	int set_b[] { 3, 4, 5 };
	cout << "18. includes [1, 2] in [1, 2, 3]: " << includes(begin(set_a), end(set_a), begin(subset_a), end(subset_a)) << endl << endl;

	vector<int> union_result;
	set_union(begin(set_a), end(set_a), begin(set_b), end(set_b), back_inserter(union_result));
	commentPrintln("19. [1, 2, 3] or [3, 4, 5]: ", union_result);	

	vector<int> intersection_result;
	set_intersection(begin(set_a), end(set_a), begin(set_b), end(set_b), back_inserter(intersection_result));
	commentPrintln("20. [1, 2, 3] and [3, 4, 5]: ", intersection_result);	

	vector<int> difference_result;
	set_difference(begin(set_a), end(set_a), begin(set_b), end(set_b), back_inserter(difference_result));
	commentPrintln("21. [1, 2, 3] - [3, 4, 5]: ", difference_result);	

	vector<int> symmetric_difference_result;
	set_symmetric_difference(begin(set_a), end(set_a), begin(set_b), end(set_b), back_inserter(symmetric_difference_result));
	commentPrintln("22. [1, 2, 3] xor [3, 4, 5]: ", symmetric_difference_result);	
	
	// lexicographical_compare
	string s1 { "100" };
	string s2 { "99" };
	string s3 { "Zeta" };
	string s4 { "ALpha" };
	cout << "23. lexicographical_compare: '100' < '99': " << lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()) << endl;
	cout << "23. lexicographical_compare: 'Zeta' < 'Alpha': " << lexicographical_compare(s3.begin(), s3.end(), s4.begin(), s4.end()) << endl << endl;
	
	// min, max, minmax; this is too easy, skip demo

	// min_element, max_element (similar: minmax_element)
	vector<int> minmax_numbers { 1, 2, 9, 8, 5, 5 };
	cout << "The numbers are: ";
	println(minmax_numbers);
	cout << "24. min value : " << *min_element(minmax_numbers.begin(), minmax_numbers.end()) << endl;
	cout << "25. min position : " << min_element(minmax_numbers.begin(), minmax_numbers.end()) - minmax_numbers.begin() << endl;
	cout << "26. max value : " << *max_element(minmax_numbers.begin(), minmax_numbers.end()) << endl;
	cout << "27. max position : " << max_element(minmax_numbers.begin(), minmax_numbers.end()) - minmax_numbers.begin() << endl;
}

int main()
{
	nonmodifyingAlgorithmExample();
	modifyingAlghorithmExample();
}
