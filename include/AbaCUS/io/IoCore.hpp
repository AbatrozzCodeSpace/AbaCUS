#ifndef ABACUS_IO_CORE_HPP
#define ABACUS_IO_CORE_HPP

namespace abacus {
	namespace io {
		
		enum ABACUS_IO_STATUS {
			IO_SUCCESS = 0,
			IO_LOAD_ERROR,
			// add here!
			IO_UNKNOWN_ERROR
		};

	}
	using namespace io;
}

#endif