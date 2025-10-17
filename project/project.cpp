#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main()
{
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("compression", po::value<int>(), "set compression level")
        ;

    std::cout<<"Hello World!"<<std::endl;
    return 0;
}