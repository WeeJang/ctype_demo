#include <string>
#include <vector>
#include <iostream>


enum class Direction : uint8_t {
	Diagonal,Row,Column
};

struct LCSCell{


public:
	Direction backtrack_direction;
	uint64_t  common_length;
};

/*
* 'i' : str_1 pos , 'j': str_2 pos
*  LCS[i][j] = max{LCS[i-1][j-1] + is_same(i,j),LCS[i][j-1],LCS[i-1][j]}
*/
int inner_LCS_finder(const std::wstring& str_1,const std::wstring& str_2,std::wstring& LCS_result){
	if(str_1.size() == 0 || str_2.size() == 0){
		return 0;
	}
	size_t str_1_length = str_1.size();
	size_t str_2_length = str_2.size();
		
	auto is_same = [&str_1,&str_2](size_t x,size_t y) -> uint8_t{
			if(str_1[x] == str_2[y]){
				return 1;
			}else{
				return 0;
			}
	};

	//LCSCell mid_cal_table[str_1_length][str_2_length];
	std::vector<std::vector<LCSCell>> mid_cal_table(str_1_length,std::vector<LCSCell>(str_2_length));
	auto get_cal_table_common_length = [&mid_cal_table](int x,int y) -> uint64_t{
		if(x < 0 || y < 0){
			return 0;
		}
		return mid_cal_table[x][y].common_length;
	};

	for(int i = 0 ; i < str_1_length ; i++){
		for(int j = 0 ; j < str_2_length ; j ++){
			mid_cal_table[i][j] = LCSCell();
			Direction max_back_direc = Direction::Diagonal;
			size_t max_com_len = get_cal_table_common_length(i-1,j-1) + is_same(i,j);
			
			if(max_com_len <= get_cal_table_common_length(i-1,j)){
				max_com_len = get_cal_table_common_length(i-1,j);
				max_back_direc = Direction::Column;
			}
			if(max_com_len <= get_cal_table_common_length(i,j-1)){
				max_com_len = get_cal_table_common_length(i,j-1);
				max_back_direc = Direction::Row;
			}
			mid_cal_table[i][j].backtrack_direction = max_back_direc;
			mid_cal_table[i][j].common_length = max_com_len;
			if(max_back_direc == Direction::Diagonal){
				std::cout << "*" ;
			}
			else if(max_back_direc == Direction::Row){
				std::cout << "-" ;
			}else if(max_back_direc == Direction::Column){
				std::cout << "|" ;
			}
		}
		std::cout << std::endl;
	}
	
	std::wstring result_buffer;
	int64_t i = str_1_length -1,j = str_2_length -1;
	//Direction cur_back_direc = mid_cal_table[i][j].backtrack_direction;	
	Direction cur_back_direc;
	do{
		cur_back_direc = mid_cal_table[i][j].backtrack_direction;	
		if(cur_back_direc == Direction::Diagonal){
			std::cout << i << ":" << j << ":" << "*" << std::endl;
			result_buffer.append(&str_2[j],0,1);
			i --; 
			j --;
		}else if(cur_back_direc == Direction::Row){
			std::cout << i << ":" << j << ":" << "-" << std::endl;
			j --;
		}else{
			std::cout << i << ":" << j << ":" << "|" << std::endl;
			i --;
		}
	}while(i >= 0 && j >= 0);
	//std::cout << result_buffer.size() << std::endl;
	std::wstring reverse_result_buffer(result_buffer.rbegin(),result_buffer.rend());
	LCS_result = reverse_result_buffer;
	return LCS_result.size();
}

extern "C" int LCS_finder(const wchar_t* p_str_1,const wchar_t* p_str_2,wchar_t* const p_LCS_result){
	std::wstring result;
	int result_len = inner_LCS_finder(std::wstring(p_str_1),std::wstring(p_str_2),result);
	if(result_len > 0){
		result.copy(p_LCS_result,result_len);
	}
	return result_len;
}

