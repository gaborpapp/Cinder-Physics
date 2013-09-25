#pragma once

#include "cinder/Cinder.h"
#include "cinder/Vector.h"

namespace mndl { namespace physics {

template< class VecT >
class Particle
{
public:
	static std::shared_ptr< Particle< VecT > > create( const VecT &pos = VecT::zero(), float w = 1.f )
	{
		return std::shared_ptr< Particle< VecT > >( new Particle< VecT >( pos, w ) );
	}

	static std::shared_ptr< Particle< VecT > > create( std::shared_ptr< Particle< VecT > > srcRef )
	{
		return std::shared_ptr< Particle< VecT > >( new Particle< VecT >( *srcRef.get() ) );
	}

	void setWeight( float w )
	{
		mWeight = w;
		mInvWeight = 1.f / w;
	}

	void addForce( const VecT &f )
	{
		mForce += f;
	}

	void addVelocity( const VecT &v )
	{
		mPrevPos -= v;
	}

	void applyForce()
	{
		VecT temp = mPos;
		mPos += mPos - mPrevPos + mForce * mInvWeight;
		mPrevPos = temp;
		mForce = VecT::zero();
	}

	VecT getVelocity() const
	{
		return mPos - mPrevPos;
	}

	void clearForce()
	{
		mForce = VecT::zero();
	}

	void clearVelocity()
	{
		mPrevPos = mPos;
	}

	void lock()
	{
		mIsLocked = true;
	}

	void unlock()
	{
		clearVelocity();
		mIsLocked = false;
	}

	void update()
	{
		if ( !mIsLocked )
		{
			applyForce();
		}
	}

    void scaleVelocity( float s )
	{
		mPrevPos = mPrevPos.lerp( s, mPos );
    }

	VecT mPos, mPrevPos;
	bool mIsLocked;

	float mWeight, mInvWeight;
	VecT mForce;

protected:
	Particle( const VecT &pos = VecT::zero(), float w = 1.f ) :
		mPos( pos ), mPrevPos( pos ), mIsLocked( false )
	{
		setWeight( w );
	}

	Particle( const Particle< VecT > &src ) :
		Particle( src.mPos, src.mWeight ),
		mIsLocked( src.mIsLocked )
	{}
};

typedef Particle< ci::Vec2f > Particle2f;
typedef std::shared_ptr< Particle< ci::Vec2f > > Particle2fRef;

} } // namespace mndl::physics

