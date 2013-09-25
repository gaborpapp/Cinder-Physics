#include "VerletPhysics.h"

namespace mndl { namespace physics {

template< class VecT >
void VerletPhysics< VecT >::update()
{
	updateParticles();
	updateSprings();
}

template< class VecT >
void VerletPhysics< VecT >::updateParticles()
{
	/*
	for (ParticleBehavior2D b : behaviors) {
		for (VerletParticle2D p : particles) {
			b.apply(p);
		}
	}
	*/
	for ( auto pit = mParticles.begin(); pit != mParticles.end(); ++pit )
	{
		(*pit)->scaleVelocity( mDrag );
		(*pit)->update();
	}
}

template< class VecT >
void VerletPhysics< VecT >::updateSprings()
{
	if ( !mSprings.empty() )
	{
		for ( int i = mNumIterations; i > 0 ; i-- )
		{
			for ( auto sit = mSprings.begin(); sit != mSprings.end(); ++sit )
			{
				(*sit)->update();
			}
		}
	}
}

template class VerletPhysics< ci::Vec2f >;

} } // namespace mndl::physics

