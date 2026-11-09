#ifndef LORD_SUMI_ACCESSIBLE_DOORBELL_H
#define LORD_SUMI_ACCESSIBLE_DOORBELL_H
#include <math.h>
namespace doorbell {
enum class Reason { Invalid, Debounced, QuietHours, Ring };
struct Settings {
 double debounce_seconds;int quiet_start,quiet_end;
 Settings(double debounce=0.3,int start=22,int end=7):
  debounce_seconds(debounce),quiet_start(start),quiet_end(end){}
};
struct Result {
 bool valid,accepted,visual,haptic,audio;Reason reason;
 Result(bool v,bool a,bool vis,bool hap,bool aud,Reason r):
   valid(v),accepted(a),visual(vis),haptic(hap),audio(aud),reason(r){}
};
inline bool valid_settings(const Settings& s){
 return isfinite(s.debounce_seconds)&&s.debounce_seconds>=0&&
  s.quiet_start>=0&&s.quiet_start<=23&&s.quiet_end>=0&&s.quiet_end<=23;
}
class Doorbell {
 public:
 explicit Doorbell(Settings settings=Settings()):settings_(settings),has_last_(false),last_press_(0){}
 Result press(double seconds,int local_hour) {
   if(!valid_settings(settings_)||!isfinite(seconds)||seconds<0||local_hour<0||local_hour>23||
      (has_last_&&seconds<last_press_))
      return Result(false,false,false,false,false,Reason::Invalid);
   if(has_last_&&seconds-last_press_<settings_.debounce_seconds)
      return Result(true,false,false,false,false,Reason::Debounced);
   last_press_=seconds;has_last_=true;
   bool quiet=settings_.quiet_start==settings_.quiet_end?false:
      settings_.quiet_start<settings_.quiet_end?
      (local_hour>=settings_.quiet_start&&local_hour<settings_.quiet_end):
      (local_hour>=settings_.quiet_start||local_hour<settings_.quiet_end);
   return Result(true,true,true,true,!quiet,quiet?Reason::QuietHours:Reason::Ring);
 }
 private:
 Settings settings_;bool has_last_;double last_press_;
};
}
#endif
