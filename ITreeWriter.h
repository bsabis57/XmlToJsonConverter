#pragma once

#include "NameValueTree.h"
#include <memory>

// stub for WriterException -- can be fleshed out if
// error reporting requirements are known
class WriterException : public std::exception
{
};

class ITreeWriter
{
public:
	virtual ~ITreeWriter() {};

	virtual void	WriteTree(const NameValueTree& tree, std::ostream& out_strream) = 0;


	// factory functions for various implementations
	static std::shared_ptr<ITreeWriter>	 NewJsonWriter();
};