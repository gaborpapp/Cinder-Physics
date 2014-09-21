#pragma once

#include "cinder/Cinder.h"
#include "cinder/CinderMath.h"
#include "cinder/Vector.h"

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

	void lockA()
	{
		mIsALocked = true;
	}

	void unlockA()
	{
		mIsALocked = false;
	}

	void lockB()
	{
		mIsBLocked = true;
	}

	void unlockB()
	{
		mIsBLocked = false;
	}

    void update()
	{
		VecT delta = mB->mPos - mA->mPos;
        float dist = delta.length() + ci::EPSILON_VALUE;
        float normDistStrength = ( dist - mRestLength ) /
			( dist * ( mA->mInvWeight + mB->mInvWeight)) * mStrength;
        if ( !mA->mIsLocked && !mIsALocked )
		{
			mA->mPos += delta * normDistStrength * mA->mInvWeight;
        }
        if ( !mB->mIsLocked && !mIsBLocked )
		{
			mB->mPos += delta * -normDistStrength * mB->mInvWeight;
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

typedef Spring< ci::Vec2f > Spring2f;
typedef std::shared_ptr< Spring< ci::Vec2f > > Spring2fRef;
typedef Spring< ci::Vec3f > Spring3f;
typedef std::shared_ptr< Spring< ci::Vec3f > > Spring3fRef;

} } // namespace mndl::physics

