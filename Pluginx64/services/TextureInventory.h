#pragma once

#include <chrono>
#include <filesystem>
#include <mutex>
#include <string>
#include <vector>

class TextureInventory
{
public:
	TextureInventory();

	void SetCookedDirectory(std::filesystem::path directory);
	const std::filesystem::path& GetCookedDirectory() const;

	std::vector<std::string> GetMissingTexturesSnapshot();
	void InvalidateCache();

	const std::vector<std::string>& GetRequiredTextures() const;
	bool IsManagedTexture(const std::filesystem::path& filename) const;

private:
	std::vector<std::string> requiredTextures;
	std::vector<std::string> cachedMissingTextures;
	std::filesystem::path cookedDirectory;

	std::chrono::steady_clock::time_point nextCheck;
	bool cacheDirty = true;
	bool checkInFlight = false;
	std::mutex mutex;

	std::vector<std::string> ComputeMissingTextures() const;
	bool PathExists(const std::filesystem::path& path) const;
};
