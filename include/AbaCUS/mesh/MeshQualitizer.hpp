/*
@Descriptions : This class is all about mesh simplification.
@Dependencies : cinder
*/

#ifndef MESH_QUALITIZER_HPP
#define MESH_QUALITIZER_HPP

#if defined (CINDER_CINDER)
	#include <cinder/TriMesh.h>
#endif

#include <vector>
#include <set>
#include <map>

namespace abacus {
	namespace mesh {
		class meshQualitizer {
		private:
#if defined (CINDER_CINDER)
			struct classcomp_vec3i {
				bool operator() (const ci::Vec3i& lhs, const ci::Vec3i& rhs) const
				{
					if ( lhs.x < rhs.x ) {
						return true;
					} else if ( lhs.x == rhs.x && lhs.y < rhs.y ) {
						return true;
					} else if ( lhs.x == rhs.x && lhs.y == rhs.y && lhs.z < rhs.z ) {
						return true;
					} else {
						return false;
					}
				}
			};
#endif
		public:
#if defined (CINDER_CINDER)
			static void qualitizeInVoxel( ci::TriMesh &input, ci::TriMesh &output, ci::Vec3f worldMinBound, ci::Vec3f worldMaxBound, ci::Vec3i voxelSize, bool centerVoxel = false ) {
				std::vector<ci::Vec3f> inVertices = input.getVertices();
				std::vector<uint32_t> inIndices = input.getIndices();

				std::vector<ci::Vec3f> outVertices;
				std::vector<uint32_t> outIndices;

				std::vector<int>** voxel2Vertices = new std::vector<int>*[voxelSize.x * voxelSize.y * voxelSize.z];
				for ( int i = 0 ; i < voxelSize.x * voxelSize.y * voxelSize.z ; i++ ) {
					voxel2Vertices[i] = NULL;
				}
				std::vector<int> vertices2Voxel;

				ci::Vec3f step = (worldMaxBound-worldMinBound) / voxelSize;
				// create the mapping voxel<->mesh
				for ( int i = 0 ; i < inVertices.size() ; i++ ) {
					ci::Vec3f position = inVertices[i];
					ci::Vec3i voxelPosition = ( position - worldMinBound ) / step;
					int index = voxelPosition.x * voxelSize.y * voxelSize.z + voxelPosition.y * voxelSize.z + voxelPosition.z;

					if( voxel2Vertices[index] == NULL ) {
						voxel2Vertices[index] = new std::vector<int>();
						voxel2Vertices[index]->push_back( i );
					} else {
						voxel2Vertices[index]->push_back( i );
					}
					vertices2Voxel.push_back( index );

				}
				// second sweep to create a new mesh vertices
				std::map<uint32_t, uint32_t> voxel2Idx;
				int counter = 0;
				for ( int i = 0 ; i < voxelSize.x * voxelSize.y * voxelSize.z ; i++ ) {
					if( voxel2Vertices[i] != NULL ) {
						voxel2Idx[i] = counter;
						counter++;

						ci::Vec3f avgPos( 0,0,0 );
						for( int j = 0 ; j < voxel2Vertices[i]->size(); j++ ){
							avgPos += inVertices[voxel2Vertices[i]->at(j)];
						}
						avgPos /= voxel2Vertices[i]->size();
						outVertices.push_back( avgPos );
					}
				}
				// third sweep to create new idx
				std::set<ci::Vec3i, classcomp_vec3i> duplicateCheck;
				for ( int i = 0 ; i < inIndices.size(); i += 3 ) {
					ci::Vec3i oldIdx( inIndices[i], inIndices[i+1], inIndices[i+2] );
					ci::Vec3i newIdx( voxel2Idx[vertices2Voxel[oldIdx.x]], voxel2Idx[vertices2Voxel[oldIdx.y]], voxel2Idx[vertices2Voxel[oldIdx.z]] );
					ci::Vec3i forCheck = newIdx;
					// do the sorting
					if( forCheck.z < forCheck.y ) { int tmp = forCheck.y; forCheck.y = forCheck.z; forCheck.z = tmp; }
					if( forCheck.y < forCheck.x ) { int tmp = forCheck.x; forCheck.x = forCheck.y; forCheck.y = tmp; }
					if( forCheck.z < forCheck.y ) { int tmp = forCheck.y; forCheck.y = forCheck.z; forCheck.z = tmp; }

					if ( duplicateCheck.find( forCheck ) == duplicateCheck.end() ) {
						duplicateCheck.insert( forCheck );
						outIndices.push_back( newIdx.x );
						outIndices.push_back( newIdx.y );
						outIndices.push_back( newIdx.z );
					}
				}
				ci::app::console() << "TT" << std::endl;
				output.clear();
				output.appendVertices( outVertices.data(), outVertices.size() );
				output.appendIndices( outIndices.data(), outIndices.size() );
			}
			
		};
	}
#endif
	using namespace mesh;
}

#endif