#ifndef ABACUS_GRAPH_HPP
#define ABACUS_GRAPH_HPP

#include <AbaCUS/ds/Node.hpp>

namespace abacus {
	namespace ds {
		
		template <typename T>
		class GraphBase {
		public :
			GraphBase();
			GraphBase( NodeBase<T>* head ) { header = head; }
			NodeBase<T>* getHead() { return header; }
			void setHead( NodeBase<T>* head ) { header = head; }
		private:
			NodeBase<T>* header;
		};

	};
	using namespace ds;
};

#endif