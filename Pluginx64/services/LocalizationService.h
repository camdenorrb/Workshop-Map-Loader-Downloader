#pragma once

class LocalizationService
{
public:
	bool ShouldApply(bool french) const;
	void MarkApplied(bool french);
	bool IsFrench() const;

private:
	bool initialized = false;
	bool lastFrench = false;
};
