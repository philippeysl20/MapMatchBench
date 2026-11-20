#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <expected>

using namespace std;

typedef struct algorithm_result {
    string algorithm_name;
    string trajectory_id;
    vector<int> matched_route;
    double execution_time;
    double preprocessing_time;
    double precision;
    double recall;
    double f1;
    int observation_count;
    double throughput;
} algorithm_result;

// The route variable should only be of type vector<int> if the road segment IDs are integers, otherswise change
// it to the appropriate type.
// Example: If the IDs are pointers, change it to: 'vector<double> route'.

// also note that it does not have to be 30 m noise. That is just a starting point.
// But change variable names accordingly.

std::expected<void, string> compare(algorithm_result result_1, algorithm_result result_2, vector<int> ground_truth, 
                                    unordered_map<string, double> experiment_conditions) { 
    // Validating values of passed variables
    if (result_1.algorithm_name.empty() || result_2.algorithm_name.empty())
        return std::unexpected("Error getting one or more names of the algorithms that are being compared.");

    if (!isfinite(result_1.execution_time) || !isfinite(result_2.execution_time))
        return std::unexpected("Passed execution times for the algorithms are not numbers or are infinite.");

    if (result_1.matched_route.empty() || result_2.matched_route.empty())
        return std::unexpected("No mathced routes given.");

    for (size_t i : result_1.matched_route) {
        if (result_1.matched_route[i] < 0)
        return std::unexpected("Element at index " + to_string(i) + " is negative for " + result_1.algorithm_name + " results.");
    }

    for (size_t i : result_2.matched_route) {
        if (result_2.matched_route[i] < 0)
            return std::unexpected("Element at index " + to_string(i) + " is negative for " + result_2.algorithm_name + " results.");
    }

    // If route is of type vector<double>:
    
    // for (size_t i : route) {
    //     if (!isinfite(route[i]))
    //     return std::unexpected("Element at index " + to_string(i) + " is not a number or infinite");
    //}

    if (result_1.trajectory_id.empty() || result_2.trajectory_id.empty()) 
        return std::unexpected("No trajectory IDs have been passed.");

    if (isnan(result_1.preprocessing_time) || isnan(result_2.preprocessing_time))
       return std::unexpected("Passed preprocessing time values are faulty (NaN)"); 

    if (experiment_conditions.empty())
        return std::unexpected("No experiment conditions have been given.");

    // following validations for experiment conditions can be changed and are just a guess at the conditions we would 
    // need for the tests/comparisons.
    if (experiment_conditions.find("noise") == experiment_conditions.end())
        return std::unexpected("No 'noise' experiment condition. This is needed");

    if (experiment_conditions.find("interval") == experiment_conditions.end())
        return std::unexpected("No 'inteval' experiment condition. This is needed");

    // Following code will implement the calculation of different metrics of route accuracy, computational efficiency, robustness and will MAYBE
    // compare multiple trajectories.
   
    // type double used to account for percentages that are not integers.
    double result_1_correctly_predicted_segments = 0;
    for (size_t i : result_1.matched_route) {
        if (result_1.matched_route[i] == ground_truth[i])
            result_1_correctly_predicted_segments++;
    }

    // precision for result result 1
    result_1.precision = result_1_correctly_predicted_segments / result_1.matched_route.size();
    
    double result_2_correctly_predicted_segments = 0;
    for (size_t i : result_2.matched_route) {
        if (result_2.matched_route[i] == ground_truth[i]) 
            result_2_correctly_predicted_segments++;
    }

    // precision for result 2 
    result_2.precision = result_2_correctly_predicted_segments / result_2.matched_route.size();

    // Recall for both results
    result_1.recall = result_1_correctly_predicted_segments / ground_truth.size();
    result_2.recall = result_2_correctly_predicted_segments / ground_truth.size();

    // F1
    result_1.f1 = 2 * (result_1.precision * result_1.recall) / (result_1.precision + result_1.recall);
    result_2.f1 = 2 * (result_2.precision * result_2.recall) / (result_2.precision + result_2.recall);

    // Speedup
    double speedup = result_1.execution_time / result_2.execution_time; // Tells how many times faster or slower one algorithm is than the other.

    // throughput
    result_1.throughput = result_1.observation_count / result_1.execution_time;
    result_2.throughput = result_2.observation_count / result_2.execution_time;

    // next is robustness.


    // Successful run.
    return std::expected<void, string>{};
}
