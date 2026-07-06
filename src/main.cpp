#include "huestream/config/Config.h"
#include "huestream/HueStream.h"
#include "huestream/effect/effects/ExplosionEffect.h"
#include "huestream/effect/effects/ManualEffect.h"

#include <iostream>

void SelectEntertainmentGroup(std::shared_ptr<huestream::HueStream> aHuestream);

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
    SelectEntertainmentGroup(huestream); // Can be commented out if you don't want to change the group

    while (!(huestream->IsStreamableBridgeLoaded() || huestream->IsBridgeStreaming())) {
        auto bridge = huestream->GetLoadedBridge();
        if (bridge->GetStatus() == huestream::BridgeStatus::BRIDGE_INVALID_GROUP_SELECTED) {
            SelectEntertainmentGroup(huestream);
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

void SelectEntertainmentGroup(std::shared_ptr<huestream::HueStream> aHuestream) {
    const auto groups = aHuestream->GetLoadedBridge()->GetGroups();
    int chosenIndex{0};
    std::cout << "Entertainment Groups" << std::endl;
    const auto groupsCount = groups->size();
    for (int i{0}; i < groupsCount; i++) {
        std::cout << i << ": ";
        std::cout << groups->at(i)->GetName() << std::endl;
    }

    std::cout << "Pick a group:";
    std::cin >> chosenIndex;
    std::cin.ignore(INT8_MAX, '\n');
    if (chosenIndex < 0 || chosenIndex >= groupsCount) {
        std::cout << "Invalid option. Got " << chosenIndex << std::endl;
        std::cout << "Defaulting to 0." << std::endl;
    }
    
    aHuestream->SelectGroup(groups->at(chosenIndex));
}