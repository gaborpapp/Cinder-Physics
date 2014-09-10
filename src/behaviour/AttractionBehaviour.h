#pragma once

#include "behaviour/ParticleBehaviour.h"

namespace mndl { namespace physics {

template< class VecT >
class AttractionBehaviour : public ParticleBehaviour< VecT >
{
public:
	static std::shared_ptr< AttractionBehaviour< VecT > > create( const VecT &pos, float radius, float strength )
	{
		return std::shared_ptr< AttractionBehaviour< VecT > >( new AttractionBehaviour( pos, radius, strength ) );
	}

	virtual void configure( float timeStep )
	{
		ParticleBehaviour< VecT >::mTimeStep = timeStep;
		setStrength( mStrength );
	}

	VecT getPosition() const { return mPos; }
	void setPosition( const VecT &pos )
	{
		mPos = pos;
	}

	float getRadius() const { return mRadius; }
	void setRadius( float r )
	{
		mRadius = r;
		mRadiusSquared = r * r;
	}

	float getStrength() const { return mStrength; }
	void setStrength( float strength )
	{
		mStrength = strength;
		mAttrStrength = strength * ParticleBehaviour< VecT >::mTimeStep;
	}

	virtual void apply( std::shared_ptr< Particle< VecT > > pref )
	{
		VecT delta = mPos - pref->mPos;
		float dSq = delta.lengthSquared();

		if ( dSq < mRadiusSquared )
		{
			VecT f = delta.normalized() * ( 1.f - dSq / mRadiusSquared ) * mAttrStrength;
			pref->addForce( f );
		}
	}

protected:
	AttractionBehaviour( const VecT &pos, float radius, float strength )
	{
		mPos = pos;
		setStrength( strength );
		setRadius( radius );
	}

	VecT mPos;
	float mAttrStrength;

	float mRadius, mRadiusSquared;
	float mStrength;
};

typedef AttractionBehaviour< ci::Vec2f > AttractionBehaviour2f;
typedef std::shared_ptr< AttractionBehaviour2f > AttractionBehaviour2fRef;
typedef AttractionBehaviour< ci::Vec3f > AttractionBehaviour3f;
typedef std::shared_ptr< AttractionBehaviour3f > AttractionBehaviour3fRef;

} } // namespace mndl::physics
