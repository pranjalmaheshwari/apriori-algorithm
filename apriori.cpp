#include "apriori.h"

void apriori::first_pass(std::vector< unsigned int >& f_k){
	for(auto it = items_count.begin(); it != items_count.end(); ++it){
		if(((float)*it)/count >= X){
			f_k.push_back(it - items_count.begin());
		}
	}
}

bool apriori::is_contained(std::vector<unsigned int>::iterator c, std::vector<unsigned int>& v, unsigned int& k1){
	unsigned int k2 = v.size();
	unsigned int i1 = 0;
	unsigned int i2 = 0;
	while(i1 < k1 && i2 < k2){
		if((*c) == v[i2]){
			++c;
			++i1;
		}
		++i2;
	}
	return (i1 == k1);
}

std::vector< unsigned int > apriori::generate_candidate(std::vector< unsigned int >& f_k, unsigned int& k){
	// assert(f_k.size()%k == 0);
	std::vector< unsigned int > ret;
	for(auto f1 = f_k.begin(); f1 != f_k.end(); f1+=k){
		for(auto f2 = f1+k; f2 != f_k.end(); f2+=k){
			bool same_k_1 = true;
			for (unsigned int i = 0; i < (k-1); ++i){
				if(*(f1+i) != *(f2+i)){
					same_k_1 = false;
					break;
				}
			}
			if(same_k_1){
				// assert(*(f1+(k-1)) < *(f2+(k-1)));
				for (unsigned int i = 0; i < (k-1); ++i){
					ret.push_back(*(f1+i));
				}
				ret.push_back(*(f1+(k-1)));
				ret.push_back(*(f2+(k-1)));
			}
			else{
				break;
			}
		}
	}
	return ret;
}

void apriori::filter_candidate(std::vector< unsigned int >& f_k, std::vector<unsigned int>& c_k, std::vector<unsigned int>& items_count, unsigned int k){
	#ifdef PARALLEL_MODE
		omp_lock_t writelock[c_k.size()];
		for(int i = 0;i<c_k.size();++i){
			omp_init_lock(&writelock[i]);
		}
	#endif
	#pragma omp parallel for
	for(unsigned int i = 0; i < T.size(); ++i){
		for(auto c = c_k.begin(); c != c_k.end(); c+=k){
			if(is_contained(c, T[i], k)){
				unsigned int temp = (c - c_k.begin())/k;
				#ifdef PARALLEL_MODE
				omp_set_lock(&writelock[temp]);
				#endif
				++items_count[temp];
				#ifdef PARALLEL_MODE
				omp_unset_lock(&writelock[temp]);
				#endif
			}
		}
	}
	#ifdef PARALLEL_MODE
	for(int i = 0;i<c_k.size();++i){
		omp_destroy_lock(&writelock[i]);
	}
	#endif
	for(auto it = items_count.begin(); it != items_count.end(); ++it){
		if(((float)*it)/count >= X){
			for (int i = 0; i < k; ++i){
				f_k.push_back(*(c_k.begin()+((it - items_count.begin())*k+i)));
			}
		}
	}
}

apriori::apriori(std::string input_file, float X){
	init(input_file, X);
}

bool apriori::init(std::string input_file, float X){
	#ifdef PARALLEL_MODE
		omp_set_num_threads(NUM_THREADS);
	#endif
	this->X = X;
	std::fstream fs(input_file, std::fstream::in);
	if(!fs.is_open()){
		return false;
	}
	count = 0;
	std::string input;
	while(getline(fs,input)){
		T.push_back(std::vector<unsigned int>());
		std::vector<unsigned int>& dummy = T.back();
		unsigned int curr = 0;
		unsigned int i = 0;
		while(i < input.size()){
			while(input[i] != ' '){
				curr *= 10;
				curr += (input[i]-'0');
				++i;
			}
			if(curr >= items_count.size()){
				items_count.resize(curr+1, 0);
			}
			++items_count[curr];
			dummy.push_back(curr);
			curr = 0;
			++i;
		}
		std::sort(dummy.begin(),dummy.end());
		++count;
	}
	fs.close();
	return true;
}

bool apriori::generate_frequent_item_set(){
	unsigned int k = 1;
	f.push_back(std::vector< unsigned int >());
	first_pass(f.back());

	for(k=1;f.back().size()>0;++k){
		// write_out(f_k, k);
		std::vector< unsigned int > c_k = generate_candidate(f.back(), k);
		std::vector<unsigned int> items_count;
		items_count.resize(c_k.size()/(k+1), 0);
		f.push_back(std::vector< unsigned int >());
		filter_candidate(f.back(), c_k, items_count, k+1);
	}
	f.pop_back();
	return true;
}

bool apriori::write_out(std::string output_file){
	std::fstream fs(output_file, std::fstream::out);
	if(!fs.is_open()){
		return false;
	}
	for(unsigned int k = 1;k<=f.size();++k){
		for(auto p = f[k-1].begin(); p != f[k-1].end(); p+=k){
			for (unsigned int i = 0; i < k; ++i){
				fs << *(p+i) << " ";
			}
			fs << "\n";
		}
	}
	fs.close();
	return true;
}

