/*
 * This class is a simple parser for console arguments
 * Which you can add the flags that is needed, and this class will automatically group the flag and args together.
 * This class is available with either char or wchar type, which you can set the template CharType to char or wchar.
 * 
 * This class is not tested yet!!!
 * 
 * Known issue :
 * 
 */

#ifndef ABACUS_ARGUMENT_PARSER_HPP
#define ABACUS_ARGUMENT_PARSER_HPP

#include <AbaCUS/string/split.hpp>

namespace abacus {
	namespace string {

		enum ABACUS_PARSER_STATUS {
			ABACUS_PARSER_SUCCESS = 0,
			ABACUS_PARSER_UNCORRECT_NUM_ARGUMENTS_ERROR,
			ABACUS_PARSER_UNCORRECT_FLAG_ERROR,
			ABACUS_PARSER_DUPLICATE_FLAG_ERROR,
			ABACUS_PARSER_REQUIRE_FLAGS_MISSING_ERROR,
			ABACUS_PARSER_UNKNOWN_ERROR,
			ABACUS_PARSER_STATUS_SIZE
		};

		/*
		 * CharType could be either char or wchar_t 
		 */
		template <typename CharType>
		class FlagArgs {
		public:
			typedef std::basic_string<CharType, std::char_traits<CharType>, std::allocator<CharType> > StringType;

			FlagArgs( StringType flag, int numArgs ) {
				this->flag = flag;
				args.resize(numArgs);
				isActive = false;
			}
			StringType flag;
			std::vector<StringType> args;
			bool isActive; // after parsed, if true, the flag is used in the app.
		};

		template <typename CharType>
		class ArgumentParser {
		public :
			typedef std::basic_string<CharType, std::char_traits<CharType>, std::allocator<CharType> > StringType;
			ArgumentParser( StringType name ) {
				flags.clear();
				descriptions.clear();
				requireFlags.clear();
				appName = name;
			}
			/*
			 *	@flag				: the flag to be added, for example "-flag"
			 *	@numArgsRequired	: number of arguments required for the flag.
			 *	@description		: description for the flag
			 *	@isRequired			: the flag should be exists when parse, otherwise, throw error
			 */
			void setName( StringType name ) { appName = name; };
			void addFlag( StringType flag, int numArgsRequired, StringType description, bool isRequired ) {
				flags.push_back( FlagArgs<CharType>(flag, numArgsRequired) );
				descriptions.push_back( description );
				requireFlags.push_back(isRequired);
			};
			template <typename U = CharType>
			typename std::enable_if<std::is_same<U, char>::value, U>::type
			getUsageString() { // char
				std::string usage = ""; 

				return usage;
			};
			template <typename U = CharType>
			typename std::enable_if<std::is_same<U, wchar_t>::value, U>::type
			getUsageString() { // wchar_t
				std::wstring usage = L"";

				return usage;
			};

			ABACUS_PARSER_STATUS parse( int argc, CharType* argv[] ) {
				for( unsigned int i = 1 ; i < argc ; i++ ) {
					StringType str = argv[i];
					bool isFlag = false;
					for( unsigned int j = 0 ; j < flags.size(); j++ ) { // check if it is one of the flags
						if( str.compare( flags[j].flag ) == 0 ) { // if it is actually one of the thing
							isFlag = true;
							if( !flags[j].isActive ) {
								flags[j].isActive = true;
							} else {
								return ABACUS_PARSER_DUPLICATE_FLAG_ERROR;
							}
							int numArgsRequired = flags[j].args.size();
							for( unsigned int k = 0 ; k < numArgsRequired ; k++ ) {
								if( i+1 < argc ) {
									StringType anArg = argv[++i];
									flags[j].args[k] = anArg;
								} else {
									return ABACUS_PARSER_UNCORRECT_NUM_ARGUMENTS_ERROR;
								}
							}
							break;
						}
					}
					if( !isFlag ) {
						return ABACUS_PARSER_UNCORRECT_FLAG_ERROR;
					}
				}
				// check if all required flag is active
				for( unsigned int i = 0 ; i < flags.size() ; i++ ) {
					if( !( requireFlags[i] && flags[i].isActive ) ) {
						return ABACUS_PARSER_REQUIRE_FLAGS_MISSING_ERROR;
					}
				}
				return ABACUS_PARSER_SUCCESS;
			};
		private:
			std::vector<FlagArgs<CharType>> flags;
			std::vector<StringType> descriptions;
			std::vector<bool> requireFlags;
			StringType appName;
		};


	}
	using namespace string;
}

#endif