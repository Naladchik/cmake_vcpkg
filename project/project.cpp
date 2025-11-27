#include <iostream>
#include <chrono>
#include <thread>
#include <boost/program_options.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

namespace po = boost::program_options;
namespace ip = boost::interprocess;

int main(int argc, char* argv[])
{
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("source", po::value<std::string>(), "set file to copy from")
        ("destination", po::value<std::string>(), "set file to copy to")
        ("memory", po::value<std::string>(), "name of shared memory object")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    if (!vm.count("source")) {
        std::cout << "Source file was not set." << std::endl;
    }
    else if (!vm.count("destination")) {
        std::cout << "Destination file was not set." << std::endl;
    }
    else if (!vm.count("memory")) {
        std::cout << "Memory name was not set." << std::endl;
	}
    else {
        std::cout << std::endl;
        /*std::cout << "Source: " << vm["source"].as<std::string>() << std::endl;
		std::cout << "Destination: " << vm["destination"].as<std::string>() << std::endl;
		std::cout << "Memory: " << vm["memory"].as<std::string>() << std::endl;*/

        // ============== MAIN LOGIC IS HERE ======================================

        constexpr unsigned int CREATOR = 0;
        constexpr unsigned int USER = 1;
		int role = CREATOR; // 0 - creator, 1 - user

        try {
            ip::shared_memory_object shm(
                ip::create_only,
                vm["memory"].as<std::string>().c_str(),
                ip::read_write
            );
            std::cout << "Memory object created. " << std::endl;
        }
        catch (const ip::interprocess_exception& ex) {
            ip::shared_memory_object shm_obj(
                ip::open_only,
                vm["memory"].as<std::string>().c_str(),
                ip::read_write
            );
            std::cout << "Memory object opened. " << std::endl;
			role = 1;
		}

        if(USER == role){
            for(int i = 0; i < 1000; ++i){
                // Simulate work
                //std::this_thread::sleep_for(std::chrono::microseconds(1));
			}
            ip::shared_memory_object::remove(vm["memory"].as<std::string>().c_str());
            std::cout << "Memory object removed. " << std::endl;
        }else {
			std::cout << "User role, not removing memory object. " << std::endl;
        }
    }

    return 0;
}