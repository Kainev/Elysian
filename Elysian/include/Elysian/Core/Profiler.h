#pragma once

#include <chrono>
#include <iostream>

#define PROFILE_SCOPE(name) ProfileScope profiler##__LINE__(name);


	class ProfileScope
	{
	public:
		ProfileScope(const char* name) : mName(name), mStopped(false)
		{
			mStartTimePoint = std::chrono::high_resolution_clock::now();
		}

		~ProfileScope()
		{
			if (!mStopped)
				Stop();
		}

		void Stop()
		{
			auto endTimePoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimePoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

			mStopped = true;

			float duration = end - start;

			std::cout << mName << "::Duration: " << duration << "us" << std::endl;
		}

	private:
		const char* mName;
		std::chrono::time_point<std::chrono::steady_clock> mStartTimePoint;
		bool mStopped;
	};
