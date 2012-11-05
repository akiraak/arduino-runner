//
//  ViewController.h
//  sandbox
//
//  Created by 小酒井 輝 on 2012/11/04.
//  Copyright (c) 2012年 小酒井 輝. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

@interface ViewController : UIViewController <MKMapViewDelegate, NSXMLParserDelegate> {
    IBOutlet MKMapView* mapView;

    NSMutableArray *statuses;
    BOOL inNameElement;
    BOOL inTextElement;
    NSMutableString *name;
    NSMutableString *text;
}

@end
