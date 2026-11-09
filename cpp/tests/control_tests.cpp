#include <cassert>
#include <limits>
#include "AccessibleDoorbell.h"
int main(){
 using namespace doorbell;
 Doorbell d;
 Result normal=d.press(1,12);
 assert(normal.valid&&normal.accepted&&normal.visual&&normal.haptic&&normal.audio);
 Result bounce=d.press(1.1,12);
 assert(bounce.valid&&!bounce.accepted&&bounce.reason==Reason::Debounced);
 Result quiet=d.press(2,23);
 assert(quiet.valid&&quiet.accepted&&quiet.visual&&quiet.haptic&&!quiet.audio);
 assert(!d.press(3,6).audio);
 assert(d.press(4,7).audio);
 assert(!d.press(0,12).valid);
 assert(!d.press(5,24).valid);
 assert(!d.press(std::numeric_limits<double>::quiet_NaN(),1).valid);
 Doorbell none(Settings(0,10,10));assert(none.press(0,10).audio);
 Doorbell day(Settings(0.3,10,12));assert(!day.press(0,11).audio);
 assert(day.press(1,13).audio);
 Doorbell invalid(Settings(-1));assert(!invalid.press(1,12).valid);
}
