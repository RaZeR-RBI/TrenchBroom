//
//  Entitiy.h
//  TrenchBroom
//
//  Created by Kristian Duske on 15.03.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Entity.h"
#import "Math.h"

@protocol Map;
@class MutableBrush;
@class Face;
@class EntityDefinition;

@interface MutableEntity : NSObject <Entity> {
    EntityDefinition* entityDefinition;
    NSNumber* entityId;
    id <Map> map;
	NSMutableArray* brushes;
	NSMutableDictionary* properties;
    TVector3f center;
    TVector3f origin;
    TBoundingBox bounds;
    BOOL valid;
    int filePosition;
}

- (id)initWithProperties:(NSDictionary *)theProperties;

- (void)addBrush:(MutableBrush *)brush;
- (void)removeBrush:(MutableBrush *)brush;
- (void)brushChanged:(MutableBrush *)brush;

- (void)setProperty:(NSString *)key value:(NSString *)value;
- (void)removeProperty:(NSString *)key;

- (void)setEntityDefinition:(EntityDefinition *)theEntityDefintion;
- (void)setMap:(id <Map>)theMap;

- (int)filePosition;
- (void)setFilePosition:(int)theFilePosition;
@end
