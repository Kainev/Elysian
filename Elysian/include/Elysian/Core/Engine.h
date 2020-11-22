#pragma once

#include <memory>

#include "Elysian/Core/Platform.h"
#include "Elysian/Core/Logging.h"
#include "Elysian/Core/Assert.h"
#include "Elysian/Core/Application.h"


namespace Elysian
{
	template <typename T>
	void initialize()
	{
		Logging::initialize();
		ELYSIAN_INTERNAL_INFO("Initializing Version {}.{}.{}", ELYSIAN_VERSION_MAJOR, ELYSIAN_VERSION_MINOR, ELYSIAN_VERSION_PATCH);

		std::unique_ptr<T> app = std::make_unique<T>();
	}
}