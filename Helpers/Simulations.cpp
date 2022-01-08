#include "Simulations.h"
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

EntityNode* Simulations::TraceLine(sf::Vector2f position, float angle, sf::Vector2f& hitPos, float radius = 0)
{
    hitPos = position;
    sf::Vector2f velocityVector = sf::Vector2f(-cos(angle / 180 * M_PI), -sin(angle / 180 * M_PI));

    for (int i = 0; i < G_TRACE_MAX_STEPS_COUNT; i++)
    {
        hitPos = hitPos + velocityVector;

        for (auto pBall : g_pBallManager->m_balls)
        {
            if (pBall->m_isPlayer || !pBall->m_isVisible) continue;

            sf::Vector2f ballPos = pBall->getPosition();
            sf::Vector2f distanceVec = ballPos - hitPos;
            float distance = Vectors::length(distanceVec) - pBall->m_ball.getRadius() - radius;

            if (distance <= 0) {
                sf::Vector2f normal = Vectors::normalize(distanceVec);
                hitPos = hitPos - (normal * distance);
                return pBall;
            }
        }

        for (auto pHole : g_pHoleManager->m_holes)
        {
            sf::Vector2f holePos = pHole->getPosition();
            sf::Vector2f distanceVec = holePos - hitPos;
            float distance = Vectors::length(distanceVec) - pHole->m_circle.getRadius() - radius;

            if (distance <= 0) {
                sf::Vector2f normal = Vectors::normalize(distanceVec);
                hitPos = hitPos + (normal * distance);
                return pHole;
            }
        }

        for (auto pWall : g_pWallManager->m_walls)
        {
            sf::Vector2f closestPoint = pWall->ClosestPoint(hitPos);
            sf::Vector2f normalVec = Vectors::normalize(closestPoint);
            float distance = Vectors::length(closestPoint) - pWall->m_depth - radius;

            if (distance <= 0)
                return pWall;
        }
    }

    return nullptr;
}

float Simulations::RandomFloat(float max)
{
    return (static_cast <float>(rand()) / static_cast <float> (RAND_MAX)) * max;
}


void Simulations::SimulateBallPhysics()
{
    int rotCycle = 0;
    float rotation = g_pBallManager->m_pPlayer->m_pCue->m_rotation;

    for (; rotation > rotation - 360; rotation -= 21.5)
    {
        float force = G_CUE_MAXFORCE;
        g_pBallManager->CopyBallsForSimulation();
        g_pBallManager->m_simulationAllStopped = false;
        g_pBallManager->m_pSimPlayer->m_velocity = -sf::Vector2f(cos(degreesToRadians(rotation)) * force, sin(degreesToRadians(rotation)) * force);
        
        int updateCount = 0;

        while (!g_pBallManager->m_simulationAllStopped)
        {
            if (updateCount >= 160) break;
            g_pBallManager->UpdateLayer(g_pBallManager->m_simulationBalls);

            auto inHoles = g_pBallManager->GetInHoles(g_pBallManager->m_simulationBalls);

            if (inHoles.size() > 0)
            {
                for (auto ball : inHoles)
                {
                    if (!ball->m_isPlayer)
                    {
                        printf("Rotation: %f; Cycle: %d\n", rotation, rotCycle);
                        g_pBallManager->m_pPlayer->m_pCue->m_rotation = rotation;
                        g_pBallManager->CleanSimulation();
                        return;
                    }
                }
            };

            updateCount++;
        }

        rotCycle++;

        if (rotCycle >= 64) return;
    }

    printf("END\n");
}
