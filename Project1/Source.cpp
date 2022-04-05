/*
*	Author:	CS
*	Date:	2022_03_18	YYYY_MM_DD
*
*	- A mechanism of reading/writing orders to/from a file
*	- Printing orders	(uses same function as writing to file)
*	- Create a file of 10 Orders (file1.txt)
*	- Read it into std::vector<Order> orders
*	- Sort orders by name of customer and write it to a different file (file2.txt)
*   - Read 3 orders from file1.txt and add a further 6 to a new std::vector<Order> orders2
*	- Sort orders2 by address of customer and write orders2 to a file (file3.txt)
*	- Merge file2.txt and file3.txt using std::merge()
*	(Note in the question statement, the two files to be merged are sorted in different ways, the merge
*	is successful but has duplicates, one entry is missing)
* 
*	Improvement:
*	Consider convenient structure for input data before defining input operation,
*	using comma seperated values is a good approach.
*	Originally, the address was not written with spaces.
*	ie: TRY AND PLAN THINGS FROM THE USERS PERSPECTIVE
*	
*	Approach:
*	Purchase objects are convertible to bool, if there are no more to detect, a default object is returned which may be evaluated.
*	(This is used when scanning individual Order/Purchase objects.
* 
*	Lesson:
*	Tokenising input would allow me to incorporate more useful error messages
*	Split firstname/surname, address numbers, etc into seperate strings
*/

#include <iostream>
#include "Order_Purchase.h"
#include <iterator>	// for std::istream_iterator

int main() {
	try {
		// a file of 10 orders
		std::ifstream in{ "file1.txt" };

		// scanning orders from a file into a vector
		std::vector<Order> orders;
		Order temp;
		in >> temp;
		while (temp && in)
		{
			orders.push_back(temp);
			char ch;
			in >> ch;
			if (in)
			{
				in.putback(ch);
				in >> temp;
			}
		}

		// print orders to terminal
		for (auto elem : orders)
			std::cout << elem << std::endl;

		// sort orders by name of customer
		std::sort(orders.begin(), orders.end(), [](Order a, Order b) { return a.get_name() < b.get_name(); });

		// print orders to file2.txt
		std::ofstream outfile2{ "file2.txt" };
		for (auto elem : orders)
			outfile2 << elem << std::endl;


		// Read 3 orders from file1.txt and add a further 6 to a new std::vector<Order> orders2
		std::vector<Order> orders2;
		int count = 3;
		std::ifstream in_orders2{ "file1.txt" };
		for (int i = 0; i < count; i++){
			Order temp;
			in_orders2 >> temp;
			orders2.push_back(temp);
		}
		orders2.push_back(Order{ "1st of 6", "alpha Address 1", 10, std::vector<Purchase>() });
		orders2.push_back(Order{ "2nd of 6", "zulu Address 2", 20, std::vector<Purchase>() });
		orders2.push_back(Order{ "3rd of 6", "bravo Address 3", 30, std::vector<Purchase>() });
		orders2.push_back(Order{ "4th of 6", "xray Address 4", 40, std::vector<Purchase>() });
		orders2.push_back(Order{ "5th of 6", "charlie Address 5", 50, std::vector<Purchase>() });
		orders2.push_back(Order{ "6th of 6", "whiskey Address 6", 60, std::vector<Purchase>() });

		// sort orders2 by address of customer, and write to file
		std::sort(orders2.begin(), orders2.end(), [](Order a, Order b) { return a.get_address() < b.get_address(); });
		std::ofstream outfile3{ "file3.txt" };
		for (auto elem : orders2)
			outfile3 << elem << std::endl;

		// merge file2.txt and file3.txt using std::merge
		std::ifstream inputfile2{ "file2.txt" };
		std::ifstream inputfile3{ "file3.txt" };
		std::istream_iterator<Order> it_file2{ inputfile2 };
		std::istream_iterator<Order> it_file3{ inputfile3 };

		std::ofstream outputfile{ "file4.txt" };
		std::ostream_iterator<Order> it_output{ outputfile };

		// std::istream_iterator<*type*>() - default constructor is the past the end iterator
		std::merge(it_file2, std::istream_iterator<Order>(), it_file3, std::istream_iterator<Order>(), it_output);

	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}