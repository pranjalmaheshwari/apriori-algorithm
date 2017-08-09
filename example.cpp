#include "apriori.h"

int main(int argc, char const *argv[])
{
	float X = atof(argv[3])/100.0;
	apriori a(argv[1], X);
	a.generate_frequent_item_set();
	a.write_out(argv[2]);
	return 0;
}
