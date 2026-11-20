#include <string>
#include <vector>
#include <unordered_map>
#include <expected>

using namespace std;

typedef struct algorithm_result algorithm_result;

std::expected<void, string> compare(algorithm_result result_1, algorithm_result result_2, vector<int> ground_truth,
                                    unordered_map<string, double> experiment_conditions);
