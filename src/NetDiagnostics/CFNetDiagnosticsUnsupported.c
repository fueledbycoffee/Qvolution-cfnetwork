#include "CFNetDiagnostics.h"
#include <errno.h>

CFNetDiagnosticRef CFNetDiagnosticCreateWithURL(CFAllocatorRef allocator, CFURLRef url)
{
    errno = ENOTSUP;
    return NULL;
}

CFNetDiagnosticStatus CFNetDiagnosticDiagnoseProblemInteractively(CFNetDiagnosticRef details)
{
    return kCFNetDiagnosticErr;
}
