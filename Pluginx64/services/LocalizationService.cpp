#include "pch.h"
#include "services/LocalizationService.h"

bool LocalizationService::ShouldApply(bool french) const
{
	if (!initialized)
	{
		return true;
	}

	return lastFrench != french;
}

void LocalizationService::MarkApplied(bool french)
{
	initialized = true;
	lastFrench = french;
}

bool LocalizationService::IsFrench() const
{
	return initialized && lastFrench;
}
