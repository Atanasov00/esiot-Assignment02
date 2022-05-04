#ifndef __TASK__
#define __TASK__


class Task {

  private:
  
  int myPeriod;
  int timeElapsed;
  bool active;
  bool completed;

  public:

    Task() {
      active = false;
    }

    virtual void init(int period) {
      myPeriod = period;  
      timeElapsed = 0;
    }

    virtual void init(){}
    
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

  void setCompleted(){
    completed = true;
    active = false;
  }

  bool isCompleted(){
    return completed;
  }

  virtual void setActive(bool active){
    timeElapsed = 0;
    this->active = active;
  }
};

#endif
