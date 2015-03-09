#pragma once

#include "cinder/Cinder.h"

#include "mndl/physics/Particle.h"

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

typedef ParticleBehaviour< ci::vec2 > ParticleBehaviour2f;
typedef std::shared_ptr< ParticleBehaviour2f > ParticleBehaviour2fRef;
typedef ParticleBehaviour< ci::vec3 > ParticleBehaviour3f;
typedef std::shared_ptr< ParticleBehaviour3f > ParticleBehaviour3fRef;

} } // namespace mndl::physics
