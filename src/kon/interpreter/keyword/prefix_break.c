#include "stdio.h"
#include "stdlib.h"
#include "prefix_lambda.h"
#include "../cps_interpreter.h"

KonTrampoline* KON_EvalPrefixBreak(KonState* kstate, KN expression, KN env, KonContinuation* cont)
{
    KON_DEBUG("meet prefix marcro break");
    KON_DEBUG("rest words %s", KON_StringToCstr(KON_ToFormatString(kstate, expression, true, 0, "  ")));

    KN loopCont = KON_EnvLookup(kstate, env, "break");
    
    KonTrampoline* bounce;
    if (KON_IS_CONTINUATION(loopCont)) {
        // loop's continuation, just receive 1 argument;
        bounce = AllocBounceWithType(KON_TRAMPOLINE_RUN);
        bounce->Run.Value = KON_FALSE;
        // goto this continuation directly. skip next exprs
        bounce->Run.Cont = loopCont;
        return bounce;
    }
    else {
        // TODO error occurred, throw exception?
        bounce = AllocBounceWithType(KON_TRAMPOLINE_RUN);
        bounce->Run.Value = KON_FALSE;
        bounce->Run.Cont = cont;
        return bounce;
    }
}