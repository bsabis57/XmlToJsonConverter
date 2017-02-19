#pragma once
#include "ITreeWriter.h"


// JSON implementation of a generic ITreeWriter
class JsonWriter : public ITreeWriter
{
public:

	JsonWriter();
	virtual ~JsonWriter();

	virtual void	WriteTree(const NameValueTree& tree, std::ostream& out_strream);
};