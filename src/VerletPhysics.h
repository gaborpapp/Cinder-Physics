#pragma once

#include <vector>

#include "Particle.h"
#include "Spring.h"

namespace mndl { namespace physics {

template< class VecT >
class VerletPhysics
{
public:
	static std::shared_ptr< VerletPhysics< VecT > > create( size_t numIterations = 50, float drag = 1.f, float timeStep = 1.f )
	{
		return std::shared_ptr< VerletPhysics< VecT > >( new VerletPhysics( numIterations, drag, timeStep ) );
	}

	void addParticle( std::shared_ptr< Particle< VecT > > pref )
	{
		mParticles.push_back( pref );
	}

	void addSpring( std::shared_ptr< Spring< VecT > > sref )
	{
		mSprings.push_back( sref );
	}

	std::vector< std::shared_ptr< Particle< VecT > > > & getParticles() { return mParticles; }
	const std::vector< std::shared_ptr< Particle< VecT > > > & getParticles() const { return mParticles; }

	std::vector< std::shared_ptr< Spring< VecT > > > & getSprings() { return mSprings; }
	const std::vector< std::shared_ptr< Spring< VecT > > > & getSprings() const { return mSprings; }

	void update();

protected:
	VerletPhysics( size_t numIterations, float drag, float timeStep ) :
		mNumIterations( numIterations ), mDrag( drag), mTimeStep( timeStep )
	{}

	void updateParticles();
	void updateSprings();

	size_t mNumIterations;
	float mDrag;
	float mTimeStep;

	std::vector< std::shared_ptr< Particle< VecT > > > mParticles;
	std::vector< std::shared_ptr< Spring< VecT > > > mSprings;
};

typedef VerletPhysics< ci::Vec2f > VerletPhysics2f;
typedef std::shared_ptr< VerletPhysics2f > VerletPhysics2fRef;

} } // namespace mndl::physics
