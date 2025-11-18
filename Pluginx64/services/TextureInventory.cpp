#include "pch.h"
#include "services/TextureInventory.h"

#include <algorithm>
#include <system_error>
#include <thread>

namespace
{
constexpr std::chrono::seconds kTextureCacheTtl{ 30 };
}

TextureInventory::TextureInventory()
	: requiredTextures{
		"EditorLandscapeResources.upk", "EditorMaterials.upk", "EditorMeshes.upk", "EditorResources.upk",
		"Engine_MI_Shaders.upk", "EngineBuildings.upk", "EngineDebugMaterials.upk",
		"EngineMaterials.upk", "EngineResources.upk", "EngineVolumetrics.upk",
		"MapTemplateIndex.upk", "MapTemplates.upk", "mods.upk", "NodeBuddies.upk" }
{
}

void TextureInventory::SetCookedDirectory(std::filesystem::path directory)
{
	cookedDirectory = std::move(directory);
	InvalidateCache();
}

const std::filesystem::path& TextureInventory::GetCookedDirectory() const
{
	return cookedDirectory;
}

std::vector<std::string> TextureInventory::GetMissingTexturesSnapshot()
{
	std::vector<std::string> snapshot;
	bool shouldDispatchCheck = false;

	{
		std::lock_guard<std::mutex> lock(mutex);
		snapshot = cachedMissingTextures;
		const auto now = std::chrono::steady_clock::now();
		if (!checkInFlight &&
			(cacheDirty || nextCheck.time_since_epoch().count() == 0 || now >= nextCheck))
		{
			checkInFlight = true;
			shouldDispatchCheck = true;
		}
	}

	if (shouldDispatchCheck)
	{
		std::thread([this]()
			{
				auto missing = ComputeMissingTextures();
				std::lock_guard<std::mutex> guard(mutex);
				cachedMissingTextures = std::move(missing);
				cacheDirty = false;
				nextCheck = std::chrono::steady_clock::now() + kTextureCacheTtl;
				checkInFlight = false;
			}).detach();
	}

	return snapshot;
}

void TextureInventory::InvalidateCache()
{
	std::lock_guard<std::mutex> lock(mutex);
	cacheDirty = true;
	nextCheck = std::chrono::steady_clock::time_point{};
}

const std::vector<std::string>& TextureInventory::GetRequiredTextures() const
{
	return requiredTextures;
}

bool TextureInventory::IsManagedTexture(const std::filesystem::path& filename) const
{
	const auto fileNameLower = filename.filename().string();
	return std::find(requiredTextures.begin(), requiredTextures.end(), fileNameLower) != requiredTextures.end();
}

std::vector<std::string> TextureInventory::ComputeMissingTextures() const
{
	if (cookedDirectory.empty())
	{
		return {};
	}

	std::vector<std::string> missingFiles;
	for (const auto& textureFile : requiredTextures)
	{
		if (!PathExists(cookedDirectory / textureFile))
		{
			missingFiles.push_back(textureFile);
		}
	}

	return missingFiles;
}

bool TextureInventory::PathExists(const std::filesystem::path& path) const
{
	std::error_code ec;
	return std::filesystem::exists(path, ec);
}
