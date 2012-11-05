//
//  ViewController.m
//  sandbox
//
//  Created by 小酒井 輝 on 2012/11/04.
//  Copyright (c) 2012年 小酒井 輝. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    CLLocationCoordinate2D coors[4];
    // 渋谷、原宿、代々木、新宿
    coors[0] = CLLocationCoordinate2DMake(35.658517, 139.701334);
    coors[1] = CLLocationCoordinate2DMake(35.670168, 139.702687);
    coors[2] = CLLocationCoordinate2DMake(35.683061, 139.702042);
    coors[3] = CLLocationCoordinate2DMake(35.690921, 139.700258);
    MKPolyline *line = [MKPolyline polylineWithCoordinates:coors count:4];
    [mapView addOverlay:line];
    
    // 地図の設定
    mapView.delegate = self;
    MKCoordinateRegion region = mapView.region;
    region.span.latitudeDelta = 0.05; // 地図の表示倍率
    region.span.longitudeDelta = 0.05;
    region.center = coors[1]; // 原宿を画面中央に表示
    [mapView setRegion:region animated:YES];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"car.kml" ofType:NULL];
    NSData *d = [[NSData alloc] initWithContentsOfFile:path];
    NSXMLParser *parser = [[NSXMLParser alloc] initWithData:d];
    [parser setDelegate:self];
    [parser parse];
    
    int i = 0;
    i++;
}

#pragma mark MKMapViewDelegate methods
- (MKOverlayView *)mapView:(MKMapView *)mapView
            viewForOverlay:(id<MKOverlay>)overlay {
    MKPolylineView *view = [[MKPolylineView alloc] initWithOverlay:overlay];
    //view.strokeColor = [UIColor blueColor];
    view.strokeColor = [UIColor colorWithRed:0.0f green:1.0f blue:5.0f alpha:0.5f];
    view.lineWidth = 5.0;
    return view;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)parserDidStartDocument:(NSXMLParser *)parser {
	NSLog(@"解析を開始しました");
}

- (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError {
	NSLog(@"エラーが発生しました");
}

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSDictionary *)attributeDict{
	NSLog(@"要素[%@]が見つかりました", elementName);
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName{
	NSLog(@"要素[%@]が終わりました", elementName);
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string{
	NSLog(@"文字列[%@]が見つかりました", string);
}

- (void)parserDidEndDocument:(NSXMLParser *)parser {
	NSLog(@"解析が完了しました");
}
@end
