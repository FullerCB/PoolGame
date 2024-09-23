#include "Borders.h"

std::vector<sLineSegment> vectorLines(6);
std::vector<sPocketProperties> pocketLocations(6);


void Borders::createBorder(float borderScaler)
{
    //left side
    vectorLines[0].sx = 175.0f * borderScaler;
    vectorLines[0].sy = 653.0f * borderScaler;
    vectorLines[0].ex = 175.0f * borderScaler;
    vectorLines[0].ey = 2527.3f * borderScaler;
    vectorLines[0].radius = 180.0f * borderScaler;
    //right side
    vectorLines[1].sx = 5381.0f * borderScaler;
    vectorLines[1].sy = 653.0f * borderScaler;
    vectorLines[1].ex = 5381.0f * borderScaler;
    vectorLines[1].ey = 2527.3f * borderScaler;
    vectorLines[1].radius = 180.0f * borderScaler;
    //top left
    vectorLines[2].sx = 653.0f * borderScaler;
    vectorLines[2].sy = 175.0f * borderScaler;
    vectorLines[2].ex = 2510.0f * borderScaler;
    vectorLines[2].ey = 175.0f * borderScaler;
    vectorLines[2].radius = 180.0f * borderScaler;
    //top right
    vectorLines[3].sx = 3046.0f * borderScaler;
    vectorLines[3].sy = 175.0f * borderScaler;
    vectorLines[3].ex = 4950.0f * borderScaler;
    vectorLines[3].ey = 175.0f * borderScaler;
    vectorLines[3].radius = 180.0f * borderScaler;
    //bottom left
    vectorLines[4].sx = 653.0f * borderScaler;
    vectorLines[4].sy = 3006.0f * borderScaler;
    vectorLines[4].ex = 2510.0f * borderScaler;
    vectorLines[4].ey = 3006.0f * borderScaler;
    vectorLines[4].radius = 180.0f * borderScaler;
    //bottom right
    vectorLines[5].sx = 3046.0f * borderScaler;
    vectorLines[5].sy = 3006.0f * borderScaler;
    vectorLines[5].ex = 4950.0f * borderScaler;
    vectorLines[5].ey = 3006.0f * borderScaler;
    vectorLines[5].radius = 180.0f * borderScaler;
}

void Borders::createPockets(float borderScaler)
{
    //Pocket locations and radius
    float pocketCornerRad = 145.0f * borderScaler;
    float pocketCenterRad = 130.0f * borderScaler;
    //TL
    pocketLocations[0].position.x = 365.0f * borderScaler;
    pocketLocations[0].position.y = 355.0f * borderScaler;
    pocketLocations[0].radius = pocketCornerRad;
    //TM
    pocketLocations[1].position.x = 2772.0f * borderScaler;
    pocketLocations[1].position.y = 214.0f * borderScaler;
    pocketLocations[1].radius = pocketCenterRad;
    //TR
    pocketLocations[2].position.x = 5212.0f * borderScaler;
    pocketLocations[2].position.y = 355.0f * borderScaler;
    pocketLocations[2].radius = pocketCornerRad;
    //BL
    pocketLocations[3].position.x = 365.0f * borderScaler;
    pocketLocations[3].position.y = 2812.0f * borderScaler;
    pocketLocations[3].radius = pocketCornerRad;
    //BM
    pocketLocations[4].position.x = 2772.0f * borderScaler;
    pocketLocations[4].position.y = 2952.0f * borderScaler;
    pocketLocations[4].radius = pocketCenterRad;
    //BR
    pocketLocations[5].position.x = 5212.0f * borderScaler;
    pocketLocations[5].position.y = 2812.0f * borderScaler;
    pocketLocations[5].radius = pocketCornerRad;
}
