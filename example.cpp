#include "apriori.h"

int main(int argc, char const *argv[])
{
	// FILE* file_open_r = freopen(argv[1], "r", stdin);
	// FILE* file_open_w = freopen(argv[3], "w", stdout);
	// if(!(file_open_r && file_open_w)){
	// 	return 1;
	// }
	// std::ios_base::sync_with_stdio(false);std::cin.tie(NULL);
	float X = atof(argv[3])/100.0;
	apriori a;
	a.init(argv[1], X);
	a.generate_frequent_item_set();
	a.write_out(argv[2]);
	// std::cerr << "Min support: " << X << std::endl;

	// char input[MAX];
	// std::vector< std::vector<unsigned int> > T;
	// // std::ifstream::pos_type input_file_size = filesize(argv[1]);
	// T.reserve(MAX);
	// std::vector<unsigned int> items_count;
	// items_count.reserve(MAX);
	
	// std::cerr << "Reading input" << std::endl;
	// unsigned int count = 0;
	// while(std::cin.getline(input,MAX)){
	// 	T.push_back(std::vector<unsigned int>());
	// 	std::vector<unsigned int>& dummy = T.back();
	// 	unsigned int curr = 0;
	// 	unsigned int i = 0;
	// 	while(input[i] != 0){
	// 		while(input[i] != ' '){
	// 			curr *= 10;
	// 			curr += (input[i]-'0');
	// 			++i;
	// 		}
	// 		if(curr >= items_count.size()){
	// 			items_count.resize(curr+1, 0);
	// 		}
	// 		++items_count[curr];
	// 		dummy.push_back(curr);
	// 		curr = 0;
	// 		++i;
	// 	}
	// 	++count;
	// }
	// std::cerr << "Reading complete with count: " << count << " and distinct items: " << items_count.size() << std::endl;

	// unsigned int k = 1;
	// std::vector< unsigned int > f_k;
	// init(f_k, items_count, count, X);

	// for(k=1;f_k.size()>0;++k){
	// 	write_out(f_k, k);
	// 	std::vector< unsigned int > c_k = generate_candidate(f_k, k);
	// 	f_k.clear();
	// 	std::vector<unsigned int> items_count;
	// 	items_count.resize(c_k.size()/(k+1), 0);
	// 	filter_candidate(T, f_k, c_k, items_count, count, X, k+1);
	// }

	// std::cout.flush();
	// fclose(stdin);
	// fflush(stdout);
	// fclose(stdout);
	return 0;
}