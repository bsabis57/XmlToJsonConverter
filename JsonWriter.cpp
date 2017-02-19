#include "stdafx.h"

#include "JsonWriter.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <ostream>


// factory function for an instance of an Xml Reader
std::shared_ptr<ITreeWriter>	 ITreeWriter::NewJsonWriter()
{
	return std::make_shared<JsonWriter>();
}


JsonWriter::JsonWriter()
{
}

JsonWriter::~JsonWriter()
{
}


void	JsonWriter::WriteTree(const NameValueTree& tree, std::ostream& out_stream)
{
	using namespace boost::property_tree;
	try
	{
		write_json(out_stream, tree);
	}
	catch (json_parser_error&)
	{
		// for now, just throw a WriterException
		throw WriterException();
	}
}

