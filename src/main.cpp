#include "huestream/config/Config.h"
#include "huestream/HueStream.h"
#include "huestream/effect/effects/ExplosionEffect.h"
#include "huestream/effect/effects/ManualEffect.h"

#include <iostream>

int main() {    
    const std::string applicationName{"Lighting-Effects"};
    const std::string deviceName{"COLLIN-SPECTRE"};
    const huestream::PersistenceEncryptionKey encryptionKey{"123"};

    auto config = std::make_shared<huestream::Config>(applicationName, deviceName, encryptionKey);

    auto huestream = std::make_shared<huestream::HueStream>(config);

    huestream->RegisterFeedbackCallback([](const huestream::FeedbackMessage &message) {
        if (message.GetMessageType() == huestream::FeedbackMessage::FEEDBACK_TYPE_USER) {
            std::cout << message.GetUserMessage() << std::endl;
        }
        if (message.GetId() == huestream::FeedbackMessage::ID_DONE_COMPLETED) {
            std::cout << "Connected to bridge with ip: " << message.GetBridge()->GetIpAddress() << std::endl;
        }
    });

    huestream->ConnectBridge();

    
    while (!(huestream->IsStreamableBridgeLoaded() || huestream->IsBridgeStreaming())) {
        auto bridge = huestream->GetLoadedBridge();
        if (bridge->GetStatus() == huestream::BridgeStatus::BRIDGE_INVALID_GROUP_SELECTED) {
            huestream->SelectGroup(bridge->GetGroups()->at(0));
        } else {
            std::cout << ("Press Enter to retry...");
            std::cin.get();
            huestream->ConnectBridge();
        }
    }

    const auto layer = 0;
    const auto name = "custom-effect";
    auto manualEffect = std::make_shared<huestream::ManualEffect>(name, layer);

    auto colorRGB = huestream::Color(1, 0.8, 0.4);
    manualEffect->SetIdToColor("0", colorRGB);

    huestream->LockMixer();
    huestream->AddEffect(manualEffect);
    manualEffect->Enable();
    huestream->UnlockMixer();


    std::cout << ("Press Enter to quit...");
    std::cin.get();
    huestream->ShutDown();

    return 0;
}