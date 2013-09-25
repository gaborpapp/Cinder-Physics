#pragma once

#include "cinder/Cinder.h"

#include "Particle.h"

namespace mndl { namespace physics {

template< class VecT >
class ParticleBehaviour
{
public:
	virtual void apply( std::shared_ptr< Particle< VecT > > pref ) = 0;

	virtual void configure( float timeStep )
	{
		mTimeStep = timeStep;
	}

protected:
	float mTimeStep;
};

typedef ParticleBehaviour< ci::Vec2f > ParticleBehaviour2f;
typedef std::shared_ptr< ParticleBehaviour2f > ParticleBehaviour2fRef;

} } // namespace mndl::physics
