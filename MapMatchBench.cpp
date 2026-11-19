#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <expected>

using namespace std;

// The route variable should only be of type vector<int> if the road segment IDs are integers, otherswise change
// it to the appropriate type.
// Example: If the IDs are pointers, change it to: 'vector<double> route'.

// also note that it does not have to be 30 m noise. That is just a starting point.
// But change variable names accordingly.

std::expected<void, string> compare(string algorithm_name_1, string algorithm_name_2, double algo1_accuracy, 
             double algo1_execution_time, double algo1_30m_noise_acc, double algo2_accuracy, 
             double algo2_execution_time, double algo2_30m_noise_acc, string trajectory_id,
             vector<int> route, double algo1_preprocessing_time, double algo2_preprocessing_time,
             unordered_map<string, double> experiment_conditions) {
    
    // Validating values of passed variables
    if (algorithm_name_1.empty() || algorithm_name_2.empty())
        return std::unexpected("Error getting one or more names of the algorithms that are being compared.");

    if (isnan(algo1_accuracy) || isnan(algo2_accuracy))
       return std::unexpected("Passed accuracy values are faulty (NaN)"); 

    if (algo1_accuracy < 0 && algo1_accuracy > 100 || algo2_accuracy < 0 && algo2_accuracy > 100)
        return std::unexpected("Passed accuracy is out of possible range (<0 or >100)");

    if (!isfinite(algo1_execution_time) || !isfinite(algo2_execution_time))
        return std::unexpected("Passed execution times for the algorithms are not numbers or are infinite.");

    if (route.empty())
        return std::unexpected("vector is empty");

    for (size_t i : route) {
        if (route[i] < 0)
        return std::unexpected("Element at index " + to_string(i) + " is negative");
    }

    // If route is of type vector<double>:
    
    // for (size_t i : route) {
    //     if (!isinfite(route[i]))
    //     return std::unexpected("Element at index " + to_string(i) + " is not a number or infinite");
    //}

    if (trajectory_id.empty()) 
        return std::unexpected("No trajectory ID has been passed.");

    if (isnan(algo1_30m_noise_acc) || isnan(algo2_30m_noise_acc))
       return std::unexpected("Passed 30 m noise accuracy values are faulty (NaN)"); 

    if (algo1_30m_noise_acc < 0 && algo1_30m_noise_acc > 100 || algo2_30m_noise_acc < 0 && algo2_30m_noise_acc > 100)
        return std::unexpected("Passed 30 m noise accuracy is out of possible range (<0 or >100)");

    if (isnan(algo1_preprocessing_time) || isnan(algo2_preprocessing_time))
       return std::unexpected("Passed preprocessing time values are faulty (NaN)"); 

    if (experiment_conditions.empty())
        return std::unexpected("No experiment conditions have been given.");

    // following validations for experiment conditions can be changed and are just a guess at the conditions we would 
    // need for the tests/comparisons.
    if (experiment_conditions.find("noise") == experiment_conditions.end())
        return std::unexpected("No 'noise' experiment condition. This is needed");

    if (experiment_conditions.find("interval") == experiment_conditions.end())
        return std::unexpected("No 'inteval' experiment condition. This is needed");

    

    // Successful run.
    return std::expected<void, string>{};
}
