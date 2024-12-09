#include "Obstacles.h"

DEFINE_LOG_CATEGORY_STATIC(LogObstacles, Log, All);

class FObstaclesModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        UE_LOG(LogObstacles, Warning, TEXT("Obstacles module has started!"));
    }

    virtual void ShutdownModule() override
    {
        UE_LOG(LogObstacles, Warning, TEXT("Obstacles module has shut down."));
    }
};

IMPLEMENT_MODULE(FObstaclesModule, Obstacles)
