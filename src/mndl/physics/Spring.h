#pragma once

#include "cinder/Cinder.h"
#include "cinder/CinderMath.h"
#include "cinder/Vector.h"

#include "glm/gtc/constants.hpp"

namespace mndl { namespace physics {

template< class VecT >
class Spring
{
public:
	static std::shared_ptr< Spring< VecT > > create( std::shared_ptr< Particle< VecT > > a,
			std::shared_ptr< Particle< VecT > > b,
			float restLength, float strength )
	{
		return std::shared_ptr< Spring< VecT > >( new Spring< VecT >( a, b, restLength, strength ) );
	}

	void lockA( bool lock = true )
	{
		mIsALocked = lock;
	}

	void unlockA()
	{
		mIsALocked = false;
	}

	void lockB( bool lock = true )
	{
		mIsBLocked = lock;
	}

	void unlockB()
	{
		mIsBLocked = false;
	}

	void update()
	{
		VecT delta = mB->mPos - mA->mPos;
		float dist = glm::length( delta ) + ci::EPSILON_VALUE;
		float normDistStrength = ( dist - mRestLength ) /
			( dist * ( mA->mInvWeight + mB->mInvWeight ) ) * mStrength;
		delta *= normDistStrength;
		if ( ! mA->mIsLocked && ! mIsALocked )
		{
			mA->mPos += delta * mA->mInvWeight;
		}
		if ( ! mB->mIsLocked && ! mIsBLocked )
		{
			mB->mPos -= delta * mB->mInvWeight;
		}
	}

	std::shared_ptr< Particle< VecT > > mA, mB;
	float mRestLength;
	float mStrength;

	bool mIsALocked, mIsBLocked; //< If either particle is locked in space (only within the scope of this spring).

protected:
	Spring( std::shared_ptr< Particle< VecT > > a, std::shared_ptr< Particle< VecT > > b,
			float restLength, float strength ) :
		mA( a ), mB( b ), mRestLength( restLength ), mStrength( strength ),
		mIsALocked( false ), mIsBLocked( false )
	{}
};

typedef Spring< ci::vec2 > Spring2f;
typedef std::shared_ptr< Spring< ci::vec2 > > Spring2fRef;
typedef Spring< ci::vec3 > Spring3f;
typedef std::shared_ptr< Spring< ci::vec3 > > Spring3fRef;

} } // namespace mndl::physics

