# Syntax goal

´´´
flx::FlagChain* flagchain = new flx::FlagChain(flags); 
// or flagchain->setFlags(flags); if nor already set
flagChain->add(someFlagEnum::flag1, &someFunc); // if someFunc is a boolean, the next 3rd argument can be a void* for if someFunc returns false
flagChain->add(someFlagEnum::flag2, &someOtherFunc);
flagChain->execute();
flagChain->deleteFlagChain();
´´´