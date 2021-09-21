#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

void merge(std::vector<int>& nums, size_t start, size_t end, size_t middle);
void merge_sort(std::vector<int>& nums, size_t start, size_t end);
int binary_search(std::vector<int> nums, size_t start, size_t end, int target, size_t exception);
std::vector<int> two_sum(std::vector<int>& nums, int target);

int binary_search(std::vector<int> nums, size_t start, size_t end, int target, size_t exception){
    size_t middle = start + ((end-start)/2);
    if (middle < 0 || middle >= nums.size()){
        return -1;
    }
    else if(nums[middle] > target){
        return binary_search(nums, start, middle-1, target, exception);
    }
    else if(nums[middle] < target){
        return binary_search(nums, middle+1, end, target, exception);
    }
    else if(nums[middle] == target && middle != exception){
        return middle;
    }
    else if(nums[middle] == target && middle == exception){
        if(middle == 0 && nums[middle+1] == target){
            return middle+1;
        }
        else if(middle == nums.size() && nums[middle-1] == target){
            return middle-1;
        }
        else if(nums[middle+1] == target){
            return middle+1;
        }
        else if(nums[middle-1] == target){
            return middle-1;
        }
    }
    return -1;
}

void merge (std::vector<int>& nums, size_t start, size_t end, size_t middle){
    std::vector<int> left_vector;
    std::vector<int> right_vector;
    for (auto i = start; i <= middle; i++){
        left_vector.push_back(nums[i]);        
    }
    for (auto i = middle+1; i <= end; i++){
        right_vector.push_back(nums[i]);
    }
    //using finger algorithm  
    size_t left_vector_index = 0;
    size_t right_vector_index = 0;
    size_t nums_index = start;
    while (left_vector_index < left_vector.size() && right_vector_index < right_vector.size()){
        if(left_vector[left_vector_index] <= right_vector[right_vector_index]){
            nums[nums_index] = left_vector[left_vector_index];
            left_vector_index++;
            nums_index++;
        }
        else{
            nums[nums_index] = right_vector[right_vector_index];
            right_vector_index++;
            nums_index++;
        }
    }
    //copy left-over elements
    //left to right
    while (left_vector_index < left_vector.size()){
        nums[nums_index] = left_vector[left_vector_index];
        left_vector_index++;
        nums_index++;
    }
    while (right_vector_index < right_vector.size()){
        nums[nums_index] = right_vector[right_vector_index];
        right_vector_index++;
        nums_index++;
    }
}

void merge_sort (std::vector<int>& nums, size_t start, size_t end){
    if (start >= end){ 
        return;
    }
    size_t middle = start + ((end-start)/2);
    merge_sort(nums, start, middle);
    merge_sort(nums, middle+1, end);
    merge(nums, start, end, middle);
}

std::vector<int> two_sum(std::vector<int>& nums, int target){
    std::vector<int> original;
    for(size_t i = 0; i < nums.size(); i++){
        original.push_back(nums[i]);
    }
    std::vector<int> result;
    merge_sort(nums, 0, nums.size() -1 );
    for(size_t i = 0; i < nums.size(); i++){
        int left_part = nums[i];
        int right_part = target - left_part;
        if(binary_search(nums, 0, nums.size()-1, right_part, i) != -1){
            result.push_back(nums[i]);
            result.push_back(nums[binary_search(nums, 0, nums.size()-1, right_part, i)]);
            break;
        }
        else continue;
    }
    if(result.size() == 0){
        return result;
    }
    std::vector<int> index_result;
    for(size_t i = 0; i < nums.size(); i++){
        if(original[i] == result[0] || original[i] == result[1]){
            index_result.push_back(i);
            continue;
        } 
    }

    return index_result;
}

int main(){
    std::vector<int> test;
    test.push_back(2);
    test.push_back(3);
    test.push_back(4);
    vector<int> result = two_sum(test, 6);
    for(size_t i = 0; i < result.size(); i++){
        std::cout << result[i] << " ";
    }
    return 0;
}
