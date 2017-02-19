#pragma once

#include "NameValueTree.h"
#include <memory>

// stub for ReaderException -- can be fleshed out if
// error reporting requirements are known
class ReaderException : public std::exception
{
};

class ITreeReader
{
public:
	virtual ~ITreeReader() {};

	virtual  void	ReadTree(std::istream& in_stream, NameValueTree& tree) = 0;

	// factory functions for various implementations
	static std::shared_ptr<ITreeReader>	 NewXmlReader() ;
};