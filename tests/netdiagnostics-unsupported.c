#include "CFNetDiagnostics.h"
#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    assert(argc == 2);
    void *library = dlopen(argv[1], RTLD_NOW | RTLD_LOCAL);
    if (!library) { fprintf(stderr, "%s\n", dlerror()); return 1; }
    CFNetDiagnosticRef (*create)(CFAllocatorRef, CFURLRef) = dlsym(library, "CFNetDiagnosticCreateWithURL");
    CFNetDiagnosticStatus (*diagnose)(CFNetDiagnosticRef) = dlsym(library, "CFNetDiagnosticDiagnoseProblemInteractively");
    assert(create && diagnose);
    errno = 0;
    assert(create(NULL, NULL) == NULL && errno == ENOTSUP);
    assert(diagnose(NULL) == kCFNetDiagnosticErr);
    dlclose(library);
    puts("PASS CFNetwork diagnostics: 2 exports, unsupported creation and diagnosis");
    return 0;
}
