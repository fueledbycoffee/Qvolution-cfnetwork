#import <Foundation/NSURLRequest.h>
#import <CFNetwork/CFURLRequest.h>

@interface NSURLRequest ()
+ (NSTimeInterval)defaultTimeoutInterval;
- (id)_initWithCFURLRequest:(CFURLRequestRef)req;
- (CFURLRequestRef)_CFURLRequest;
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
}

- (void)dealloc;

@end
