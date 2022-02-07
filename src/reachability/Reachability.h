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

   private:
      void computeReachableStates();
      BDD_ID computeTransitionRelation(std::vector<BDD_ID>& nextStateBits, std::vector<BDD_ID>& transitionFunction);
      /* Question: is compute characteristic function just
      * transition relaton with 0 ? (if yes let arguments if no then remove arguments)
      * BDD_ID computeCharacteristicFunction();
      */

      int stateSize;
      std::vector<BDD_ID> currentStateBits;
      std::vector<BDD_ID> nextStateBits;
      std::vector<BDD_ID> transitionFunction;

      std::vector<std::vector<bool>> reachableStates;
   };

}
#endif
