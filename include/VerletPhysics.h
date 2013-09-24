#pragma once

#include <vector>

#include "Particle.h"

namespace mndl { namespace physics {

template< class VecT >
class VerletPhysics
{
public:
	static std::shared_ptr< VerletPhysics< VecT > > create( size_t numIterations = 50, float drag = 1.f, float timeStep = 1.f )
	{
		return std::shared_ptr< VerletPhysics< VecT > >( new VerletPhysics( numIterations, drag, timeStep ) );
	}

protected:
	VerletPhysics( size_t numIterations, float drag, float timeStep ) :
		mNumIterations( numIterations ), mDrag( drag), mTimeStep( timeStep )
	{}

	size_t mNumIterations;
	float mDrag;
	float mTimeStep;

	std::vector< std::shared_ptr< Particle< VecT > > > mParticles;
};

typedef VerletPhysics< ci::Vec2f > VerletPhysics2f;
typedef std::shared_ptr< VerletPhysics2f > VerletPhysics2fRef;

} } // namespace mndl::physics
