//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H

#include "ReachabilityInterface.h"

namespace ClassProject {

   class Reachability : public ReachabilityInterface {
   
   public:

      Reachability(unsigned int stateSize);

      const std::vector<BDD_ID> &getStates() const;
      bool isReachable(const std::vector<bool> &stateVector);
      void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions);
      void setInitState(const std::vector<bool> &stateVector);
      const vector<bool> &getInitStates() const;
      const vector<BDD_ID> &getTransitionFunctions() const;
      const BDD_ID &getCr() const;

   private:
      BDD_ID computeReachableStates();
      BDD_ID computeTransitionRelation(std::vector<BDD_ID>& nextStateBits, std::vector<BDD_ID>& transitionFunction);
      BDD_ID computeInitialCharacteristic(std::vector<BDD_ID> currentStateBits, std::vector<bool> initStates);

      int stateSize;
      BDD_ID Cr;

      std::vector<bool> initStates;
      std::vector<BDD_ID> currentStateBits;
      std::vector<BDD_ID> nextStateBits;
      std::vector<BDD_ID> transitionFunction;
   };
}
#endif
