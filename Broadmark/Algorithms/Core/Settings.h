#pragma once

#include "Macros.h"
#include "Core/Math/Vec3.h"
#include "Dependencies/json.hpp"
#include "Core/Scene.h"
#include <string>


// Input data of the Broadmark System. This is provided via a json file passed
// via command line arguments. During initialization, a settings object is 
// "inflated" with some additional data collected from the scene's header
class Settings {
public:
	std::string m_inputScene = "";
	std::string m_outputLog = "";
	std::string m_algorithm = "";
	std::string m_algorithm_prettyName = "";
	
	Vec3 m_margin = Vec3(0.01f, 0.01f, 0.01f);
	int m_numThreads = 4;
	int m_Grid_ObjectsPerCell = 200;
	int m_Tracy_ObjectsPerCell = 200;
	int m_GPUSap_KernelType = 5;
	int m_KD_ObjectsPerLeaf = 512;
	int m_GPUGrid_maxBodiesPerCell = 256*100;
	int m_vertices = 0;
	int m_edges = 0;
	int m_faces = 0;

	Settings() = default;
	void Validate() {
		STRONG_ASSERT(m_inputScene != "", " -The test file has no input scene");
		STRONG_ASSERT(m_outputLog != "", " -The test file has no output log");
		STRONG_ASSERT(m_algorithm != "", " -The test file has no algorithm");
		if (m_algorithm_prettyName.empty()) {
			m_algorithm_prettyName = m_algorithm;
		}

		STRONG_ASSERT(0 <= m_margin[0], " -The test file has a negative X margin");
		STRONG_ASSERT(0 <= m_margin[1], " -The test file has a negative Y margin");
		STRONG_ASSERT(0 <= m_margin[2], " -The test file has a negative Z margin");
	}
};

// Settings + some scene specific values read from the scene header
class InflatedSettings : public Settings {
public:
	size_t m_numberOfObjects = 0;
	Aabb m_worldAabb;

	InflatedSettings() = default;
	InflatedSettings(const Settings& settings, const SceneHeader& header) {
		this->m_inputScene = settings.m_inputScene;
		this->m_outputLog = settings.m_outputLog;
		this->m_algorithm = settings.m_algorithm;
		this->m_algorithm_prettyName = settings.m_algorithm_prettyName;

		this->m_margin = settings.m_margin;
		this->m_numThreads = settings.m_numThreads;
		this->m_Grid_ObjectsPerCell = settings.m_Grid_ObjectsPerCell;
		this->m_Tracy_ObjectsPerCell = settings.m_Tracy_ObjectsPerCell;
		this->m_KD_ObjectsPerLeaf = settings.m_KD_ObjectsPerLeaf;
		this->m_GPUSap_KernelType = settings.m_GPUSap_KernelType;

		this->m_numberOfObjects = header.m_numberOfObjects;
		this->m_worldAabb = header.m_worldAabb;
	}
};


using nlohmann::json;
void to_json(json& j, const Settings& p);
void to_json(json& j, const InflatedSettings& p);
void from_json(const json& j, Settings& p);
