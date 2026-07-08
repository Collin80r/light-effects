#include "Setup/StreamSetup.hpp"

#include "huestream/HueStream.h"
#include "huestream/effect/effects/ManualEffect.h"

#include <iostream>

int main() {    

    std::shared_ptr<huestream::HueStream> stream{Setup::SetupStream()};
    const auto layer = 0;
    const auto name = "custom-effect";
    auto manualEffect = std::make_shared<huestream::ManualEffect>(name, layer);

    auto colorRGB = huestream::Color(1, 0.8, 0.4);
    manualEffect->SetIdToColor("0", colorRGB);

    stream->LockMixer();
    stream->AddEffect(manualEffect);
    manualEffect->Enable();
    stream->UnlockMixer();


    std::cout << ("Press Enter to quit...");
    std::cin.get();
    stream->ShutDown();

    return 0;
}