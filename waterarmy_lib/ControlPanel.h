//
// Created by jaume on 11/8/19.
//

#ifndef WATERARMY_MAIN_WATERARMY_LIB_CONTROLPANEL_H_
#define WATERARMY_MAIN_WATERARMY_LIB_CONTROLPANEL_H_

class ControlPanel {
 public:
  virtual ~ControlPanel() = default;
  virtual unsigned short getMinimumMoistureSetting() = 0;
  virtual unsigned short getWaterAmountSetting() = 0;
};

#endif //WATERARMY_MAIN_WATERARMY_LIB_CONTROLPANEL_H_
