// Author: Collin Downey, Created: 2026

#if !defined SETUP_STREAMSETUP_HPP
#define SETUP_STREAMSETUP_HPP

#include "huestream/config/Config.h"
#include "huestream/HueStream.h"
#include "huestream/effect/effects/ExplosionEffect.h"
#include "huestream/effect/effects/ManualEffect.h"

#include <iostream>

namespace Setup {
    void SelectEntertainmentGroup(std::shared_ptr<huestream::HueStream> aHuestream);
    std::shared_ptr<huestream::HueStream> SetupStream();
    
} // namespace Setup

#endif