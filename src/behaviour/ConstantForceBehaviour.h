#pragma once

#include "behaviour/ParticleBehaviour.h"

namespace mndl { namespace physics {

template< class VecT >
class ConstantForceBehaviour : public ParticleBehaviour< VecT >
{
 public:
	static std::shared_ptr< ConstantForceBehaviour< VecT > > create( const VecT &force )
	{
		return std::shared_ptr< ConstantForceBehaviour< VecT > >( new ConstantForceBehaviour( force ) );
	}

	virtual void configure( float timeStep )
	{
		ParticleBehaviour< VecT >::mTimeStep = timeStep;
	}

	void setForce( const VecT &force )
	{
		mForce = force;
	}

	const VecT & getForce() const { return mForce; }

	virtual void apply( std::shared_ptr< Particle< VecT > > pref )
	{
		pref->addForce( mForce );
	}

 protected:
	ConstantForceBehaviour( const VecT &force ) : mForce( force )
	{}

	VecT mForce;
};

typedef ConstantForceBehaviour< ci::Vec2f > ConstantForceBehaviour2f;
typedef std::shared_ptr< ConstantForceBehaviour2f > ConstantForceBehaviour2fRef;
typedef ConstantForceBehaviour< ci::Vec3f > ConstantForceBehaviour3f;
typedef std::shared_ptr< ConstantForceBehaviour3f > ConstantForceBehaviour3fRef;

} } // namespace mndl::physics

