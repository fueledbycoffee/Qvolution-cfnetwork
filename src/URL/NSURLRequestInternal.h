#import <Foundation/NSURLRequest.h>
#import <CFNetwork/CFURLRequest.h>
#import <Foundation/NSDictionary.h>

@interface NSURLRequest ()
+ (NSTimeInterval)defaultTimeoutInterval;
- (id)_initWithCFURLRequest:(CFURLRequestRef)req;
- (CFURLRequestRef)_CFURLRequest;
- (id)_protocolPropertyForKey:(NSString *)key;
- (void)_setProtocolProperty:(id)value forKey:(NSString *)key;
@end

CF_PRIVATE
@interface NSURLRequestInternal : NSObject {
@public
    CFURLRequestRef request;
    // Request properties CFURLRequest does not carry; copied with the request.
    BOOL assumesHTTP3Capable;
    BOOL allowsExpensiveNetworkAccess;
    BOOL allowsConstrainedNetworkAccess;
    BOOL requiresDNSSECValidation;
    // NSURLProtocol properties (setProperty:forKey:inRequest:), by key value.
    NSMutableDictionary *protocolProperties;
}

- (void)dealloc;

@end
