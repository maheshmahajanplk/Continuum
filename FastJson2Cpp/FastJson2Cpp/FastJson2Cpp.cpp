// FastJson2Cpp.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}
//



#include "CParserJson.h"

#include <iostream>

// json data to c-structure

typedef struct{
	CParserVarNumber<_CONST_CHAR("length")>  m_length;
	CParserVarBool<_CONST_CHAR("use_space")> m_use_space;
}tIdent;

typedef struct
{
    // Default encoding for text
    CParserVarString<_CONST_CHAR("encoding")> 		m_encoding;
	
    // Example number
    CParserVarNumber<_CONST_CHAR("number")> 		m_number;
	
    // Plug-ins loaded at start-up
    CParserVarArrayString<_CONST_CHAR("plug-ins")> 	 m_plugins;
        
    // Tab indent size
    CParserVarPropertyGroup<tIdent,_CONST_CHAR("indent")> m_indent;
}tSampleJson;


int main(int argc, char *argv[]){

	std::cout << "FastJsonC++ ver. "<< FASTJSON_MAJOR_VERSION << "." << FASTJSON_MINOR_VERSION << "."<<FASTJSON_PATCH_VERSION << std::endl;
	if(argc <=1){
		std::cerr << "put file to parse"<< std::endl;
		return 0;
	}
    // declare our data var interface.
    CParserVarPropertyGroup<tSampleJson> * data_json;

    // create json-parser
    CParserJson<tSampleJson> * parser = new CParserJson<tSampleJson>();

    // parse our file
    if(parser->parseFile(argv[1])){
        // get data from parser.
		std::cout << "elements:" << parser->getData()->size()<< std::endl;
		// the values before modifications.
		std::cout << " Before modifications:"<< std::endl;
		std::cout << parser->getData()->cpp2json();    	
		for(unsigned g = 0; g < parser->getData()->size(); g++){
			data_json = parser->getData()->at(g); // gets first element group...

   			// From here we can operate with loaded data in our program using c++ operators
			// put m_use_space to false...
			data_json->m_indent.m_use_space = false;

			// iterate of all m_plugins var and replace with random strings...
			for(unsigned i = 0; i < data_json->m_plugins.size(); i++) {
				data_json->m_plugins[i] = "my_randomstring"+intToString(i+g+1);
			}

		}

		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " After modifications:"<< std::endl;
			   
		// show the modifications at screen (it can be saved in file too)
		std::cout << parser->getData()->cpp2json();

    }
    
    // deallocates parser
    delete parser;

    // that's all :)
    return 0;

}
