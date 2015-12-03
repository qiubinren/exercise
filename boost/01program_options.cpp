#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
	int level;
	po::options_description myOptions("command line options by bujian");
	myOptions.add_options()
	("help,h","Produce help message")
	("level",po::value<int>(& level)->default_value(5));
	po::variables_map vmap;
	po::store(po::parse_command_line(argc,argv,myOptions), vmap);
	po::notify(vmap);
	if(vmap.count("help"))
	{
		std::cout<<myOptions<<std::endl;
		return 1;
	}
	if(vmap.count("level"))
	{
		level = vmap["level"].as<int>();
		std::cout<<"Int: "<<level<<std::endl;
	}
}
