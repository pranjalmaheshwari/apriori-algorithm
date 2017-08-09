#ifndef APROIRI_H
#define APROIRI_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
// #include <assert.h>

#ifdef PARALLEL_MODE
#include <omp.h>
#define NUM_THREADS 4
#endif

class apriori
{
	// vars
	float X;// support for frequent itemsets in terms of fraction
	unsigned int count;
	std::vector< std::vector<unsigned int> > T;
	std::vector<unsigned int> items_count;
	std::vector<std::vector< unsigned int >> f;
	// func
	void first_pass(std::vector< unsigned int >& f_k);
	bool is_contained(std::vector<unsigned int>::iterator c, std::vector<unsigned int>& v, unsigned int& k1);
	std::vector< unsigned int > generate_candidate(std::vector< unsigned int >& f_k, unsigned int& k);
	void filter_candidate(std::vector< unsigned int >& f_k, std::vector<unsigned int>& c_k, std::vector<unsigned int>& items_count, unsigned int k);
public:
	apriori(){}
	~apriori(){}
	apriori(std::string input_file, float X);
	bool init(std::string input_file, float X);
	bool generate_frequent_item_set();
	bool write_out(std::string output_file);
};

#endif
