#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\..\ITreeReader.h"

#include <sstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReaderTest
{
	// test xml file 
	std::string	xmlOK =
		"<?xml version = \"1.0\"?>"
		"<catalog>"
		"<book id = \"bk101\">"
		"<author>Gambardella, Matthew</author>"
		"<title>XML Developer's Guide</title>"
		"<genre>Computer</genre>"
		"<price>44.95</price>"
		"<publish_date>2000 - 10 - 01</publish_date>"
		"</book>"
		"</catalog>";
	
	// test xml file with error
	std::string	illFormedOK =
		"< ? xml version = \"1.0\"?>"
		"<catalog>"
		"<book id = \"bk101\">"
		"<author>Gambardella, Matthew</author>"
		"<title>XML Developer's Guide</title>"
		"<genre>Computer</genre>"
		"<price>44.95</price>"
		"<publish_date>2000 - 10 - 01</publish_date>"
		"<book>"
		"</catalog>";

	TEST_CLASS(UnitTest1)
	{
	public:
		
		// Instantiates a Reader
		TEST_METHOD(InstantiateReader)
		{
			auto pReader = ITreeReader::NewXmlReader();
			Assert::IsNotNull(pReader.get());
		}

		// XmlRead -- reads in an xml file, validates a field
		TEST_METHOD(ReadXml)
		{
			auto pReader = ITreeReader::NewXmlReader();
			std::istringstream  sstr(xmlOK);
			NameValueTree		tree;
			pReader->ReadTree(sstr, tree);
			auto& pChild = tree.get_child("catalog.book.genre");
			Assert::AreEqual(pChild.data().c_str(), "Computer");
		}

		// XmlFail -- Reads in an ill formed xml file, should throw an exception
		TEST_METHOD(XmlFail)
		{
			auto pReader = ITreeReader::NewXmlReader();
			std::istringstream  sstr(illFormedOK);
			NameValueTree		tree;
			Assert::ExpectException<ReaderException>([&] {pReader->ReadTree(sstr, tree); });
		}

	};
}