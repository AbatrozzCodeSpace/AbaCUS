#ifndef ABACUS_NODE_HPP
#define ABACUS_NODE_HPP

#include <vector>

namespace abacus {
	namespace ds {

		template <typename T>
		class NodeBase {
		public :
			NodeBase( T &newData ) { data = newData; }
			~NodeBase() { delete data; }
			T* getData() { return data; } // return data inside this node
			void setData( T &newData ) { data = newData; }
			NodeBase<T>* getParent() { return parent; } // return the parent if any, return NULL if there is no parent. (HAH! you orphan)
			NodeBase<T>* getChild( int idx ) // return a child of index idx, return NULL if none
			{ 
				if( getNumChildern() < idx && idx >= 0 ) return children.at( idx );
				else return NULL;
			}
			std::vector<NodeBase<T>*> &getChildren() { return children; } // return all children in this node, it returns the internal data of the class, use it at your own risk!
			unsigned int getNumChildren() { return childern.size(); } // return the size of children

			void setParent( NodeBase<T>* newParent ) { parent = newParent; }  // set new parent to this node
			void addChild( NodeBase<T>* newChild ) { children.push_back( newChild ); } // add new child to this node
			void removeChild( unsigned int thatChild ) { children.erase( children.begin() + thatChild ); } /* remove thatChild from the children. 
																											* Noted that the index of other children can be changed. 
																											* (YOU'RE NOT MY SON!)
																											*/
			void clearChildren() { children.clear(); } // clear all the children. (KILL THEM ALL!)
		private:
			T* data;
			std::vector<NodeBase<T>*> children;
			NodeBase<T>* parent;
		};
	
	};
	using namespace ds;
};

#endif