#include <pybind11/pybind11.h>
#include "MapMatchBench.hpp"

namespace py = pybind11;

PYBIND11_MODULE(compare, pybind_module, py::mod_gil_not_used()) {
    pybind_module.def("compare", &compare, "The entry point for the MapMatchBench framework, that compares the results of two different map matching algorithms");
}
