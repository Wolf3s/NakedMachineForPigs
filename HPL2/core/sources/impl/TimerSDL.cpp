/*
 * Copyright © 2011-2020 Frictional Games
 *
 * This file is part of Amnesia: A Machine For Pigs.
 *
 * Amnesia: A Machine For Pigs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Amnesia: A Machine For Pigs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Amnesia: A Machine For Pigs.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "impl/TimerSDL.h"

#include <stdlib.h>

namespace hpl {

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cTimerSDL::cTimerSDL()
	{
#ifdef _WIN32
		QueryPerformanceFrequency(&mFrequency);
		mStartCount.QuadPart = 0;
		mEndCount.QuadPart = 0;
#else
		mFrequency = 1000;
		mStartCount.tv_sec = mStartCount.tv_usec = 0;
		mEndCount.tv_sec = mEndCount.tv_usec = 0;
#endif

		mbStopped = false;
		mfStartTimeInMicroSec = 0;
		mfEndTimeInMicroSec = 0;
	}

	//-----------------------------------------------------------------------

	cTimerSDL::~cTimerSDL()
	{

	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	void cTimerSDL::Start()
	{
		mbStopped = false;
#ifdef _WIN32
		QueryPerformanceCounter(&mStartCount);
#else
		gettimeofday(&mStartCount, NULL);
#endif
	}

	void cTimerSDL::Stop()
	{
#ifdef _WIN32
		QueryPerformanceCounter(&mEndCount);
#else
		gettimeofday(&mEndCount, NULL);
#endif
		mbStopped = true;
	}

	double cTimerSDL::GetTimeInMicroSec()
	{
#ifdef _WIN32
		if(mbStopped==false)
			QueryPerformanceCounter(&mEndCount);

		mfStartTimeInMicroSec = mStartCount.QuadPart * (1000000.0 / mFrequency.QuadPart);
		mfEndTimeInMicroSec = mEndCount.QuadPart * (1000000.0 / mFrequency.QuadPart);
#else
		if(mbStopped==false)
			gettimeofday(&mEndCount, NULL);

		mfStartTimeInMicroSec = ((double)mStartCount.tv_sec * 1000000.0) + mStartCount.tv_usec;
		mfEndTimeInMicroSec = ((double)mEndCount.tv_sec * 1000000.0) + mEndCount.tv_usec;
#endif

		return mfEndTimeInMicroSec - mfStartTimeInMicroSec;
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PRIVATE METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------


	//-----------------------------------------------------------------------

}

