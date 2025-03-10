#pragma once
#include "libtcod.hpp"

namespace Color {
    // Grey levels
    static const tcod::ColorRGB black{0, 0, 0};
    static const tcod::ColorRGB darkestGrey{31, 31, 31};
    static const tcod::ColorRGB darkerGrey{63, 63, 63};
    static const tcod::ColorRGB darkGrey{95, 95, 95};
    static const tcod::ColorRGB grey{127, 127, 127};
    static const tcod::ColorRGB lightGrey{159, 159, 159};
    static const tcod::ColorRGB lighterGrey{191, 191, 191};
    static const tcod::ColorRGB lightestGrey{223, 223, 223};
    static const tcod::ColorRGB white{255, 255, 255};

    // Sepia
    static const tcod::ColorRGB darkestSepia{31, 24, 15};
    static const tcod::ColorRGB darkerSepia{63, 50, 31};
    static const tcod::ColorRGB darkSepia{94, 75, 47};
    static const tcod::ColorRGB sepia{127, 101, 63};
    static const tcod::ColorRGB lightSepia{158, 134, 100};
    static const tcod::ColorRGB lighterSepia{191, 171, 143};
    static const tcod::ColorRGB lightestSepia{222, 211, 195};

    // Standard colors
    static const tcod::ColorRGB red{255, 0, 0};
    static const tcod::ColorRGB flame{255, 63, 0};
    static const tcod::ColorRGB orange{255, 127, 0};
    static const tcod::ColorRGB amber{255, 191, 0};
    static const tcod::ColorRGB yellow{255, 255, 0};
    static const tcod::ColorRGB lime{191, 255, 0};
    static const tcod::ColorRGB chartreuse{127, 255, 0};
    static const tcod::ColorRGB green{0, 255, 0};
    static const tcod::ColorRGB sea{0, 255, 127};
    static const tcod::ColorRGB turquoise{0, 255, 191};
    static const tcod::ColorRGB cyan{0, 255, 255};
    static const tcod::ColorRGB sky{0, 191, 255};
    static const tcod::ColorRGB azure{0, 127, 255};
    static const tcod::ColorRGB blue{0, 0, 255};
    static const tcod::ColorRGB han{63, 0, 255};
    static const tcod::ColorRGB violet{127, 0, 255};
    static const tcod::ColorRGB purple{191, 0, 255};
    static const tcod::ColorRGB fuchsia{255, 0, 255};
    static const tcod::ColorRGB magenta{255, 0, 191};
    static const tcod::ColorRGB pink{255, 0, 127};
    static const tcod::ColorRGB crimson{255, 0, 63};

    // Dark colors
    static const tcod::ColorRGB darkRed{191, 0, 0};
    static const tcod::ColorRGB darkFlame{191, 47, 0};
    static const tcod::ColorRGB darkOrange{191, 95, 0};
    static const tcod::ColorRGB darkAmber{191, 143, 0};
    static const tcod::ColorRGB darkYellow{191, 191, 0};
    static const tcod::ColorRGB darkLime{143, 191, 0};
    static const tcod::ColorRGB darkChartreuse{95, 191, 0};
    static const tcod::ColorRGB darkGreen{0, 191, 0};
    static const tcod::ColorRGB darkSea{0, 191, 95};
    static const tcod::ColorRGB darkTurquoise{0, 191, 143};
    static const tcod::ColorRGB darkCyan{0, 191, 191};
    static const tcod::ColorRGB darkSky{0, 143, 191};
    static const tcod::ColorRGB darkAzure{0, 95, 191};
    static const tcod::ColorRGB darkBlue{0, 0, 191};
    static const tcod::ColorRGB darkHan{47, 0, 191};
    static const tcod::ColorRGB darkViolet{95, 0, 191};
    static const tcod::ColorRGB darkPurple{143, 0, 191};
    static const tcod::ColorRGB darkFuchsia{191, 0, 191};
    static const tcod::ColorRGB darkMagenta{191, 0, 143};
    static const tcod::ColorRGB darkPink{191, 0, 95};
    static const tcod::ColorRGB darkCrimson{191, 0, 47};

    // Darker colors
    static const tcod::ColorRGB darkerRed{127, 0, 0};
    static const tcod::ColorRGB darkerFlame{127, 31, 0};
    static const tcod::ColorRGB darkerOrange{127, 63, 0};
    static const tcod::ColorRGB darkerAmber{127, 95, 0};
    static const tcod::ColorRGB darkerYellow{127, 127, 0};
    static const tcod::ColorRGB darkerLime{95, 127, 0};
    static const tcod::ColorRGB darkerChartreuse{63, 127, 0};
    static const tcod::ColorRGB darkerGreen{0, 127, 0};
    static const tcod::ColorRGB darkerSea{0, 127, 63};
    static const tcod::ColorRGB darkerTurquoise{0, 127, 95};
    static const tcod::ColorRGB darkerCyan{0, 127, 127};
    static const tcod::ColorRGB darkerSky{0, 95, 127};
    static const tcod::ColorRGB darkerAzure{0, 63, 127};
    static const tcod::ColorRGB darkerBlue{0, 0, 127};
    static const tcod::ColorRGB darkerHan{31, 0, 127};
    static const tcod::ColorRGB darkerViolet{63, 0, 127};
    static const tcod::ColorRGB darkerPurple{95, 0, 127};
    static const tcod::ColorRGB darkerFuchsia{127, 0, 127};
    static const tcod::ColorRGB darkerMagenta{127, 0, 95};
    static const tcod::ColorRGB darkerPink{127, 0, 63};
    static const tcod::ColorRGB darkerCrimson{127, 0, 31};

    // Darkest colors
    static const tcod::ColorRGB darkestRed{63, 0, 0};
    static const tcod::ColorRGB darkestFlame{63, 15, 0};
    static const tcod::ColorRGB darkestOrange{63, 31, 0};
    static const tcod::ColorRGB darkestAmber{63, 47, 0};
    static const tcod::ColorRGB darkestYellow{63, 63, 0};
    static const tcod::ColorRGB darkestLime{47, 63, 0};
    static const tcod::ColorRGB darkestChartreuse{31, 63, 0};
    static const tcod::ColorRGB darkestGreen{0, 63, 0};
    static const tcod::ColorRGB darkestSea{0, 63, 31};
    static const tcod::ColorRGB darkestTurquoise{0, 63, 47};
    static const tcod::ColorRGB darkestCyan{0, 63, 63};
    static const tcod::ColorRGB darkestSky{0, 47, 63};
    static const tcod::ColorRGB darkestAzure{0, 31, 63};
    static const tcod::ColorRGB darkestBlue{0, 0, 63};
    static const tcod::ColorRGB darkestHan{15, 0, 63};
    static const tcod::ColorRGB darkestViolet{31, 0, 63};
    static const tcod::ColorRGB darkestPurple{47, 0, 63};
    static const tcod::ColorRGB darkestFuchsia{63, 0, 63};
    static const tcod::ColorRGB darkestMagenta{63, 0, 47};
    static const tcod::ColorRGB darkestPink{63, 0, 31};
    static const tcod::ColorRGB darkestCrimson{63, 0, 15};

    // Light colors
    static const tcod::ColorRGB lightRed{255, 63, 63};
    static const tcod::ColorRGB lightFlame{255, 111, 63};
    static const tcod::ColorRGB lightOrange{255, 159, 63};
    static const tcod::ColorRGB lightAmber{255, 207, 63};
    static const tcod::ColorRGB lightYellow{255, 255, 63};
    static const tcod::ColorRGB lightLime{207, 255, 63};
    static const tcod::ColorRGB lightChartreuse{159, 255, 63};
    static const tcod::ColorRGB lightGreen{63, 255, 63};
    static const tcod::ColorRGB lightSea{63, 255, 159};
    static const tcod::ColorRGB lightTurquoise{63, 255, 207};
    static const tcod::ColorRGB lightCyan{63, 255, 255};
    static const tcod::ColorRGB lightSky{63, 207, 255};
    static const tcod::ColorRGB lightAzure{63, 159, 255};
    static const tcod::ColorRGB lightBlue{63, 63, 255};
    static const tcod::ColorRGB lightHan{111, 63, 255};
    static const tcod::ColorRGB lightViolet{159, 63, 255};
    static const tcod::ColorRGB lightPurple{207, 63, 255};
    static const tcod::ColorRGB lightFuchsia{255, 63, 255};
    static const tcod::ColorRGB lightMagenta{255, 63, 207};
    static const tcod::ColorRGB lightPink{255, 63, 159};
    static const tcod::ColorRGB lightCrimson{255, 63, 111};

    // Lighter colors
    static const tcod::ColorRGB lighterRed{255, 127, 127};
    static const tcod::ColorRGB lighterFlame{255, 159, 127};
    static const tcod::ColorRGB lighterOrange{255, 191, 127};
    static const tcod::ColorRGB lighterAmber{255, 223, 127};
    static const tcod::ColorRGB lighterYellow{255, 255, 127};
    static const tcod::ColorRGB lighterLime{223, 255, 127};
    static const tcod::ColorRGB lighterChartreuse{191, 255, 127};
    static const tcod::ColorRGB lighterGreen{127, 255, 127};
    static const tcod::ColorRGB lighterSea{127, 255, 191};
    static const tcod::ColorRGB lighterTurquoise{127, 255, 223};
    static const tcod::ColorRGB lighterCyan{127, 255, 255};
    static const tcod::ColorRGB lighterSky{127, 223, 255};
    static const tcod::ColorRGB lighterAzure{127, 191, 255};
    static const tcod::ColorRGB lighterBlue{127, 127, 255};
    static const tcod::ColorRGB lighterHan{159, 127, 255};
    static const tcod::ColorRGB lighterViolet{191, 127, 255};
    static const tcod::ColorRGB lighterPurple{223, 127, 255};
    static const tcod::ColorRGB lighterFuchsia{255, 127, 255};
    static const tcod::ColorRGB lighterMagenta{255, 127, 223};
    static const tcod::ColorRGB lighterPink{255, 127, 191};
    static const tcod::ColorRGB lighterCrimson{255, 127, 159};

    // Lightest colors
    static const tcod::ColorRGB lightestRed{255, 191, 191};
    static const tcod::ColorRGB lightestFlame{255, 207, 191};
    static const tcod::ColorRGB lightestOrange{255, 223, 191};
    static const tcod::ColorRGB lightestAmber{255, 239, 191};
    static const tcod::ColorRGB lightestYellow{255, 255, 191};
    static const tcod::ColorRGB lightestLime{239, 255, 191};
    static const tcod::ColorRGB lightestChartreuse{223, 255, 191};
    static const tcod::ColorRGB lightestGreen{191, 255, 191};
    static const tcod::ColorRGB lightestSea{191, 255, 223};
    static const tcod::ColorRGB lightestTurquoise{191, 255, 239};
    static const tcod::ColorRGB lightestCyan{191, 255, 255};
    static const tcod::ColorRGB lightestSky{191, 239, 255};
    static const tcod::ColorRGB lightestAzure{191, 223, 255};
    static const tcod::ColorRGB lightestBlue{191, 191, 255};
    static const tcod::ColorRGB lightestHan{207, 191, 255};
    static const tcod::ColorRGB lightestViolet{223, 191, 255};
    static const tcod::ColorRGB lightestPurple{239, 191, 255};
    static const tcod::ColorRGB lightestFuchsia{255, 191, 255};
    static const tcod::ColorRGB lightestMagenta{255, 191, 239};
    static const tcod::ColorRGB lightestPink{255, 191, 223};
    static const tcod::ColorRGB lightestCrimson{255, 191, 207};

    // Desaturated colors
    static const tcod::ColorRGB desaturatedRed{127, 63, 63};
    static const tcod::ColorRGB desaturatedFlame{127, 79, 63};
    static const tcod::ColorRGB desaturatedOrange{127, 95, 63};
    static const tcod::ColorRGB desaturatedAmber{127, 111, 63};
    static const tcod::ColorRGB desaturatedYellow{127, 127, 63};
    static const tcod::ColorRGB desaturatedLime{111, 127, 63};
    static const tcod::ColorRGB desaturatedChartreuse{95, 127, 63};
    static const tcod::ColorRGB desaturatedGreen{63, 127, 63};
    static const tcod::ColorRGB desaturatedSea{63, 127, 95};
    static const tcod::ColorRGB desaturatedTurquoise{63, 127, 111};
    static const tcod::ColorRGB desaturatedCyan{63, 127, 127};
    static const tcod::ColorRGB desaturatedSky{63, 111, 127};
    static const tcod::ColorRGB desaturatedAzure{63, 95, 127};
    static const tcod::ColorRGB desaturatedBlue{63, 63, 127};
    static const tcod::ColorRGB desaturatedHan{79, 63, 127};
    static const tcod::ColorRGB desaturatedViolet{95, 63, 127};
    static const tcod::ColorRGB desaturatedPurple{111, 63, 127};
    static const tcod::ColorRGB desaturatedFuchsia{127, 63, 127};
    static const tcod::ColorRGB desaturatedMagenta{127, 63, 111};
    static const tcod::ColorRGB desaturatedPink{127, 63, 95};
    static const tcod::ColorRGB desaturatedCrimson{127, 63, 79};

    // Metallic
    static const tcod::ColorRGB brass{191, 151, 96};
    static const tcod::ColorRGB copper{197, 136, 124};
    static const tcod::ColorRGB gold{229, 191, 0};
    static const tcod::ColorRGB silver{203, 203, 203};

    // Miscellaneous
    static const tcod::ColorRGB celadon{172, 255, 175};
    static const tcod::ColorRGB peach{255, 159, 127};
}
