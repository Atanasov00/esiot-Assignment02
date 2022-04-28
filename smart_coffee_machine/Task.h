#ifndef __TASK__
#define __TASK__

class Task {

  private:
  
  int myPeriod;
  int timeElapsed;
  bool active;

  public:

    Task() {
      active = false;
    }

    virtual void init(int period) {
      myPeriod = period;  
      timeElapsed = 0;
      active = true;
    }
    
    virtual void tick() = 0;
    
    bool updateAndCheckTime(int basePeriod) {
      timeElapsed += basePeriod;
      if (timeElapsed >= myPeriod){
        timeElapsed = 0;
        return true;
      } else {
        return false; 
      }
  }

  bool isActive(){
    return active;
  }

  virtual void setActive(bool active){
    timeElapsed = 0;
    this->active = active;
  }
};

#endif
