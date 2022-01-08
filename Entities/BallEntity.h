#pragma once
#include "Entities/EntityNode.h"
#include "Entities/WallEntity.h"
#include "Entities/HoleEntity.h"
#include "Entities/CueEntity.h"
#include "Helpers/Simulations.h"
#include "Helpers/Vectors.h"
#include "Helpers/Globals.h"
#include "UI/UIBallTrajectory.h"

class BallEntity : public EntityNode
{
public:
	virtual const char* getName() { return "BallEntity"; }

	bool m_isPlayer = false;
	float m_elacticity = 1.0f;
	CueEntity* m_pCue = 0x0;
	UIBallTrajectory* m_pTrajectory = 0x0;
	sf::Vector2f m_velocity;

private:
	virtual void PreUpdate();
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates state) const;
	sf::Clock m_noRotTime;

public:
	BallEntity(bool isPlayer, bool isSimulation);
	void SetElacticity(float elasticity);
	void AttachCue(CueEntity* pCue);
	void AttachTrajectory(UIBallTrajectory* pTrajectory);
	void CollisionBallsCheck(std::vector<BallEntity*>& layer, bool isSimulation);
	void CollisionWallsCheck(std::vector<WallEntity*>& layer, bool isSimulation);
	void CheckHoles(std::vector<HoleEntity*> pLayer);
	void RebuildTrajectory();
	sf::CircleShape m_ball;
};

class BallManager
{
public:
	BallManager() {};
	void AddBall(BallEntity* pBall);
	void UpdateLayer(std::vector<BallEntity*>& layer);
	void Update();
	void CleanSimulation();
	void CopyBallsForSimulation();
	std::vector<BallEntity*> GetInHoles(std::vector<BallEntity*>& layer);

	bool m_allStopped = true;
	bool m_simulationAllStopped = true;
	BallEntity* m_pPlayer = nullptr;
	BallEntity* m_pSimPlayer = nullptr;
	std::vector<BallEntity*> m_balls;
	std::vector<BallEntity*> m_simulationBalls;
};

extern class BallManager* g_pBallManager;
