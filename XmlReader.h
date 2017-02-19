#pragma once
#include "ITreeReader.h"


// XML implementation of a generic ITreeReader
class XmlReader : public ITreeReader
{
public:

	XmlReader();
	virtual ~XmlReader();

	virtual	void	ReadTree(std::istream& in_stream, NameValueTree& tree);

};