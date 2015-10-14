#ifndef XMLPARSER
#define XMLPARSER
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using boost::property_tree::ptree;
using boost::property_tree::read_xml;

void
printData(const ptree& _pt){
  for(const auto& iter : _pt){
    std::cout << iter.first << '\n';
	if(iter.second.empty()){
		std::cout << iter.second.get_value<std::string>() << '\n';
	}
	if(iter.second.size()){
		printData(iter.second);
	}
  }
}

class Xml_Parser{
public:
  void readFile(const std::string& _fileName){
    if(_fileName.empty()) return;
    read_xml(_fileName, mXML);
    mReaded = true;
  }
  void read(const std::string& _tag, const std::string& _child, const std::string& _tagAttrb){
    if(mReaded){
		try{
			auto tags = mXML.get_child(_tag);
			for(const auto& iter : tags){
				const auto& child = iter.second.get_child("<xmlattr>");
				std::cout << '\t' << iter.first << '\n';
				for(const auto& iters : child){
					std::cout << "\t\t" << iters.first << '\n';
					std::cout << "\t\t" << iters.second.get_value<std::string>() << '\n';
				}
			}
		}
		catch(const std::exception& exp){
			std::cerr << exp.what() << '\n';
		}
    }
  }
  void write(const std::string& _tag, const std::string& _child, const std::string& _value){

  }
protected:
  bool mReaded = false;
  ptree mXML;
};

#endif // XMLPARSER

