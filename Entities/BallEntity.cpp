#include "BallEntity.h"

void BallEntity::PreUpdate()
{
	if (m_pTrajectory != nullptr && m_pCue != nullptr) {
		m_pTrajectory->setPosition(getPosition());

		if (m_pCue->m_cueState == CueEntity::CUESTATE::PLACING)
		{
			if (m_pCue->m_rotationSpeed != 0)
			{
				m_pCue->m_rotation += m_pCue->m_rotationSpeed;
				RebuildTrajectory();
			}
		}
	}
}

void BallEntity::OnDraw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(m_ball, state);
}

BallEntity::BallEntity(bool isPlayer, bool isSimulation = false)
{
	m_isPlayer = isPlayer;
	m_ball = sf::CircleShape(10.0f, 24);
	m_ball.setOrigin(m_ball.getRadius(), m_ball.getRadius());
	
	if (isSimulation) g_pBallManager->m_simulationBalls.push_back(this);
	else g_pBallManager->AddBall(this);
}

void BallEntity::SetElacticity(float elasticity)
{
	m_elacticity = elasticity;
}

void BallEntity::AttachCue(CueEntity* pCue)
{
	m_pCue = pCue;
	addNode(pCue);
}

void BallEntity::AttachTrajectory(UIBallTrajectory* pTrajectory)
{
	m_pTrajectory = pTrajectory;
	m_pTrajectory->m_rotation = &m_pCue->m_rotation;
	RebuildTrajectory();
}

void BallEntity::CollisionBallsCheck(std::vector<BallEntity*>& layer, bool isSimulation)
{
	if ((g_pBallManager->m_allStopped || !m_isVisible) && !isSimulation) return;

	for (auto pBall : layer)
	{
		if (pBall != this && pBall->m_isVisible)
		{
			sf::Vector2f myPos = getPosition();
			sf::Vector2f otPos = pBall->getPosition();

			sf::Vector2f distanceVec = otPos - myPos;
			sf::Vector2f normalVec = Vectors::normalize(distanceVec);
			sf::Vector2f relVel = m_velocity - pBall->m_velocity;

			float sepVel = Vectors::dot(relVel, normalVec) * m_elacticity;
			float distance = Vectors::length(distanceVec) - m_ball.getRadius() - pBall->m_ball.getRadius();

			if (distance < 0)
			{
				float halfDistance = distance / 2;
				move(normalVec * halfDistance);
				pBall->move(-normalVec * halfDistance);

				m_velocity = m_velocity + sf::Vector2f(normalVec * -sepVel);
				pBall->m_velocity = pBall->m_velocity + sf::Vector2f(normalVec * sepVel);
			}
		}
	}
}

void BallEntity::CollisionWallsCheck(std::vector<WallEntity*>& layer, bool isSimulation)
{
	if ((g_pBallManager->m_allStopped || !m_isVisible) && !isSimulation) return;

	for (size_t i = 0; i < layer.size(); i++)
	{
		WallEntity* wall = layer[i];
		sf::Vector2f closestPoint = wall->ClosestPoint(getPosition());
		sf::Vector2f normalVec = Vectors::normalize(closestPoint);
		float wallDist = Vectors::length(closestPoint) - m_ball.getRadius() - wall->m_depth;

		if (wallDist < 0)
		{
			float sepVel = Vectors::dot(m_velocity, normalVec);
			float new_sepVel = -sepVel * m_elacticity;

			move(normalVec * wallDist);
			m_velocity += sf::Vector2f(normalVec * -(sepVel - new_sepVel));
			return;
		}
	}
}

void BallEntity::CheckHoles(std::vector<HoleEntity*> pLayer)
{
	if (!m_isVisible) return;

	for (auto hole : pLayer)
	{
		sf::Vector2f myPos = getPosition();
		sf::Vector2f otPos = hole->getPosition();

		sf::Vector2f distanceVec = otPos - myPos;
		sf::Vector2f normalVec = Vectors::normalize(distanceVec);
		float distance = Vectors::length(distanceVec) - m_ball.getRadius() - hole->m_fRadius;

		if (distance < 0)
		{
			m_velocity = sf::Vector2f(0, 0);
			if (!m_isPlayer) m_isVisible = false;
			else setPosition(100, 200);
		}
	}
}

void BallEntity::RebuildTrajectory()
{
	sf::Vector2f hitPos;
	sf::Vector2f startPos = getPosition();
	EntityNode* pEntity = Simulations::TraceLine(startPos, m_pCue->m_rotation, hitPos, m_ball.getRadius());

	if (pEntity == nullptr)
		m_pTrajectory->m_isVisible = false;
	else if (pEntity->getName() == "BallEntity" || pEntity->getName() == "WallEntity" || pEntity->getName() == "HoleEntity")
		m_pTrajectory->Rebuild(Vectors::length(startPos - hitPos) - 16);
}

/* BallManager */

void BallManager::AddBall(BallEntity* pBall)
{
	if (pBall->m_isPlayer) m_pPlayer = pBall;
	m_balls.push_back(pBall);
}

void BallManager::UpdateLayer(std::vector<BallEntity*>& layer)
{
	bool isSimulation = layer == m_simulationBalls;
	short cyclesCount = 4;

	for (int i = 0; i < cyclesCount; i++)
	{
		for (auto ball : layer) ball->move(ball->m_velocity / (float)cyclesCount);
		for (auto ball : layer) ball->CollisionWallsCheck(g_pWallManager->m_walls, isSimulation);
		for (auto ball : layer) ball->CollisionBallsCheck(layer, isSimulation);
		for (auto ball : layer) ball->CheckHoles(g_pHoleManager->m_holes);
	}

	for (auto ball : layer) ball->m_velocity = ball->m_velocity * (1.0f - G_FRICTION);

	if ((m_allStopped && !isSimulation) || (m_simulationAllStopped && isSimulation)) return;

	bool allStopped = true;
	for (auto ball : layer)
	{
		float velocity = Vectors::length(ball->m_velocity);

		if (velocity <= G_BALL_MINSPEED) ball->m_velocity = sf::Vector2f();
		else allStopped = false;
	}

	if (isSimulation == false && allStopped == true && m_allStopped == false)
	{
		// starting a new round of the game
		m_pPlayer->RebuildTrajectory();
		m_pPlayer->m_pCue->m_cueState = CueEntity::CUESTATE::PLACING;
		CleanSimulation();
	}

	if (isSimulation == false)
	{
		m_allStopped = allStopped;

		if (m_pPlayer != 0x0 && m_pPlayer->m_pCue != 0x0)
			m_pPlayer->m_pCue->m_isVisible = allStopped;

		if (m_pPlayer != 0x0 && m_pPlayer->m_pTrajectory != 0x0 && m_pPlayer->m_pCue != 0x0)
			m_pPlayer->m_pTrajectory->m_isVisible = allStopped;
	}
	else
	{
		m_simulationAllStopped = allStopped;
	}
}

void BallManager::Update()
{
	UpdateLayer(m_balls);
}

void BallManager::CleanSimulation()
{
	for (BallEntity* ball : m_simulationBalls) delete ball;
	m_simulationBalls.clear();
}

void BallManager::CopyBallsForSimulation()
{
	CleanSimulation();

	for (BallEntity* ball : m_balls)
	{
		if (!ball->m_isVisible) continue;
		BallEntity* pNBall = new BallEntity(ball->m_isPlayer, true);
		if (ball->m_isPlayer) m_pSimPlayer = pNBall;

		sf::Vector2f position = ball->getPosition();
		pNBall->setPosition(position);
	}
}

std::vector<BallEntity*> BallManager::GetInHoles(std::vector<BallEntity*>& layer)
{
	std::vector<BallEntity*> inHoles;

	for (auto ball : layer)
		if (!ball->m_isVisible) inHoles.push_back(ball);

	return inHoles;
}

BallManager* g_pBallManager = new BallManager();