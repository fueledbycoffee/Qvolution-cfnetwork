#import <Foundation/Foundation.h>
#include <stdio.h>

static int checks, failures;
static void expect(BOOL ok, const char *label)
{
    checks++;
    failures += !ok;
    printf("%s %s\n", ok ? "ok" : "FAIL", label);
}
static id value(NSString *key, NSURLRequest *r) { return [NSURLProtocol propertyForKey:key inRequest:r]; }

int main(void)
{
    @autoreleasepool {
        NSMutableString *key = [NSMutableString stringWithString:@"protocol-key"];
        NSMutableString *equalKey = [NSMutableString stringWithString:@"protocol-key"];
        expect(key != equalKey && [key isEqual:equalKey], "equal keys are distinct objects");
        NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:@"http://example.invalid/"]];
        [NSURLProtocol setProperty:@"original" forKey:key inRequest:request];
        expect([value(equalKey, request) isEqual:@"original"], "lookup by equal key value");
        NSURLRequest *copy = [request copy];
        NSMutableURLRequest *mutableCopy = [request mutableCopy];
        NSMutableURLRequest *copyOfCopy = [copy mutableCopy];
        expect([value(equalKey, copy) isEqual:@"original"], "copy keeps metadata");
        expect([value(equalKey, mutableCopy) isEqual:@"original"], "mutableCopy keeps metadata");
        expect([value(equalKey, copyOfCopy) isEqual:@"original"], "copy of copy keeps metadata");
        [NSURLProtocol setProperty:@"changed" forKey:equalKey inRequest:mutableCopy];
        expect([value(key, mutableCopy) isEqual:@"changed"], "equal key replaces value");
        expect([value(key, request) isEqual:@"original"] && [value(key, copy) isEqual:@"original"], "mutation leaves source and immutable copy independent");
        [NSURLProtocol removePropertyForKey:equalKey inRequest:request];
        expect(value(key, request) == nil, "remove by equal key value");
        expect([value(key, copy) isEqual:@"original"] && [value(key, mutableCopy) isEqual:@"changed"], "source removal leaves copies independent");
        [NSURLProtocol removePropertyForKey:key inRequest:mutableCopy];
        expect(value(equalKey, mutableCopy) == nil && [value(equalKey, copyOfCopy) isEqual:@"original"], "copy removal leaves other copy independent");
        [copy release]; [mutableCopy release]; [copyOfCopy release];
    }
    printf("HARNESS done: %d checks, %d failed\n", checks, failures);
    return failures != 0;
}
