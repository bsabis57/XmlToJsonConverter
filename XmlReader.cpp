#include "XmlReader.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <sstream>

// factory function for an instance of an Xml Reader
std::shared_ptr<ITreeReader>	 ITreeReader::NewXmlReader()
{
	return std::make_shared<XmlReader>();
}



XmlReader::XmlReader()
{
}

XmlReader::~XmlReader()
{
}


// Read function populates a PTree from an input stream
void	XmlReader::ReadTree(std::istream& in_stream, NameValueTree& tree)
{
	using namespace boost::property_tree;
	try
	{
		// NOTE: Need trim_whitespace flag to prevent subsequent errors with writing
		xml_parser::read_xml(in_stream, tree, xml_parser::trim_whitespace);
	}
	catch (xml_parser::xml_parser_error& )
	{
		throw ReaderException();
	}
}
